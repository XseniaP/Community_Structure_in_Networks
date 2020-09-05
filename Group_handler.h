
#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"

typedef struct Element
{
    void* data;
    struct Element* next;
}Element;

//typedef struct List{
//    Element* head;
//    int size;
//}List;

Element* createElement(size_t data_size_bytes);
int is_empty(Element* p_set_head);
Group* remove_graph_from_list(Element* p_set_head);
int add_group_to_element(Group* g_p, Element* o_set_head);
int add_group_to_final_set(Group* g_p, Element* some_set_head);



#endif //PROJECT_TOHNA_GROUP_HANDLER_H
