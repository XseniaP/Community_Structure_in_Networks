
#include "Group_handler.h"
#include "structures.h"
#include <math.h>

Element* createElement(size_t data_size_bytes)
{
    Element* newNode = NULL;

    newNode =  malloc(sizeof(Element));/*always the same*/
    if(NULL == newNode)
    {
        return NULL;
    }
    newNode->data =  malloc(data_size_bytes);/*changes by input*/
    if(NULL == newNode->data)
    {
        printf("failed to allocate memory for the Node");
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
}

int is_empty(Element* p_set_head){
    if (p_set_head->data == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

Group* remove_graph_from_list(Element* p_set_head){
    Group *temp;
    if (p_set_head->data == NULL){
        printf("the set is empty, no groups to remove");
        return NULL;
    }
    else if(p_set_head->next == NULL)
    {
        temp = p_set_head->data;
        p_set_head->data = NULL;
        p_set_head->next = NULL;
        return temp;
    }
    else{
        temp = p_set_head->data;
        p_set_head->data = p_set_head->next->data;
        p_set_head->next = p_set_head->next->next;
        return temp;
    }
}

int add_group_to_element(Group* g_p, Element* some_set_head){
    Element temp;
    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
        some_set_head->data = g_p;
        return 0;
    }
    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
        printf("linked list element has inaccurate structure");
        return 1;
    }
    else{
        temp = *some_set_head;
        some_set_head->data = g_p;
        some_set_head->next = &temp;
        return 0;
    }
}
