

#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Power_iter.h"
#include "Group_handler.h"
#include "fileHandler.h"


int divide_network(char* argv[], int*** output_p);
int adj_ind_for_input_set(Graph* graph , Group* g);
int divide_group_into_two(Graph* graph, Group* g);
int compute_s(Pair *pair_p, struct Vector_int* s_p);
int create_groups(struct Vector_int* s_p, Graph** groups);


#endif //PROJECT_TOHNA_ALGO2_H
