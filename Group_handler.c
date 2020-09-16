
#include "Group_handler.h"
#include "structures.h"
#include <math.h>

Node* createNode()
{
    Node* newNode = NULL;

    newNode =  (Node*)malloc(sizeof(Node));
    if(NULL == newNode)
    {
        printf("failed to allocate memory for the Node");
        return NULL;
    }
    newNode->data = NULL;
    newNode->next = NULL;
    return newNode;
}

int is_empty(Node* p_set_head){
    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
        return 1;
    }
    else{
        return 0;
    }
}

Group* pop_group(Node* p_set_head){
    Group *temp; Node* temp2;
    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
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
        *p_set_head = *p_set_head->next;
        return temp;
    }
}

int push_group(Group* g_p, Node* p_set_head, Node* new_node, Group* new_group){
    Node* temp; int i;
    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
        p_set_head->data = new_group;
        p_set_head->data->group_size = g_p->group_size;
        for(i=0; i<g_p->group_size; i++){
            p_set_head->data->indices[i] = g_p->indices[i];
        }
        p_set_head->data->Adj_size = g_p->Adj_size;
        for(i=0; i<g_p->Adj_size; i++){
            p_set_head->data->Adj_indices[i] = g_p->Adj_indices[i];
        }
        free(new_node);
        return 0;
    }
    else if ((p_set_head->data == NULL)&&(p_set_head->next != NULL)){
        printf("linked list element has inaccurate structure");
        return 1;
    }
    else{
        new_node->data = new_group;
        new_node->data->group_size = g_p->group_size;
        for(i=0; i<g_p->group_size; i++){
            new_node->data->indices[i] = g_p->indices[i];
        }
        new_node->data->Adj_size = g_p->Adj_size;
        for(i=0; i<g_p->Adj_size; i++){
            new_node->data->Adj_indices[i] = g_p->Adj_indices[i];
        }
        new_node->next = NULL;
        temp = p_set_head;
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = new_node;
        return 0;
    }
}

int add_group_to_final_cluster(Group* g_p, Final_List* final_cluster_p){
    int i;
    final_cluster_p->total_groups +=1;
    for (i=0;i<g_p->group_size;i++){
        final_cluster_p->nodes_group_ind[g_p->indices[i]] = final_cluster_p->total_groups;
    }
    free(g_p->indices);
    free(g_p->Adj_indices);
    return 0;
}

