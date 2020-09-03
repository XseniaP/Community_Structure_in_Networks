
#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"

typedef struct Element {
    Graph graph;
    struct list *next;
} Element;

typedef struct list{
    Element* head;
    int size;
}List;

int create_list_with_graph(Graph* graph_p, List head);
int create_empty_list(List head);
int add_graph_to_list(Graph* graph_p,List tail);
Graph remove_graph_from_list(List head);
int is_empty(List head);

#endif //PROJECT_TOHNA_GROUP_HANDLER_H
