#include "Algo2.h"

int produce_input_set(Vector_int* input_set){
    int i=0;
    input_set->data = (int *)malloc(input_set->size*sizeof(int));
    for (i=0; i<input_set->size; i++){
        input_set->data[i] = i;
    }
    return 0;
}

int compute_s(Pair *pair_p, struct Vector_int* s_p){
    int i=0;
    s_p->data = (int*)malloc(s_p->size * sizeof(int));
    for (i=0; i<s_p->size; i++){
        if (pair_p->eigenvector[i]>0){
            s_p->data[i] = 1;
        }
        else{
            s_p->data[i] = -1;
        }
    }
    return 0;
}

int graph_for_input_set(Graph* graph ,Vector_int* input_set, Graph* graph_modified){
    int i=0, j=0, index=0, count=0;
    graph_modified->number_of_nodes = input_set->size;
    graph_modified->deg_vec->size = input_set->size;
    graph_modified->deg_vec->data = (int*)malloc(graph_modified->number_of_nodes* sizeof(int));
    for(i=0;i<graph->adj_matrix->size;i++){
        for (j=0;j<input_set->size;j++) {
            if ((input_set->data[j] == graph->adj_matrix->row[i]) || (input_set->data[j] == graph->adj_matrix->col[i])) {
                index += 1;
            }
            if (index == 2){
                count +=1;
                index = 0;
                break;
            }
        }
    }

    graph_modified->adj_matrix->size = count;
    graph_modified->M = count*2;
    graph_modified->adj_matrix->row = (int*)malloc(count*sizeof(int));
    graph_modified->adj_matrix->col = (int*)malloc(count*sizeof(int));
    count = 0;
    for(i=0;i<graph->adj_matrix->size;i++){
        for (j=0;j<input_set->size;j++) {
            if ((input_set->data[j] == graph->adj_matrix->row[i]) || (input_set->data[j] == graph->adj_matrix->col[i])) {
                index += 1;
            }
            if (index == 2){
                graph->adj_matrix->row[count] = graph->adj_matrix->row[i];
                graph->adj_matrix->row[count] = graph->adj_matrix->col[i];
                index = 0;
                count+=1;
                break;
            }
        }
    }
//    for (i=0; i<input_set->size;i++){
//        index = input_set->data[i];
//        graph_modified->deg_vec->data[i] = graph->deg_vec->data[index];
//    }
return 0;
}

//int divide_group_into_two(Graph graph ,int *input_set, struct SymMatrix *bg_hat_matrix_p , Pair *pair_p){
//
//
//    return 0;
//}
