#include "Algo2.h"

/// O(n)
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

/// O(m*n)
int adj_ind_for_input_set(Graph* graph ,Group* g){
    int i=0, j=0, index=0;

    for(i=0;i<graph->M/2;i++){
        for (j=0;j<graph->number_of_nodes;j++) {
            if ((g->indices[graph->adj_matrix->row[i]]==1) || (g->indices[graph->adj_matrix->col[i]]==1)) {
                index += 1;
            }
            if (index == 2) {
                g->Adj_indices[i] = 1;
                break;
            }
        }
        index = 0;
    }

    return 0;
}

int divide_group_into_two(Graph* graph, Group* g){
    ///declarations
    Pair pair = {0.0, NULL};Vector_double row_sums = {0,NULL};Vector_double *row_sums_p;Vector_int* s_p;
    struct Vector_int s ={0, NULL};
    ///pointers
    Pair* pair_p = &pair;row_sums_p=&row_sums; s_p = &s;

    row_sums.data = (double *)calloc(graph->number_of_nodes,sizeof(double));
    powerIteration(graph, g, pair_p, row_sums_p);
    compute_s(pair_p, s_p);

    if (pair_p->eigenvalue<=0){
        printf("network is non-dividable");
        return 1;
    }

    free(pair_p->eigenvector);
    return 0;
}

int divide_network(char* argv[], int*** output_p){
///declarations , initializations, pointers
    Graph new_graph = {NULL,0,0,NULL, NULL};Graph *myGraph_p;
    SparseMatrix adj_matrix = {0, NULL,NULL, NULL};Vector_int deg_vec = {0,NULL};
    Group g ={NULL,NULL};
    Group* g_p; g_p = &g;
    Element p_set ={NULL,NULL}, o_set ={NULL,NULL};
    Element *p_set_head, *o_set_head;

    int i=0, a, result;

    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph;
    p_set_head = &p_set; o_set_head = &o_set;


///reading the file, creating the graph with Adj matrix and degree vector
    a = readFile(argv[1], myGraph_p);
    if (a){
        printf("Couldn't read the file\n");
        return 1;
    }

    ///Allocations
    g.indices = (int *)malloc(myGraph_p->number_of_nodes*sizeof(int));
//    g.group_size = myGraph_p->number_of_nodes;
    for (i=0; i<myGraph_p->number_of_nodes;i++){
        g.indices[i]=i;
    }

//    g.indices = (int *)malloc(3*sizeof(int));
//    g.group_size = 3;
//    g.indices[0] = 0;
//    g.indices[1] = 2;
//    g.indices[2] = 4;


    g.Adj_indices = (int *)calloc(myGraph_p->M/2,sizeof(int));
//    g.Adj_size = myGraph_p->M/2;
    for (i=0; i<myGraph_p->M/2;i++){
        g.Adj_indices[i]=i;
    }

//    g.Adj_indices = (int *)calloc(3,sizeof(int));
//    g.Adj_size = 3;
//    g.Adj_indices[0] = 1;
//    g.Adj_indices[1] = 3;
//    g.Adj_indices[2] = 4;

///    print indices set indices
    for (i=0; i<new_graph.number_of_nodes; i++){
        printf("%c",'\n');
        printf("%d", g.indices[i]);
    }

///    print adjacency matrix
    for (i=0; i<new_graph.M/2; i++){
        printf("%c",'\n');
        printf("%d %d", new_graph.adj_matrix->row[i],new_graph.adj_matrix->col[i]);
    }

///    print degree vector
//    for (i=0; i<new_graph.number_of_nodes; i++){
//        printf("%c",'\n');
//        printf("%d", new_graph.deg_vec->data[i]);
//    }


///   meantime a placeholder with functions , later when groups are defined will be replaced with the ALGORITHM3 flow :
/// while P is not empty keep dividing
/// my graph pointer is assigned new graph every time (head from the LINKED LIST SET)

    ///creating P and O lists
//    p_set_head = createElement(sizeof(Group));
//    p_set_head->data = (void *)g_p;
//
//    o_set_head = createElement(sizeof(int**));
//
//    while (!is_empty(p_set_head)){
//        g_p = remove_graph_from_list(p_set_head);
//        result = divide_group_into_two(myGraph_p,g_p);
//        if (result ==1){
//            add_group_to_element(g_p, o_set_head);
//        }
//        else{
//            create_groups(s_p, groups);
//            if (groups[0]->number_of_nodes == 1)&(groups[1]->number_of_nodes == 1){
//                add_graph_to_list(groups[0], tail_o);
//                add_graph_to_list(groups[1], tail_o);
//            };
//            else if (groups[0]->number_of_nodes == 1){
//                add_graph_to_list(groups[0], tail_o);
//                add_graph_to_list(groups[1], tail_p);
//            };
//            else if (groups[1]->number_of_nodes == 1){
//                add_graph_to_list(groups[0], tail_p);
//                add_graph_to_list(groups[1],tail_o);
//            };
//            else {
//                add_graph_to_list(groups[0], tail_p);
//                add_graph_to_list(groups[1], tail_p);
//            }
//        }
//    }



    divide_group_into_two(myGraph_p, g_p);

//    adj_ind_for_input_set(myGraph_p ,g);

///create new Graph struct for the given set



    ///placeholder for the output
//    return o_head;

    ///free memory
//    free(myGraph_p->deg_vec->data);
//    free(myGraph_p->adj_matrix->row);
//    free(myGraph_p->adj_matrix->col);
//    free(myGraph_p->indices_set);
//    free(b_matrix.value);
//free(g.Adj_indices);
//free(g.indices);
    return 0;
}

