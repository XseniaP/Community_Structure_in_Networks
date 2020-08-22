#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Modularity.h"
#include "Power_iter.h"
#include "Group_handler.h"

int produce_input_set(Vector_int* input_set);
int compute_s(Pair *pair_p, struct Vector_int* s_p);
int graph_for_input_set(Graph* graph ,Vector_int* input_set, Graph* graph_modified);
int divide_group_into_two(Graph graph ,int *input_set, struct SymMatrix *bg_hat_matrix_p , Pair *pair_p);
int correction();

#endif //PROJECT_TOHNA_ALGO2_H
