//
// Created by Ksenia Polonsky on 8/17/20.
//

#ifndef PROJECT_TOHNA_MODULARITY_H
#define PROJECT_TOHNA_MODULARITY_H
#include "structures.h"
#include <math.h>


int modularity_matrix(Graph *g, SymMatrix *b_matrix_p);
int matrix_bg(SymMatrix *b_matrix_p,Vector_int* input_set_p, SymMatrix *bg_matrix_p);
int modularity_hat_matrix(SymMatrix *bg_matrix_p,SymMatrix *bg_hat_matrix, Vector_double *row_sums_p);




#endif //PROJECT_TOHNA_MODULARITY_H
