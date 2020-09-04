

#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Power_iter.h"
#include "Group_handler.h"
#include "fileHandler.h"


int divide_network(char* argv[], int*** output_p);
int adj_ind_for_input_set(Graph* graph , Group* g);
int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2);
int compute_s(Pair *pair_p, int* s_p, int size);
int split_group_based_on_s(int* s_p, int size, Group* group1, Group* group2);



#endif //PROJECT_TOHNA_ALGO2_H
