#ifndef PROJECT_TOHNA_MAXIMIZATION_H
#define PROJECT_TOHNA_MAXIMIZATION_H

#include "Group_handler.h"
#include "fileHandler.h"
#include "Power_iter.h"

int maximize(Graph* graph,Group* g_p, int *s_p);
int score_calc(Graph* graph,Group*  g_p, int *s_p, long double *score, int *moved);

#endif //PROJECT_TOHNA_MAXIMIZATION_H
