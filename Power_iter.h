
#ifndef PROJECT_TOHNA_POWER_ITER_H
#define PROJECT_TOHNA_POWER_ITER_H
#include "structures.h"
#include <math.h>
#include <time.h>

int create_vec(int size, double *vec);
int matrix_shift(SymMatrix *b_matrix_p,double* max);
int norm_vec (Graph* graph, double *rand_vec, double max, double *row_norm);
//int norm_vec_improved_complexity (double *rand_vec, Graph *graph_p,Vector_double *row_sums_p,double max,double *row_norm, Vector_int *input_set_p);
int check_difference(int height ,double *temp ,double *next);
//int powerIteration(SymMatrix *bg_matrix_p ,Pair* pair_p, Vector_double *row_sums_p);
int powerIteration(Graph* graph,SymMatrix *bg_hat_matrix_p ,Pair* pair_p);


#endif //PROJECT_TOHNA_POWER_ITER_H
