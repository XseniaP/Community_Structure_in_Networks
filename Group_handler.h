
#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"

Element* createElement(size_t data_size_bytes);
int is_empty(Element* p_set_head);
Group * remove_graph_from_list(Element* p_set_head);
int add_group_to_element(Group* g_p, Element* o_set_head, Element* next);
int count_size(Element* set_head);
int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p);



void push(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack);
void pop(struct Group** stack);
Group* top(struct Group* stack);

#endif //PROJECT_TOHNA_GROUP_HANDLER_H
