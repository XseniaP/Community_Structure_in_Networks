
#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"

typedef struct Element
{
    void* data;
    struct Element* next;
}Element;

typedef struct Final_List_{
    int total_nodes;
    int total_groups;
    int* nodes_group_ind;
    double modularity;
}Final_List;

Element* createElement(size_t data_size_bytes);
int is_empty(Element* p_set_head);
Group* remove_graph_from_list(Element* p_set_head);
int add_group_to_element(Group* g_p, Element* o_set_head);
int add_group_to_final_set(Group* g_p, Element* some_set_head);
int count_size(Element* set_head);
int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p);



#endif //PROJECT_TOHNA_GROUP_HANDLER_H
