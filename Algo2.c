#include "Algo2.h"

int produce_input_set(Vector_int* input_set){
    int i=0;
    input_set->data = (int *)malloc(input_set->size*sizeof(int));
    for (i=0; i<input_set->size; i++){
        input_set->data[i] = i;
    }
    return 0;
}

int compute_s(SymMatrix *b_matrix_p , Pair *pair_p, int* s){
    int i=0;
    s = NULL;
    s = (int*)malloc(b_matrix_p->col_row_n * sizeof(int));
    for (i=0; i<b_matrix_p->col_row_n; i++){
        if (pair_p->eigenvector[i]>0){
            s[i] = 1;
        }
        else{
            s[i] = -1;
        }
    }
    return 0;
}

//int divide_group_into_two(int *input_set, Matrix *b_matrix_p , Pair *pair_p){
//
//    }
//
//
//    return 0;
//}
