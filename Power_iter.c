#include "Power_iter.h"


int indices_to_indices_set(Group* group,int *indices, int size, int* indices_set){
    int i, count =0;
    for (i=0; i<size; i++){
        if((indices[count] == i)&&(count<group->group_size)) {
            indices_set[i] = 1;
            count +=1;
        }
        else{
            indices_set[i] = 0;
        }
    }
    return 0;
}

///create random vector for initialization of power iteration ; O(n)
int create_vec(Group* g, int size, double *vec){
    int i;
    int* indices_set;
    indices_set = (int*)malloc(size*sizeof(int));
    indices_to_indices_set(g,g->indices, size, indices_set);

    srand(time(NULL));
    for (i=0; i<size; i++){
        if (indices_set[i] == 0){
            vec[i] = 0;
        }
        else if (indices_set[i] == 1){
            vec[i] = (double)rand();
        }
        else{
            printf("unknown character instead of index; only 0,1 are allowed");
            return 1;
        }
    }
    free(indices_set);
    return 0;
}

///calculate ||C|| (sum of max column) /// optionally add it to diagonal elements of symmetric matrix B to create b^, but we dont need to keep b^
/// complexity O(m+n)*n , sparse graphs with m ~ n are in in the focus thus the resulting complexity would be O(n^2)
int matrix_shift_C_new(Graph* graph, Group* g, double* max_p, Vector_double *row_sums_p){
    int i,j;
    double sum, max;
    double * temp;
    temp = (double*) calloc( graph->number_of_nodes , sizeof(double));
    sum=0, max=0;

    int* indices_set;
    indices_set = (int*)malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g,g->indices, graph->number_of_nodes, indices_set);

    int* Adj_indices_set;
    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g,g->Adj_indices, graph->M/2, Adj_indices_set);


    /// the loop is O(n*(m+n))
    for (i=0; i<graph->number_of_nodes; i++){

        /// the loop is O(M); going over Adj matrix and adding 1 where appropriate
        for (j=0; j<graph->adj_matrix->size;j++) {
            if (Adj_indices_set[j] == 1) {
                if ((graph->adj_matrix->row[j] == i) || (graph->adj_matrix->col[j] == i)) {
                    if (graph->adj_matrix->row[j] == i) {
                        temp[graph->adj_matrix->col[j]] += 1.0;
                    } else {
                        temp[graph->adj_matrix->row[j]] += 1.0;
                    }
                }
            }
        }

        /// the loop is O(n); deducting kikj/M
        for (j=0; j<graph->number_of_nodes; j++){
            temp[j] +=  - (((double)graph->deg_vec->data[i]) * ((double)graph->deg_vec->data[j]) / (double)graph->M);
//            printf("  %f", temp[j]);
        }

        /// the loop is O(n); multiplying by the indices , not relevant elements will turn zero
        for (j=0; j<graph->number_of_nodes; j++){
            temp[j] = temp[j]*indices_set[i]*indices_set[j];
//            printf("  %f", temp[j]);
            sum += temp[j];
        }


//            printf("\n %f  %f  %f \n", temp[0],temp[1],temp[2]);
        row_sums_p->data[i]=sum;
//        printf("\n  %f\n", sum);
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

//    printf("\n %f \n", max);
    free(temp);
    free(indices_set);
    free(Adj_indices_set);
    *max_p = max;
    return 0;

}

///multiply vector by symmetric shifted matrix B ; O(n+m)
int vec_mult_B_shifted(Graph* graph, Group* g_p, double *rand_vec, double max,double *row_norm, Vector_double *row_sums_p) {
    int i=0, ind1=0,ind2=0;
    long double cons=0.0, *comp2, *comp3; double* comp;

    int* indices_set;
    indices_set = (int*)malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, indices_set);

    int* Adj_indices_set;
    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set);

//    printf("\n  ");
//    for (i=0; i<graph->adj_matrix->size; i++){
//        printf("  %d  ", g_p->Adj_indices[i]);
//    }
//    printf("\n  ");

    ///step1 - calculate A * random vector - O(m)
    for (i=0; i<graph->adj_matrix->size; i++){
        if (Adj_indices_set[i]==1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            row_norm[ind1] += rand_vec[ind2];
            row_norm[ind2] += rand_vec[ind1];
        }
//        printf("\n\n%f  %f  %f  %f  %f   %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);
    }
//    printf("\n\n%f  %f  %f  %f  %f   %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);
//    printf("\n\n%f  %f  %f\n", rand_vec[0],rand_vec[1],rand_vec[2]);
//    printf("\n\n%d  %d  %d\n", graph->adj_matrix->row[0],graph->adj_matrix->row[1],graph->adj_matrix->row[2]);
//    printf("\n\n%d  %d  %d\n", graph->deg_vec->data[0],graph->deg_vec->data[1],graph->deg_vec->data[2]);
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step2 - to calculate Constant = Random vector * k^T - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(rand_vec[i])*(long double)(graph->deg_vec->data[i]);
    }
//    printf("\n%Lf  ", cons);

    ///step3 - multiply Constant (Random vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
    }
//    printf("\n\n%Lf  %Lf  %Lf   %Lf  %Lf  %Lf\n", comp2[0],comp2[1],comp2[2],comp2[3],comp2[4],comp2[5]);

    ///step4 - random vector * ||C|| (matrix shift max column sum) - O(n)
    comp3 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp3[i] = (long double)max * (long double)rand_vec[i];
    }
//    printf("\n\n%Lf  %Lf  %Lf   %Lf  %Lf  %Lf\n", comp3[0],comp3[1],comp3[2],comp3[3],comp3[4],comp3[5]);

    ///step5 - combine 4 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i]+(double)comp3[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step6 - deduct Row sums of B_hat matrix * Eigenvector  - O(n)
    comp = (double *)malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p->data[i]*rand_vec[i];
        row_norm[i] = row_norm[i] - comp[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
    free(comp);
    free(comp2);
    free(comp3);
    free(indices_set);
    free(Adj_indices_set);
    return 0;
}

///O(n+m) due to vec_mult_B complexity
int norm_vec (Graph* graph, Group* g_p, double *rand_vec, double max,double *row_norm,Vector_double *row_sums_p){
    int i=0;
    double sum=0.0;
    vec_mult_B_shifted(graph, g_p,rand_vec,max,row_norm,row_sums_p);
    ///step5 - combine 4 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        sum +=pow(row_norm[i],2);
    }

    ///step6 - normalize - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]/pow(sum,0.5);
    }

    ///print normalized vector at each step of power iter
//    printf("  \n");
//    for (i=0; i<graph->number_of_nodes; i++){
//        printf("%f  ",row_norm[i]);
//    }
//    printf("  \n");
    return 0;
}

//check if the difference between two vectors is ~0
int check_difference(int height ,double *temp ,double *next){
    double difference, *pointer1 = NULL, *pointer2 = NULL;
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
int powerIteration(Graph* graph, Group* g_p, Pair* pair_p, Vector_double *row_sums_p){
    double *temp = NULL, *row_norm = NULL,  *vec = NULL, *max =NULL, numerator, max_v;
    int check, true=0, i=0; double value_without_c; double* vect_temp;
    max = &max_v;
    vec = (double *)malloc(graph->number_of_nodes*sizeof(double));
    /// using calloc to initialize to zero - important!
    row_norm = (double *)calloc(graph->number_of_nodes,sizeof(double));

    /// create random vector
    create_vec(g_p,graph->number_of_nodes, vec);

    ///print random vector
    for (i=0; i<graph->number_of_nodes; i++){
        printf("\n\n%f",vec[i]);
    }

    matrix_shift_C_new(graph, g_p, max, row_sums_p);
    ///print ||C|| = max column
    printf("\n\n %f \n\n",max_v);

    temp = vec;
    while (true == 0) {
        norm_vec(graph, g_p, temp, max_v, row_norm, row_sums_p);
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
    vec_mult_B_shifted(graph, g_p, pair_p->eigenvector , max_v,vect_temp, row_sums_p);

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


int calculate_dq(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p){
    int i=0, ind1=0,ind2=0; double* row_norm;
    long double cons=0.0, *comp2; double* comp;
    *dq_p=0.0;

    row_norm = (double*)calloc(graph->number_of_nodes,sizeof(double));
    int* indices_set;
    indices_set = (int*)malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, indices_set);

    int* Adj_indices_set;
    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set);

    ///step1 - calculate A *  s_vector - O(m)
    for (i=0; i<graph->adj_matrix->size; i++){
        if (Adj_indices_set[i]==1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            row_norm[ind1] += s_p[ind2];
            row_norm[ind2] += s_p[ind1];
        }
//        printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
    }
//    printf("\n\n%f  %f  %f  %f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);
//    printf("\n\n%f  %f  %f\n", rand_vec[0],rand_vec[1],rand_vec[2]);
//    printf("\n\n%d  %d  %d\n", graph->adj_matrix->row[0],graph->adj_matrix->row[1],graph->adj_matrix->row[2]);
//    printf("\n\n%d  %d  %d\n", graph->deg_vec->data[0],graph->deg_vec->data[1],graph->deg_vec->data[2]);
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step2 - to calculate Constant = s_vector * k^T - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(s_p[i])*(long double)(graph->deg_vec->data[i]);
    }
//    printf("\n%Lf  \\n", cons);

    ///step3 - multiply Constant (s_vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
    }
//    printf("\n\n%Lf  %Lf  %Lf\n", comp2[0],comp2[1],comp2[2]);

    ///step4 - combine 3 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step5 - deduct Row sums of B_hat matrix * Eigenvector  - O(n)
    comp = (double *)malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p->data[i]*s_p[i];
        row_norm[i] = row_norm[i] - comp[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

//    printf("\n\n%f  %f  %f  %f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);

    ///step6 - multiply the obtained vector by ST from the left  - O(n)
    for(i=0; i<graph->number_of_nodes;i++){
        *dq_p += row_norm[i]*s_p[i];
    }

    ///step7 - divide by 2M according to the original paper
//    *dq_p = *dq_p/(graph->M*2);
//    printf("\n  %f  \n",*dq_p);


    free(comp);
    free(comp2);
    free(indices_set);
    free(Adj_indices_set);
    return 0;
}