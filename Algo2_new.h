
#ifndef PROJECT_TOHNA_ALGO2_NEW_H
#define PROJECT_TOHNA_ALGO2_NEW_H
#include "Power_iter_new.h"
#include "Group_handler.h"
#include "fileHandler.h"


int divide_network(char* argv[], Set* output_p);
int graph_for_input_set(Graph* graph ,Vector_int* input_set, Graph* graph_modified);
int divide_group_into_two(Graph* graph);
int compute_s(Pair *pair_p, struct Vector_int* s_p);
int create_groups(struct Vector_int* s_p, Graph** groups);

#endif //PROJECT_TOHNA_ALGO2_NEW_H
