#include "Algo2.h"

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
    int i=0, j=0,v=0, index=0, count=0;

    graph_modified->number_of_nodes = input_set->size;
    graph_modified->indices_set = (int*)malloc(graph_modified->number_of_nodes* sizeof(int));
    graph_modified->indices_set = input_set->data;

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
        index = 0;
    }

    graph_modified->adj_matrix->size = count;
    graph_modified->adj_matrix->row = (int*)malloc(count*sizeof(int));
    graph_modified->adj_matrix->col = (int*)malloc(count*sizeof(int));
    count = 0;

    for(i=0;i<graph->adj_matrix->size;i++){
        for (j=0;j<input_set->size;j++) {
            if ((input_set->data[j] == graph->adj_matrix->row[i]) || (input_set->data[j] == graph->adj_matrix->col[i])) {
                index += 1;
            }
            if (index == 2){
                v =graph->adj_matrix->row[i];
                graph_modified->adj_matrix->row[count] = graph->adj_matrix->row[i];
                v =graph->adj_matrix->col[i];
                graph_modified->adj_matrix->col[count] = graph->adj_matrix->col[i];
                index = 0;
                count+=1;
                break;
            }
        }
        index = 0;
    }
    graph_modified->indices_set=input_set->data;
    graph_modified->M = graph->M;
    ///update degree vector based on the relevant indices
    for (i=0; i<graph_modified->number_of_nodes;i++){
        index = input_set->data[i];
        graph_modified->deg_vec->data[i] = graph->deg_vec->data[index];
    }
return 0;
}

int divide_group_into_two(Graph* graph){
    ///declarations
    SymMatrix bg_matrix = {0, NULL }; SymMatrix bg_hat_matrix = {0, NULL};
    Pair pair = {0.0, NULL};Vector_double row_sums = {0,NULL};Vector_double *row_sums_p;Vector_int* s_p;
    struct Vector_int s ={0, NULL};
    int size =0, i=0;
    ///pointers
    SymMatrix* bg_matrix_p = &bg_matrix; SymMatrix* bg_hat_matrix_p = &bg_hat_matrix;
    Pair* pair_p = &pair;row_sums_p=&row_sums; s_p = &s;
    ///calculate B matrix and row_sums for [g] based on its Graph
    matrix_bg(graph,bg_matrix_p);

    ///print B[g] matrix
//    size = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
//    printf("\n%d", size);
//    for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", bg_matrix_p->value[i] );
//    }

    ///build B_hat matrix and run power iterations to return eigenPair: vector and value
    modularity_hat_matrix(bg_matrix_p, bg_hat_matrix_p, row_sums_p);
//    size = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
//    printf("\n%d", size);
//    for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", bg_hat_matrix_p->value[i] );
//    }


    powerIteration(graph, bg_hat_matrix_p ,pair_p, row_sums_p);
    compute_s(pair_p, s_p);

    if (pair_p->eigenvalue<=0){
        printf("network is non-dividable");
    }

    return 0;
}

int divide_network(char* argv[], Set* output_p){
///declarations , initializations
    Graph new_graph = {NULL,0,0,NULL, NULL};Graph *myGraph_p;
    Graph graph_modified = {NULL,0,0,NULL, NULL}; Graph* graph_modified_p = &graph_modified;
    SparseMatrix adj_matrix = {0, NULL,NULL, NULL}, adj_matrix2={0,NULL,NULL,NULL};Vector_int deg_vec = {0,NULL}, deg_vec2={0,NULL};
    Vector_int input_set ={0,NULL};Vector_int* input_set_p;
    SymMatrix *bg_matrix_p; SymMatrix bg_matrix = {0, NULL };
    int i=0, a; int size;

///Pointers
    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; graph_modified.deg_vec = &deg_vec2;graph_modified.adj_matrix = &adj_matrix2; myGraph_p = &new_graph;input_set_p=&input_set;
    bg_matrix_p = &bg_matrix;
///reading the file, creating the graph with Adj matrix and degree vector
    a = readFile(argv[1], myGraph_p);
    if (a){
        printf("Couldn't read the file\n");
        return 1;
    }

///    print indices set indices
//    for (i=0; i<new_graph.number_of_nodes; i++){
//        printf("%c",'\n');
//        printf("%d", new_graph.indices_set[i]);
//    }

///    print adjacency matrix
//    for (i=0; i<new_graph.M/2; i++){
//        printf("%c",'\n');
//        printf("%d %d", new_graph.adj_matrix->row[i],new_graph.adj_matrix->col[i]);
//    }


///    print degree vector
//    for (i=0; i<new_graph.number_of_nodes; i++){
//        printf("%c",'\n');
//        printf("%d", new_graph.deg_vec->data[i]);
//    }

///    calculate matrix B only once to get out of it rum_sums for further calculations
//    modularity_matrix(myGraph_p, b_matrix_p);

///   print B matrix
//    size = (int)(pow(b_matrix_p->col_row_n,2) + b_matrix_p->col_row_n)/2;
//     for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", b_matrix_p->value[i]);
//    }

///   meantime a placeholder with functions , later when groups are defined will be replaced with the ALGORITHM3 flow :
/// while P is not empty keep dividing
/// my graph pointer is assigned new graph every time (head from the LINKED LIST SET)
//    input_set.data = (int*)malloc(3*sizeof(int));
//    for (i=0; i<3;i++){
//        input_set.data[i]=i;
//    }
//    input_set.size=3;
//    graph_for_input_set(myGraph_p ,input_set_p, graph_modified_p);
//    divide_group_into_two(graph_modified_p, b_matrix_p);
    divide_group_into_two(myGraph_p);

///create new Graph struct for the given set

//    graph_for_input_set(graph ,input_set, graph_modified_p);


    ///placeholder for the output
    output_p->indices_set = new_graph.indices_set;

    ///free memory
//    free(myGraph_p->deg_vec->data);
//    free(myGraph_p->adj_matrix->row);
//    free(myGraph_p->adj_matrix->col);
//    free(myGraph_p->indices_set);
//    free(b_matrix.value);

    return 0;
}

