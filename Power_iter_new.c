#include "Power_iter_new.h"

//create random vector for initialization of power iteration
int create_vec(int size, double *vec){
    int i;
    clock_t start;
    srand(time(NULL));
    start = clock();
    for (i=0; i<size; i++){
        vec[i] = (double)rand();
    }
    return 0;
}

///calculate ||C|| (sum of max column) /// optionally add it to diagonal elements of symmetric matrix B to create b^, but we dont need to keep b^
/// complexity O(m+n)*n , sparse graphs with m ~ n are in in the focus thus the resulting complexity would be O(n^2)
int matrix_shift_C_new(Graph* graph, double* max_p, Vector_double *row_sums_p){
    int i,j; double sum, max,q, count, index, *temp, *temp2;
    temp = (double*) calloc(graph->number_of_nodes , sizeof(double));
    temp2 = (double*) calloc(graph->adj_matrix->size , sizeof(double));
    sum=0, max=0, count =0, index=0;

    for(i=0;i<graph->adj_matrix->size;i++){
        for (j=0;j<graph->number_of_nodes;j++) {
            if ((graph->indices_set[j] == graph->adj_matrix->row[i]) || (graph->indices_set[j] == graph->adj_matrix->col[i])) {
                index += 1;
            }
            if (index == 2){
                temp2[i]=1;
                break;
            }
        }
        index = 0;
    }

    for (i=0; i<graph->number_of_nodes; i++) {
        /// the loop is O(M)
        for (j = 0; j < graph->adj_matrix->size; j++) {
            if (temp2[j]==1){
                if ((graph->adj_matrix->row[j] == i) || (graph->adj_matrix->col[j] == i)) {
                    if (graph->adj_matrix->row[j] == i) {
                        temp[graph->adj_matrix->col[j]] += 1.0;
                    } else {
                        temp[graph->adj_matrix->row[j]] += 1.0;
                    }
                }
            }
        }
        /// the loop is O(n)
        for (j=0; j<graph->number_of_nodes; j++){
            temp[j] +=  - (((double)graph->deg_vec->data[i]) * ((double)graph->deg_vec->data[j]) / (double)graph->M);
            sum += temp[j];
        }

        row_sums_p->data[i]=sum;
        sum=0;

        /// the loop is O(n)
        for (j=0; j<graph->number_of_nodes; j++){
            if(i==j){
                sum += fabs(temp[j]-row_sums_p->data[i]);
            }
            else {
                sum += fabs(temp[j]);
            }
        }
        if (sum>max){
            max = sum;
        }
        sum=0;
        /// memset is O(n)
        memset(temp,(double)0.0,(graph->number_of_nodes)*(sizeof(double)));
    }

    free(temp); free(temp2);
    *max_p = max;

    return 0;

}

///multiply vector by symmetric shifted matrix B
int vec_mult_B(Graph* graph, double *rand_vec, double max,double *row_norm, Vector_double *row_sums_p) {
    int i=0, ind1=0,ind2=0;
    long double cons=0.0, *comp2, *comp3; double* comp;

    ///step1 - calculate A * random vector - O(m)
    for (i=0; i<graph->adj_matrix->size; i++){
        ind1 = graph->adj_matrix->row[i];
        ind2 = graph->adj_matrix->col[i];
        row_norm[ind1] += rand_vec[ind2];
        row_norm[ind2] += rand_vec[ind1];
//        printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
    }
//    printf("\n\n%f  %f  %f\n", rand_vec[0],rand_vec[1],rand_vec[2]);
//    printf("\n\n%d  %d  %d\n", graph->adj_matrix->row[0],graph->adj_matrix->row[1],graph->adj_matrix->row[2]);
//    printf("\n\n%d  %d  %d\n", graph->deg_vec->data[0],graph->deg_vec->data[1],graph->deg_vec->data[2]);
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step2 - to calculate Constant = Random vector * k^T - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(rand_vec[i])*(long double)(graph->deg_vec->data[i]);
    }
//    printf("\n%Lf  \\n", cons);

    ///step3 - multiply Constant (Random vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp2[i] = cons*(graph->deg_vec->data[i])/(graph->M);
    }
//    printf("\n\n%Lf  %Lf  %Lf\n", comp2[0],comp2[1],comp2[2]);

    ///step4 - random vector * ||C|| (matrix shift max column sum) - O(n)
    comp3 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp3[i] = (long double)max * (long double)rand_vec[i];
    }
//    printf("\n\n%Lf  %Lf  %Lf\n", comp3[0],comp3[1],comp3[2]);

    ///step5 - combine 4 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i]+(double)comp3[i];
    }
    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step6 - deduct Row sums of B_hat matrix * Eigenvector  - O(n)
    comp = (double *)malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p->data[i]*rand_vec[i];
        row_norm[i] = row_norm[i] - comp[i];
    }
    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
    free(comp);
    free(comp2);
    free(comp3);
    return 0;
}

int norm_vec (Graph* graph, double *rand_vec, double max,double *row_norm,Vector_double *row_sums_p){
    int i=0;
    double sum=0.0;
    vec_mult_B(graph,rand_vec,max,row_norm,row_sums_p);
    ///step5 - combine 4 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        sum +=pow(row_norm[i],2);
    }

    ///step6 - normalize - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]/pow(sum,0.5);
    }

    ///print normalized vector at each step of power iter
    for (i=0; i<graph->number_of_nodes; i++){
        printf("%f\n",row_norm[i]);
    }

    return 0;
}

//check if the difference between two vectors is ~0
int check_difference(int height ,double *temp ,double *next){
    double difference=0.0, *pointer1 = NULL, *pointer2 = NULL;
    int i;
    pointer1 = &temp[0]; pointer2 = &next[0];

    for (i = 0; i < height; i++) {
        difference=fabs((*(pointer1 + i))-(*(pointer2 + i)));
        if (!IS_POSITIVE(difference)){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

///power iteration which starts with random vector and matrix shift and returns the Pair structure with eigenvector and eigenvalue
///int powerIteration(SymMatrix *bg_hat_matrix_p ,Pair* pair_p, Vector_double *row_sums_p){
int powerIteration(Graph* graph,Pair* pair_p, Vector_double *row_sums_p){
    double *temp = NULL, *row_norm = NULL,  *vec = NULL, *max =NULL, numerator, max_v;
    int check, true=0, i=0; int j=0; double sum=0.0, value_without_c = 0.0; double* vect_temp;
    max = &max_v;
    vec = (double *)malloc(graph->number_of_nodes*sizeof(double));
    /// using calloc to initialize to zero - important!
    row_norm = (double *)calloc(graph->number_of_nodes,sizeof(double));

    /// create random vector
    create_vec(graph->number_of_nodes, vec);

    ///print random vector
    for (i=0; i<graph->number_of_nodes; i++){
        printf("\n\n%f",vec[i]);
    }

    matrix_shift_C_new(graph, max, row_sums_p);
    ///print ||C|| = max column
    printf("\n\n %f \n\n",max_v);

    temp = vec;
    while (true == 0) {
        norm_vec(graph,temp, max_v, row_norm, row_sums_p);
//            printf("%f %f %f  \\n", row_norm[0],row_norm[1],row_norm[2]);
        check=check_difference(graph->number_of_nodes ,temp ,row_norm);
        if (check==0){
            free(temp);
            temp = row_norm;
            row_norm = (double *)calloc(graph->number_of_nodes,sizeof(double));
        }
        else{
            free(temp);
            true=1;
        }
    }

    pair_p->eigenvector = row_norm;
    ///print eigenvector
    for (i=0; i<graph->number_of_nodes; i++){
        printf("\n\n%f", pair_p->eigenvector[i] );
    }

    ///find corresponding eigenvalue of the shifted matrix
    numerator = 0.0;
//    denominator=0.0;
//    ///calculate eigenvector * eigenvector O(n)
//    for(i=0; i<graph->number_of_nodes;i++){
//        denominator+= pair_p->eigenvector[i]*pair_p->eigenvector[i];
//    }
//    printf("\n%f\n\n", denominator);
    ///important to use calloc here, so that zeroes are initiated
    vect_temp = (double *)calloc(graph->number_of_nodes,sizeof(double));
    vec_mult_B(graph, pair_p->eigenvector , max_v,vect_temp, row_sums_p);


///dot product of eigenvector and vector with the results from B_hat shifted * eigenvector - O(n)
    for(i=0; i<graph->number_of_nodes;i++){
        numerator+= vect_temp[i]*pair_p->eigenvector[i];
    }
    printf("\n\n%f \n", numerator);

///deduct ||C|| to get leading eigenvalue of the original matrix O(1)
//    printf("\n\n%f \n", value);
    value_without_c = numerator - max_v;
    pair_p->eigenvalue = value_without_c;

    printf("\n\n%f \n", pair_p->eigenvalue);

//    free(row_norm);
    return 0;
}
