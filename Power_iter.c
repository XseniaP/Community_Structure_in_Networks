
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

    //checking sum of the maximum column
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

    for (j = 0, i=2; j < count; j+=i, i++) {
        bg_hat_matrix_p->value[j] = bg_hat_matrix_p->value[j] + max;
    }
    return 0;
}

//multiply vector by symmetric shifted matrix B
int norm_vec (double *rand_vec, SymMatrix *b_matrix_p,double *row_norm){
    int i=0, j=0; double temp = 0, temp2=0;
    double *pointer2 = NULL, *pointer1 = NULL, *pointer3=NULL, *pointer4=NULL, *pointer5=NULL;
    pointer1 = rand_vec; pointer2 = &b_matrix_p->value[0]; pointer3 = &temp; pointer4 = &row_norm[0]; pointer5 = &temp2;

    for(i=0; i<b_matrix_p->col_row_n; i++) {
        for (j = 0; j < b_matrix_p->col_row_n; j++) {
            if (i>=j){
                *pointer3 += (*(pointer2 + (i*(i+1)/2 + j))) * (*(pointer1+j));
            }
            else{
                *pointer3 += (*(pointer2 + (j*(j+1)/2 + i))) * (*(pointer1+j));
            }

        }

        (*(pointer4 + i)) = *pointer3;
        *pointer5+=(*pointer3)*(*pointer3);
        temp=0;
    }

    pointer4 = &row_norm[0];
    temp = sqrt(temp2);
    for (i = 0; i < b_matrix_p->col_row_n; i++) {
        (*(pointer4 + i)) = (*(pointer4 + i))/temp;
    }
//    for (i=0; i<b_matrix_p->col_row_n; i++){
//        printf("\n\n%f", row_norm[i] );
//    }

    return 0;
}

//int norm_vec_improved_complexity (double *rand_vec, Graph *graph_p,Vector_double *row_sums_p,double max,double *row_norm, Vector_int *input_set_p){
//    Vector_double ax, kktx; double ktx;int i, size;
//    ax.data = (double*)calloc(row_sums_p->size,sizeof(double));
//    kktx.data = (double*)calloc(row_sums_p->size,sizeof(double));
//    ktx = 0.0;
//    size = (int)(graph_p->M/2);
//    //calculate Ax in O(m+n)
//    for (i=0;i<size;i++){
//        ax.data[graph_p->adj_matrix->col[i]] += rand_vec[graph_p->adj_matrix->row[i]];
//        ax.data[graph_p->adj_matrix->row[i]] += rand_vec[graph_p->adj_matrix->col[i]];
//    }
//    //calculate k(kt * x)/M   in O(n)
//    for(i=0;i<row_sums_p->size;i++){
//        ktx += (double)rand_vec[i] * (double)graph_p->deg_vec->data[i];
//    }
//    for(i=0;i<graph_p->deg_vec->size;i++){
//        ktx += (double)rand_vec[i] * (double)graph_p->deg_vec->data[i];
//    }
//
//
//    return 0;
//}

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

//power iteration which starts with random vector and matrix shift and returns the Pair structure with eigenvector and eigenvalue
//int powerIteration(SymMatrix *bg_hat_matrix_p ,Pair* pair_p, Vector_double *row_sums_p){
int powerIteration(SymMatrix *bg_hat_matrix_p ,Pair* pair_p){
    double *temp = NULL, *row_norm = NULL,  *vec = NULL, *max =NULL, value=0.0, denominator, numerator, max_v;
    int check, true=0, i=0;
    max = &max_v;
    vec = (double *)malloc(bg_hat_matrix_p->col_row_n*sizeof(double));
    row_norm = (double *)malloc(bg_hat_matrix_p->col_row_n*sizeof(double));

    create_vec(bg_hat_matrix_p->col_row_n, vec);
    //print random vector
    for (i=0; i<bg_hat_matrix_p->col_row_n; i++){
        printf("\n\n%f",vec[i]);
    }
    //print B[g] matrix
//    int count=0;
//    count = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
//    for (i=0; i<count; i++){
//        printf("\n\n%f", bg_matrix_p->value[i] );
//    }

    matrix_shift(bg_hat_matrix_p, max);

    //print shifted B[g] matrix
//    for (i=0; i<count; i++){
//        printf("\n\n%f", bg_matrix_p->value[i] );
//    }


    temp = vec;
    while (true == 0) {
        norm_vec(temp, bg_hat_matrix_p, row_norm);
        for (i=0; i<bg_hat_matrix_p->col_row_n; i++){
            printf("\n%f", row_norm[i] );
        }
        check=check_difference(bg_hat_matrix_p->col_row_n ,temp ,row_norm);
        if (check==0){
            free(temp);
            temp = row_norm;
            row_norm = (double *)malloc(bg_hat_matrix_p->col_row_n*sizeof(double));
        }
        else{
            free(temp);
            true=1;
        }
    }

    pair_p->eigenvector = row_norm;

    //find corresponding eigenvalue of the shifted matrix
    denominator=0.0, numerator = 0.0;
    for(i=0; i<bg_hat_matrix_p->col_row_n;i++){
        denominator+= pair_p->eigenvector[i]*pair_p->eigenvector[i];
    }

//    for(i=0; i<bg_hat_matrix_p->col_row_n;i++){
//        numerator =
//    }


    value =numerator/denominator;

    //deduct ||C|| to get leading eigenvalue of the original matrix


//    bg_matrix_p->value;


//    free(row_norm);
    return 0;
}
