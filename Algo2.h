#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Modularity.h"
#include "Power_iter.h"
#include "Group_handler.h"
#include "fileHandler.h"

int divide_network(char* argv[], Set* output_p);
int graph_for_input_set(Graph* graph ,Vector_int* input_set, Graph* graph_modified);
int divide_group_into_two(Graph* graph, SymMatrix *b_matrix_p);
int compute_s(Pair *pair_p, struct Vector_int* s_p);
int improvement();

#endif //PROJECT_TOHNA_ALGO2_H
