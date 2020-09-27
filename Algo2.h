
#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Group_handler.h"
#include "fileHandler.h"
#include "Maximization.h"


int divide_network(char* argv[]);
int adj_for_g(Graph* graph ,Group* g);
int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2, double *dq_p);
int compute_s(Pair *pair_p, int* s_p, int size);
int split_group_based_on_s(int* s_p, Graph* graph, Group* group1, Group* group2);
int separate_singletones(Graph *graph, Group* group, Final_List* final_cluster_p);



#endif //PROJECT_TOHNA_ALGO2_H
