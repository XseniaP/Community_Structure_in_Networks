
#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"

int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p);
void push(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack);
void pop(struct Group** stack);
Group* top(struct Group* stack);

#endif
