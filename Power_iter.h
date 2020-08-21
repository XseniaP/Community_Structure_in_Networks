
#ifndef PROJECT_TOHNA_POWER_ITER_H
#define PROJECT_TOHNA_POWER_ITER_H
#include "structures.h"
#include <math.h>
#include <time.h>

int create_vec(int size, double *vec);
int matrix_shift(SymMatrix *b_matrix_p);
int norm_vec (double *rand_vec, SymMatrix *b_matrix_p, double *row_norm);
int check_difference(int height ,double *temp ,double *next);
int powerIteration(SymMatrix *bg_matrix_p ,Pair* pair_p);


#endif //PROJECT_TOHNA_POWER_ITER_H
