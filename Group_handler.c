
#include "Group_handler.h"
#include "structures.h"


void push(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack){
    int i;
    struct Group* Element = (struct Group*)safe_malloc(sizeof(struct Group));

    Element->Adj_size = Adj_size;
    Element->group_size = group_size;
    Element->indices = (int*)safe_calloc(group_size,sizeof(int));

    for (i=0; i < group_size; i++){
        Element->indices[i] = indices[i];
    }
    Element->Adj_indices = (int*)safe_calloc(Adj_size,sizeof(int));
    for (i=0; i < Adj_size; i++){
        Element->Adj_indices[i] = Adj_indices[i];
    }

    Element->next = *stack;
    (*stack) = Element;
}

void pop(struct Group** stack){
    if(*stack != NULL){
        struct Group* tempPtr = *stack;
        *stack = (*stack)->next;
        free(tempPtr->indices);
        free(tempPtr->Adj_indices);
        free(tempPtr);
    }
}

Group* top(struct Group* stack){
    if(stack != NULL){
        return stack;
    }
    else{
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

