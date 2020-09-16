
#include "Group_handler.h"
#include "structures.h"
#include <math.h>


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


int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p){
    int i;
    final_cluster_p->total_groups +=1;
    for (i=0;i<g_p->group_size;i++){
        final_cluster_p->nodes_group_ind[g_p->indices[i]] = final_cluster_p->total_groups;
    }
    return 0;
}

