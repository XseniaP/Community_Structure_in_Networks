//
// Created by Ksenia Polonsky on 9/4/20.
//

#ifndef PROJECT_TOHNA_POWER_ITER_H
#define PROJECT_TOHNA_POWER_ITER_H
#include "structures.h"
#include <math.h>
#include <time.h>

int create_vec(Group* g, int size, double *vec);
int vec_mult_B_shifted(Graph* graph,Group* g_p, double *rand_vec, double max,double *row_norm,Vector_double *row_sums_p);
int norm_vec (Graph* graph,Group* g_p, double *rand_vec, double max, double *row_norm,Vector_double *row_sums_p);
int check_difference(int height ,double *temp ,double *next);
int powerIteration(Graph* graph, Group* g, Pair* pair_p, Vector_double *row_sums_p);
int matrix_shift_C_new(Graph* graph,Group* g, double* max_p, Vector_double *row_sums_p);
int indices_to_indices_set(Group* group, int *indices, int size, int* indices_set);
int calculate_dq(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p);

#endif //PROJECT_TOHNA_POWER_ITER_H
