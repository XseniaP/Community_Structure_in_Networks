#include "fileHandler.h"
#include "Algo2.h"

int main(int argc,char* argv[]) {
    //new branch
    //declarations , initializations
    Graph new_graph = {0,0,NULL,NULL}; Vector_int deg_vec = {0,NULL};
    SymMatrix b_matrix = {0, NULL }; SymMatrix bg_hat_matrix = {0, NULL}; SymMatrix bg_matrix = {0, NULL };
    Pair pair = {0.0, NULL}; Vector_int input_set = {0,NULL}; Vector_double row_sums = {0,NULL}; SparseMatrix adj_matrix = {0, NULL,NULL, NULL};
    int i=0, a, size;Graph *myGraph_p;SymMatrix *b_matrix_p,*bg_matrix_p, *bg_hat_matrix_p;Pair* pair_p;Vector_int *input_set_p;Vector_double *row_sums_p;
    //Pointers
    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph;
    b_matrix_p = &b_matrix;bg_matrix_p = &bg_matrix; bg_hat_matrix_p = &bg_hat_matrix; pair_p = &pair; input_set_p = &input_set; row_sums_p=&row_sums;
    //check command line args
    if (argc<3){
        printf("Command line arguments missing\n");
        return 1;
    }
    //reading the file, creating the graph with Adj matrix and degree vector
    a = readFile(argv[1], myGraph_p);
    if (a){
        printf("Couldn't read the file\n");
        return 1;
    }

    //produce initial default set including all vertices
    input_set.size = myGraph_p->number_of_nodes;
    produce_input_set(input_set_p);

    //print input set indices
//    printf("\n%d", input_set.size);
//    for (i=0; i<input_set.size; i++){
//        printf("%c",'\n');
//        printf("%d", input_set.data[i] );
//    }


    //print adjacency matrix
    for (i=0; i<new_graph.M/2; i++){
        printf("%c",'\n');
        printf("%d %d", new_graph.adj_matrix->row[i],new_graph.adj_matrix->col[i]);
    }


    modularity_matrix(myGraph_p, b_matrix_p);
    matrix_bg(b_matrix_p, input_set_p, bg_matrix_p);

    size = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
//    printf("\n%d", size);
//    for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", bg_matrix_p->value[i] );
//    }

    modularity_hat_matrix(bg_matrix_p, bg_hat_matrix_p, row_sums_p);

    size = (int)(pow(bg_hat_matrix_p->col_row_n,2) + bg_hat_matrix_p->col_row_n)/2;
//    printf("\n%d", size);
//    for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", bg_hat_matrix_p->value[i] );
//    }
//    powerIteration(bg_hat_matrix_p ,pair_p, row_sums_p);
    powerIteration(bg_hat_matrix_p ,pair_p);


//    powerIteration(b_matrix_p ,pair_p);

//    divide_group_into_two(input_set_p, b_matrix_p , pair_p);



//    i=0;
//    int k[16] = {5,3,1,2,4,1,0,3,0,3,4,1,2,2,0,2};
//    FILE * f2 = NULL; int n;
//    f2 = fopen("graph_test2.in", "wb");
//    assert(f2 != NULL);
//    n = fwrite(&k, sizeof(int), 16, f2);
//    assert(n==16);
//    fclose(f2);



//int divide_a_network(Graph* graph,int **output_set){
//    int n=0, i=0; int **p_set; output_set = NULL;
//    n = graph->number_of_nodes;
//
//    // default set P
//    p_set = (int **)malloc(sizeof(int*));
//    p_set[0] = (int *)malloc(n*sizeof(int));
//    for (i=0; i<n;i++) {
//        p_set[0][i] = i;
//    }
//
//    // output set O is empty
//    output_set = (int **)malloc(sizeof(int*));
//    output_set[0][0]=-1;
//
//    //repeat until P is empty
//
//    while (p_set[0][0]!=-1){
//        temp = p_set[0];
//    }
//}


    free(input_set.data);
//    free(myGraph_p->data);
    free(myGraph_p->deg_vec->data);
    free(myGraph_p->adj_matrix->row);
    free(myGraph_p->adj_matrix->col);

    return 0;
}
