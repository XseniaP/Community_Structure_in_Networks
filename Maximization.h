#ifndef PROJECT_TOHNA_MAXIMIZATION_H
#define PROJECT_TOHNA_MAXIMIZATION_H

#include "Group_handler.h"
#include "fileHandler.h"
#include "Power_iter.h"

int maximize(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p);
int bs(Graph* graph,Group* g_p, int *s_p,double* bs_p);

#endif //PROJECT_TOHNA_MAXIMIZATION_H
