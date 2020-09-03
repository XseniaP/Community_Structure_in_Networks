
#ifndef PROJECT_TOHNA_POWER_ITER_NEW_H
#define PROJECT_TOHNA_POWER_ITER_NEW_H

#include "structures.h"
#include <math.h>
#include <time.h>

int create_vec(int size, double *vec);
int vec_mult_B(Graph* graph, double *rand_vec, double max,double *row_norm,Vector_double *row_sums_p);
int norm_vec (Graph* graph, double *rand_vec, double max, double *row_norm,Vector_double *row_sums_p);
int check_difference(int height ,double *temp ,double *next);
int powerIteration(Graph* graph,Pair* pair_p, Vector_double *row_sums_p);
int matrix_shift_C_new(Graph* graph, double* max_p, Vector_double *row_sums_p);

#endif //PROJECT_TOHNA_POWER_ITER_NEW_H
