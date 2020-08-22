#include "Algo2.h"

int produce_input_set(Vector_int* input_set){
    int i=0;
    input_set->data = (int *)malloc(input_set->size*sizeof(int));
    for (i=0; i<input_set->size; i++){
        input_set->data[i] = i;
    }
    return 0;
}

int compute_s(Pair *pair_p, struct Vector_int* s_p){
    int i=0;
    s_p->data = (int*)malloc(s_p->size * sizeof(int));
    for (i=0; i<s_p->size; i++){
        if (pair_p->eigenvector[i]>0){
            s_p->data[i] = 1;
        }
        else{
            s_p->data[i] = -1;
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
