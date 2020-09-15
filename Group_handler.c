
#include "Group_handler.h"
#include "structures.h"
#include <math.h>

Element* createElement(size_t data_size_bytes)
{
    Element* newNode = NULL;
    Group g ={NULL,NULL};

    newNode =  malloc(sizeof(Element));/*always the same*/
    if(NULL == newNode)
    {
        printf("failed to allocate memory for the Node");
        return NULL;
    }
    newNode->data =  malloc(data_size_bytes);/*changes by input*/
    if(NULL == newNode->data)
    {
        printf("failed to allocate memory for the Node's data");
        return NULL;
    }

    newNode->data_value = g;
    newNode->next = NULL;
    return newNode;
}

int is_empty(Element* p_set_head){
    if ((p_set_head->data_value.indices == NULL)&&(p_set_head->data_value.Adj_indices == NULL)){
        return 1;
    }
    else{
        return 0;
    }
}

//Group* remove_graph_from_list(Element* p_set_head){
//    Group *temp;
//    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
//        printf("the set is empty, no groups to remove");
//        return NULL;
//    }
//    else if(p_set_head->next == NULL)
//    {
//        temp = p_set_head->data;
//        p_set_head->data = NULL;
//        p_set_head->next = NULL;
//        return temp;
//    }
//    else{
//        temp = p_set_head->data;
//        p_set_head->data = p_set_head->next->data;
//        p_set_head->next = p_set_head->next->next;
//        return temp;
//    }
//}
//
//int add_group_to_element(Group* g_p, Element* some_set_head){
//    Element temp;
//    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
//        some_set_head->data = g_p;
//        return 0;
//    }
//    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
//        printf("linked list element has inaccurate structure");
//        return 1;
//    }
//    else{
//        temp = *some_set_head;
//        some_set_head->data = g_p;
//        some_set_head->next = &temp;
//        return 0;
//    }
//}

Group remove_graph_from_list(Element* p_set_head, Group *temp){
    int i;
    //free(temp->Adj_indices);
    //free(temp->indices);
    temp->Adj_indices = NULL;
    temp->indices = NULL;
    temp->Adj_size = 0;
    temp->group_size = 0;
    if ((p_set_head->data == NULL)&&(p_set_head->next == NULL)){
        printf("the set is empty, no groups to remove");
        return *temp;
    }
    else if(p_set_head->next == NULL)
    {
        *temp = p_set_head->data_value;
        p_set_head->data = NULL;
        p_set_head->next = NULL;
        p_set_head->data_value.Adj_indices =NULL;
        p_set_head->data_value.Adj_size =0;
        p_set_head->data_value.indices =NULL;
        p_set_head->data_value.group_size =0;
        return *temp;
    }
    else{
//        *temp = p_set_head->data_value;
        temp->Adj_size = p_set_head->data_value.Adj_size;
        temp->group_size = p_set_head->data_value.group_size;
        temp->indices = (int*)malloc(p_set_head->data_value.group_size*sizeof(int));
        for (i=0; i<p_set_head->data_value.group_size; i++){
            temp->indices[i] = p_set_head->data_value.indices[i];
        }
        temp->Adj_indices = (int*)malloc(p_set_head->data_value.Adj_size*sizeof(int));
        for (i=0; i<p_set_head->data_value.Adj_size; i++){
            temp->Adj_indices[i] = p_set_head->data_value.Adj_indices[i];
        }

        p_set_head = p_set_head->next;
        p_set_head->next = p_set_head->next->next;
        return *temp;
    }
}

int add_group_to_element(Group* g_p, Element* some_set_head){
    Element temp;
    int i;
    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
        some_set_head->data = g_p;
        some_set_head->data_value.Adj_size = g_p->Adj_size;
        some_set_head->data_value.group_size = g_p->group_size;
        some_set_head->data_value.indices = (int*)malloc(g_p->group_size*sizeof(int));
        for (i=0; i<g_p->group_size; i++){
            some_set_head->data_value.indices[i] = g_p->indices[i];
        }
        some_set_head->data_value.Adj_indices = (int*)malloc(g_p->Adj_size*sizeof(int));
        for (i=0; i<g_p->Adj_size; i++){
            some_set_head->data_value.Adj_indices[i] = g_p->Adj_indices[i];
        }
        return 0;
    }
    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
        printf("linked list element has inaccurate structure");
        return 1;
    }
    else{
        temp = *some_set_head;
        some_set_head->data = g_p;
        some_set_head->data_value = *g_p;
        some_set_head->next = &temp;
        return 0;
    }
}






//int add_group_to_final_set(Group* g_p, Element* some_set_head){
//    Element temp; int i;
//
//    printf("\n \n");
//    for(i=0;i<g_p->group_size;i++){
//        printf("%d  ",g_p->indices[i]);
//        printf("\n");
//    }
//
//    if ((some_set_head->data == NULL)&&(some_set_head->next == NULL)){
//        some_set_head->data = g_p->indices;
//        return 0;
//    }
//    else if ((some_set_head->data == NULL)&&(some_set_head->next != NULL)){
//        printf("linked list element has inaccurate structure");
//        return 1;
//    }
//    else{
//        temp = *some_set_head;
//        some_set_head->data = g_p->indices;
//        some_set_head->next = &temp;
//        return 0;
//    }
//}

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

int count_size(Element* set_head){
    int cnt = 0;
    for (; set_head!=NULL; set_head = set_head->next)
        cnt++;
    return cnt;
}
