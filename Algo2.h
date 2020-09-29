
/** Algo2 module summary:
 *
 * this module divides graph (aka network) into the respective communities (indivisible sub-groups) by means of maxtrix
 * representation and the eigenvectors
 *
 * The module implements the following Functions:
 *
 * divide_network - receives the input file name and divides the graph into the respective communities
 * adj_for_g - marks which indices of the Adjacency matrix are relevant for specific sub-group g
 * divide_group_into_two - divides given network into two sub-groups which might or might not be divided further
 * compute_s - computes the binary vector of {-1,1} which marks each node affiliation with one of 2 groups
 * split_group_based_on_s - creates two groups out of 1 based on the binary s-vector
 * separate_singletons - extract the isolated nodes from the initial graph and writes them into the final set of indivisible groups
 *
 */

#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Maximization.h"
#include "fileHandler.h"
#include "safe_memory.h"


int divide_network(char* argv[]);
int adj_for_g(Graph* graph ,Group* g);
int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2, double *dq_p);
int compute_s(Pair *pair_p, int* s_p, int size);
int split_group_based_on_s(int* s_p, Graph* graph, Group* group1, Group* group2);
int separate_singletons(Graph *graph, Group *group, struct Group** stack);



#endif
