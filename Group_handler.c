
#include "Group_handler.h"
#include "structures.h"
#include <math.h>

Element* createElement(size_t data_size_bytes)
{
    Element* newNode = NULL;
    newNode =  malloc(sizeof(Element));/*always the same*/
    if(NULL == newNode)
    {
        printf("failed to allocate memory for the Node");
        return NULL;
    }
    newNode->data =  malloc(sizeof(Group));/*changes by input*/
    if(NULL == newNode->data)
    {
        printf("failed to allocate memory for the Node's data");
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
    Group *temp = NULL;
    int i;

    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
        printf("the set is empty, no groups to remove");
        return NULL;
    }

    if (p_set_head->next == NULL) {
        temp = p_set_head->data;

        p_set_head->data = NULL;
        return temp;

    } else {
        temp = p_set_head->data;
        *p_set_head = *p_set_head->next;
        return temp;

    }

}



void push(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack){
    struct Group* Element = (struct Group*)malloc(sizeof(struct Group));
    int i;
    Element->Adj_size = Adj_size;
    Element->group_size = group_size;
    Element->indices = (int*)malloc(group_size*sizeof(int));
    for (i=0; i < group_size; i++){
        Element->indices[i] = indices[i];
    }
    Element->Adj_indices = (int*)malloc(Adj_size*sizeof(int));
    for (i=0; i < Adj_size; i++){
        Element->Adj_indices[i] = Adj_indices[i];
    }


    Element->next = *stack;
    (*stack) = Element;
}

void pop(struct Group** stack){
    if(*stack != NULL){
//        printf("Element popped: %c\n",(*stack) -> data);
        struct Group* tempPtr = *stack;
        *stack = (*stack)->next;
        free(tempPtr->indices);
        free(tempPtr->Adj_indices);
        free(tempPtr);
    }
    else{
        printf("The stack is empty.\n");
    }
}

Group* top(struct Group* stack){
    if(stack != NULL){
//        printf("Element on top: %c\n", stack -> data);
        return stack;
    }
    else{
        printf("The stack is empty.\n");
        return NULL;
    }
}

int add_group_to_element(Group* g_p, Element* some_set_head, Element* next_el){
    Element temp;
    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
        free(some_set_head);

        *some_set_head = *next_el;
        return 0;
    }
    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
        printf("linked list element has inaccurate structure");
        return 1;
    }
    else{
        next_el->next = NULL;
        temp = *some_set_head;
        *some_set_head = *next_el;
        some_set_head->next = &temp;
        return 0;
    }
}

int add_group_to_final_set(Group* g_p, Element* some_set_head){
    Element temp; int i;

    printf("\n \n");
    for(i=0;i<g_p->group_size;i++){
        printf("%d  ",g_p->indices[i]);
        printf("\n");
    }

    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
        some_set_head->data = g_p->indices;
        return 0;
    }
    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
        printf("linked list element has inaccurate structure");
        return 1;
    }
    else{
        temp = *some_set_head;
        some_set_head->data = g_p->indices;
        some_set_head->next = &temp;
        return 0;
    }
}

int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p){
    int i;
    final_cluster_p->total_groups +=1;
    for (i=0;i<g_p->group_size;i++){
        final_cluster_p->nodes_group_ind[g_p->indices[i]] = final_cluster_p->total_groups;
    }
    return 0;
}

int count_size(Element* set_head){
    int cnt = 0;
    for (; set_head!=NULL; set_head = set_head->next)
        cnt++;
    return cnt;
}
