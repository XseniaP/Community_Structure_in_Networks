#ifndef PROJECT_TOHNA_ALGO2_H
#define PROJECT_TOHNA_ALGO2_H
#include "Modularity.h"
#include "Power_iter.h"
#include "Group_handler.h"

int compute_s(Pair *pair_p, struct Vector_int* s_p);
int correction();
int divide_group_into_two(int *input_set, SymMatrix *b , Pair *pair);
int produce_input_set(Vector_int* input_set);

#endif //PROJECT_TOHNA_ALGO2_H
