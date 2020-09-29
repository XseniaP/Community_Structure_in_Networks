/** Maximization module summary:
 *
 * this module implements modularity maximization technique by means of finding among the vertices the ones that , when
 * moved to the other group, will give the biggest increase in the modularity of the complete network;
 * each vertex is moved only once;
 *
 * The module implements the following Functions:
 * score_calc - calculates the vector of scores for all unmoved nodes in specific iteration
 * maximize - implements the whole maximization process by means of choosing and moving the vertex with
 * the highest score in the scores vector; the procedure is repeated until no further improvement can be made;
 * the time complexity is minimized by means of reworking the scores formula and then by decomposition of matrix B
 * and step-by-step multiplication;
 * */


#ifndef PROJECT_TOHNA_MAXIMIZATION_H
#define PROJECT_TOHNA_MAXIMIZATION_H

#include "Group_handler.h"
#include "Power_iter.h"

int maximize(Graph* graph,Group* g_p, int *s_p);
int score_calc(Graph* graph,Group*  g_p, int *s_p, long double *score, int *moved);

#endif

