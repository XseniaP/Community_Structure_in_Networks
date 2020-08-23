
#include "Power_iter.h"

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

//add ||C|| (sum of max column) to diagonal elements of symmetric matrix B
int matrix_shift(SymMatrix *bg_hat_matrix_p, double* max_p){
    int i=0, j=0,count=0; double c_norm=0, max=0;

    ///checking sum of the maximum column - O(n^2)
    for (j=0; j<bg_hat_matrix_p->col_row_n; j++){
        c_norm=0;
        for (i=0; i<bg_hat_matrix_p->col_row_n;i++){
            if (i>=j){
                c_norm+= fabs(bg_hat_matrix_p->value[i*(i+1)/2 + j]);
            }
            else{
                c_norm+= fabs(bg_hat_matrix_p->value[j*(j+1)/2 + i]);
            }
        }
        if (c_norm>max){
            max = c_norm;
        }
    }
//    printf("\n\n%f", max);
    *max_p = max;
    //matrix shifting using max_column_sum
    count = (int)(pow(bg_hat_matrix_p->col_row_n,2) + bg_hat_matrix_p->col_row_n)/2;
///adding sum of the max column to the diagonal - O(n)
    for (j = 0, i=2; j < count; j+=i, i++) {
        bg_hat_matrix_p->value[j] = bg_hat_matrix_p->value[j] + max;
//        printf("\n\n%f\n", bg_hat_matrix_p->value[j]);
    }
    return 0;
}

//multiply vector by symmetric shifted matrix B
int norm_vec (Graph* graph, double *rand_vec, double max,double *row_norm){
    int i=0, ind1=0,ind2=0;
    double cons=0.0, *comp2, *comp3, sum=0.0;

    ///step1 - calculate A * random vector - O(M)
    for (i=0; i<graph->M/2; i++){
        ind1 = graph->adj_matrix->row[i];
        ind2 = graph->adj_matrix->col[i];
        row_norm[ind1] += rand_vec[ind2];
        row_norm[ind2] += rand_vec[ind1];
    }

    ///step2 - to calculate Constant = Random vector * k^T - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=rand_vec[i]*graph->deg_vec->data[i];
    }

    ///step3 - multiply Constant (Random vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (double*)malloc(graph->number_of_nodes* sizeof(double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp2[i] = cons*graph->deg_vec->data[i]/graph->M;
    }

    ///step4 - random vector * ||C|| (matrix shift max column sum) - O(n)
    comp3 = (double*)malloc(graph->number_of_nodes* sizeof(double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp3[i] = max*rand_vec[i];
    }

    ///step5 - combine 4 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-comp2[i]+comp3[i];
        sum +=pow(row_norm[i],2);
    }

    ///step6 - normalize - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]/pow(sum,0.5);
    }

    ///print normalized vector at each step of power iter
//    for (i=0; i<graph->number_of_nodes; i++){
//        printf("%f\n",row_norm[i]);
//    }

    free(comp2);
    free(comp3);
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
int powerIteration(Graph* graph,SymMatrix *bg_hat_matrix_p ,Pair* pair_p){
    double *temp = NULL, *row_norm = NULL,  *vec = NULL, *max =NULL, value=0.0, denominator, numerator, max_v;
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

    ///print B_hat[g] matrix
//    int count=0;
//    count = (int)(pow(bg_hat_matrix_p->col_row_n,2) + bg_hat_matrix_p->col_row_n)/2;
//    for (i=0; i<count; i++){
//        printf("\n\n%f", bg_hat_matrix_p->value[i] );
//    }

    matrix_shift(bg_hat_matrix_p, max);
    ///print ||C|| = max column
    printf("\n\n %f \n\n",max_v);

    ///print shifted B[g] matrix
//    for (i=0; i<count; i++){
//        printf("\n\n%f", bg_hat_matrix_p->value[i] );
//    }


    temp = vec;
    while (true == 0) {
        norm_vec(graph,temp, max_v, row_norm);
//        for (i=0; i<bg_hat_matrix_p->col_row_n; i++){
//            printf("\n%f", row_norm[i] );
//        }
        check=check_difference(bg_hat_matrix_p->col_row_n ,temp ,row_norm);
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

    ///find corresponding eigenvalue of the shifted matrix
    denominator=0.0, numerator = 0.0;
    ///calculate eigenvector * eigenvector O(n)
    for(i=0; i<bg_hat_matrix_p->col_row_n;i++){
        denominator+= pair_p->eigenvector[i]*pair_p->eigenvector[i];
    }

    ///calculate B_hat shifted * eigenvector O(n^2) - CAN BE IMPROVED USING A - kk/m + IC
    vect_temp = (double *)malloc(bg_hat_matrix_p->col_row_n*sizeof(double));
    for(i=0; i<bg_hat_matrix_p->col_row_n;i++){
        sum=0;
        for (j = 0; j < bg_hat_matrix_p->col_row_n; j++) {
            if (i>=j){
                sum += bg_hat_matrix_p->value[i*(i+1)/2 + j] * pair_p->eigenvector[j];
            }
            else{
                sum += bg_hat_matrix_p->value[j*(j+1)/2 + i] * pair_p->eigenvector[j];
            }
        }
        vect_temp[i] = sum;
//        printf("\n\n %f \n",vect_temp[i]);
    }
///dot product of eigenvector and vector with the results from B_hat shifted * eigenvector - O(n)
    for(i=0; i<bg_hat_matrix_p->col_row_n;i++){
        numerator+= vect_temp[i]*pair_p->eigenvector[i];
    }

    value =numerator/denominator;

///deduct ||C|| to get leading eigenvalue of the original matrix O(1)
//    printf("\n\n%f \n", value);
    value_without_c = value - max_v;
    pair_p->eigenvalue = value_without_c;

//    printf("\n\n%f \n", pair_p->eigenvalue);

//    free(row_norm);
    return 0;
}
