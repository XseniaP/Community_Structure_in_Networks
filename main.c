#include "Algo2.h"
#include "structures.h"

int main(int argc,char* argv[]) {
    int** output={NULL}; int*** output_p;
    output_p = &output;
///check command line args
    if (argc<3){
        printf("Command line arguments missing\n");
        return 1;
    }
    divide_network(argv, output_p);

//    free(output.indices_set);
        return 0;

//    Vector_int deg_vec = {0,NULL};
//    SymMatrix b_matrix = {0, NULL }; SymMatrix bg_hat_matrix = {0, NULL}; SymMatrix bg_matrix = {0, NULL };
//    Pair pair = {0.0, NULL}; Vector_double row_sums = {0,NULL}; SparseMatrix adj_matrix = {0, NULL,NULL, NULL};
//    Vector_int s ={0,NULL};
//    int i=0, a, size;Graph *myGraph_p;SymMatrix *b_matrix_p,*bg_matrix_p, *bg_hat_matrix_p;Pair* pair_p;Vector_double *row_sums_p; Vector_int* s_p;
////Pointers
//    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph;
//    b_matrix_p = &b_matrix;bg_matrix_p = &bg_matrix; bg_hat_matrix_p = &bg_hat_matrix; pair_p = &pair; row_sums_p=&row_sums;s_p = &s;


///    matrix_bg(b_matrix_p, input_set_p, bg_matrix_p);
//
//    size = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
//    printf("\n%d", size);
//    for (i=0; i<size; i++){
//        printf("%c",'\n');
//        printf("%f", bg_matrix_p->value[i] );
//    }
//
//    modularity_hat_matrix(bg_matrix_p, bg_hat_matrix_p, row_sums_p);
//
//    size = (int)(pow(bg_hat_matrix_p->col_row_n,2) + bg_hat_matrix_p->col_row_n)/2;
////    printf("\n%d", size);
////    for (i=0; i<size; i++){
////        printf("%c",'\n');
////        printf("%f", bg_hat_matrix_p->value[i] );
////    }
////    powerIteration(bg_hat_matrix_p ,pair_p, row_sums_p);
//    powerIteration(bg_hat_matrix_p ,pair_p);
//    if (pair_p->eigenvalue<=0) printf("the group is non-dividable");
//    s_p->size = bg_hat_matrix_p->col_row_n;
//    compute_s(pair_p,s_p);
////    for (i=0;i<bg_hat_matrix_p->col_row_n;i++){
////        printf("\n\n %d \n",s_p->data[i]);
////    }
//
////    powerIteration(b_matrix_p ,pair_p);
//
////    divide_group_into_two(input_set_p, b_matrix_p , pair_p);
//
//
////    create new file with the nodes
////    i=0;
////    int k[16] = {5,3,1,2,4,1,0,3,0,3,4,1,2,2,0,2};
////    FILE * f2 = NULL; int n;
////    f2 = fopen("graph_test2.in", "wb");
////    assert(f2 != NULL);
////    n = fwrite(&k, sizeof(int), 16, f2);
////    assert(n==16);
////    fclose(f2);
//
//
//
////int divide_a_network(Graph* graph,int **output_set){
////    int n=0, i=0; int **p_set; output_set = NULL;
////    n = graph->number_of_nodes;
////
////    // default set P
////    p_set = (int **)malloc(sizeof(int*));
////    p_set[0] = (int *)malloc(n*sizeof(int));
////    for (i=0; i<n;i++) {
////        p_set[0][i] = i;
////    }
////
////    // output set O is empty
////    output_set = (int **)malloc(sizeof(int*));
////    output_set[0][0]=-1;
////
////    //repeat until P is empty
////
////    while (p_set[0][0]!=-1){
////        temp = p_set[0];
////    }
////}

}
