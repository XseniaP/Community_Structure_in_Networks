#include "Algo2.h"

/// O(n)
int compute_s(Pair *pair_p, int* s_p, int size){
    int i=0;
    for (i=0; i<size; i++){
        if(pair_p->eigenvector[i]==0.0){
            s_p[i] = 0;
        }
        else if (IS_POSITIVE(pair_p->eigenvector[i])){
            s_p[i] = 1;
        }
        else{
            s_p[i] = -1;
        }
    }
    return 0;
}

/// O(m*n)
int adj_for_g(Graph* graph ,Group* g){
    int i, j, count1=0,count2=0;
    for(i=0;i<graph->M/2;i++) {
        for (j = 0; j < g->group_size; j++) {
            if ((g->indices[j] == graph->adj_matrix->row[i])||(g->indices[j] == graph->adj_matrix->col[i])) {
                count1 += 1;
            }
            if (count1 == 2) {
                count2 += 1;
                break;
            }
        }
        count1 = 0;
    }
    g->Adj_size = count2;
    g->Adj_indices = (int*)malloc(g->Adj_size* sizeof(int));

    count1=0,count2=0;
    for(i=0;i<graph->M/2;i++) {
        for (j = 0; j < g->group_size; j++) {
            if ((g->indices[j] == graph->adj_matrix->row[i])||(g->indices[j] == graph->adj_matrix->col[i])) {
                count1 += 1;
            }
            if (count1 == 2) {
                g->Adj_indices[count2] = i;
                count2 += 1;
                break;
            }
        }
        count1 = 0;
    }

    return 0;
}

int split_group_based_on_s(int *s_p, Graph *graph, Group* group1, Group* group2){
    int i,count1=0, count2=0;

    for (i=0; i<graph->number_of_nodes; i++){
            if(s_p[i]==1){
                count1+=1;
            }
            else if(s_p[i]==(-1)){
                count2+=1;
            }
    }
    group1->indices = (int*)calloc(count1,sizeof(int));
    group1->group_size = count1;
    group2->indices = (int*)calloc(count2,sizeof(int));
    group2->group_size = count2;
//    for (i=0; i<graph->number_of_nodes; i++){
//        printf("%d ", s_p[i]);
//    }
//    printf("\n ");
    count1=0; count2=0;
    for (i=0; i<graph->number_of_nodes; i++){
        if(s_p[i]==1){
            group1->indices[count1]=i;
//            printf("gr1  %d  ",i);
            count1+=1;
        }
        else if(s_p[i]==(-1)){
            group2->indices[count2]=i;
//            printf("gr2  %d  ",i);
            count2+=1;
        }
    }
    adj_for_g(graph ,group1);
    adj_for_g(graph ,group2);

//    printf("\n");
    return 0;
}


int separate_singletones(Graph *graph, Group* group, Final_List* final_cluster_p){
    int i, count = 0;
    for (i=0; i<graph->number_of_nodes; i++){
        if (IS_POSITIVE(graph->deg_vec->data[i])){
            count+=1;
        }
    }
    group->group_size = count;
    free(group->indices);
    group->indices = (int*)malloc(group->group_size* sizeof(int));
    count = 0;
    for (i=0; i<graph->number_of_nodes; i++){
        if (IS_POSITIVE(graph->deg_vec->data[i])){
            group->indices[count] = i;
            count+=1;
        }
        else{
            final_cluster_p->total_groups+=1;
            final_cluster_p->nodes_group_ind[i] = final_cluster_p->total_groups;
        }
    }
    return 0;
}

int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2, double *dq_p){
    ///declarations
    Pair pair = {0.0, NULL};Vector_double row_sums = {0,NULL};Vector_double *row_sums_p;
    int* s_p;
    ///pointers
    Pair* pair_p = &pair;row_sums_p=&row_sums;
 //   int i, count1=0, count2=0;

    row_sums.data = (double *)calloc(graph->number_of_nodes,sizeof(double));
    powerIteration(graph, g, pair_p, row_sums_p);

    s_p = (int*)malloc(graph->number_of_nodes * sizeof(int));
    compute_s(pair_p, s_p, graph->number_of_nodes);

//    printf("\n");
//    for (i=0; i<graph->number_of_nodes; i++){
//        printf("%f  ", row_sums_p->data[i]);
//    }
//    printf("\n");

//    calculate_dq(graph, g, s_p, row_sums_p, dq_p);

    ///    call for maximization
    maximize(graph, g, s_p);

    calculate_dq(graph, g, s_p, row_sums_p, dq_p);

    if (!IS_POSITIVE(pair_p->eigenvalue)){
        printf("network is non-dividable");
        free(pair_p->eigenvector);
        free(row_sums.data);
        free(s_p);
        return 1;
    }
    else if (!IS_POSITIVE(*dq_p)){
        printf("%f  network is non-dividable", *dq_p);
        free(pair_p->eigenvector);
        free(row_sums.data);
        free(s_p);
        return 1;
    }
    else{
        split_group_based_on_s(s_p, graph, g1, g2);
        free(pair_p->eigenvector);
        free(row_sums.data);
        free(s_p);
        return 0;
    }

//    free(pair_p->eigenvector);
//    return 0;
}

int divide_network(char* argv[], int*** output_p){
///declarations , initializations, pointers
    Graph new_graph = {0,0,NULL,NULL};Graph *myGraph_p;
    Final_List final_cluster = {0, 0,NULL,0.0};
    SparseMatrix adj_matrix = {0, NULL,NULL};Vector_int deg_vec = {0,NULL};
    Group g ={NULL,0,NULL,0,NULL};Group g1 ={NULL,0,NULL,0,NULL};Group g2 ={NULL,0,NULL,0,NULL};
    Group *g_p, *g1_p, *g2_p;g_p = &g;g1_p = &g1; g2_p = &g2;
    Final_List *final_cluster_p;
    double *dq_p; double dq;
    struct Group* root;

    int i=0, a, result;

    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph; final_cluster_p = &final_cluster;
     dq_p = &dq;


///reading the file, creating the graph with Adj matrix and degree vector
    a = readFile(argv[1], myGraph_p);
    if (a){
        printf("Couldn't read the file\n");
        return 1;
    }

    ///Initiate default group g of initial full graph
    g.indices = (int *)malloc(myGraph_p->number_of_nodes*sizeof(int));
    g.group_size = myGraph_p->number_of_nodes;
    for (i=0; i<myGraph_p->number_of_nodes;i++){
            g.indices[i] = i;
    }

    ///Initiate Adj matrix indices for default g
    g.Adj_indices = (int *)calloc(myGraph_p->M/2,sizeof(int));
    g.Adj_size = myGraph_p->M/2;
    for (i=0; i<myGraph_p->M/2;i++){
        g.Adj_indices[i]=i;
    }

///    print indices in the default g
//    printf("\n------------------------------------\n");
//    printf("Printing indices of the group");
//    printf("\n------------------------------------\n");
//    for (i=0; i<new_graph.number_of_nodes; i++){
//        printf("%c",'\n');
//        printf("%d", g.indices[i]);
//    }

///    print full adjacency matrix
    printf("\n------------------------------------\n");
    printf("Printing Adj matrix");
    printf("\n------------------------------------\n");
    for (i=0; i<new_graph.M/2; i++){
        printf("%c",'\n');
        printf("%d %d", new_graph.adj_matrix->row[i],new_graph.adj_matrix->col[i]);
    }

///    print degree vector
//    for (i=0; i<new_graph.number_of_nodes; i++){
//        printf("%c",'\n');
//        printf("%d", new_graph.deg_vec->data[i]);
//    }


    ///Start groups division here
    ///extracting singletones
    final_cluster.total_nodes = myGraph_p->number_of_nodes;
    final_cluster.nodes_group_ind = (int *)malloc(myGraph_p->number_of_nodes*sizeof(int));
    separate_singletones(myGraph_p,g_p,final_cluster_p);

    ///create root
//    root = (struct Group*)malloc(sizeof(struct Group));
    push(g_p->Adj_size,g_p->group_size,g_p->indices,g_p->Adj_indices,&root);
    root->next = NULL;


    while (top(root) != NULL){


//        g_p = top(root);


        result = divide_group_into_two(myGraph_p,root,g1_p, g2_p, dq_p);

//        printf("\n------------------------------------");
//        printf("\nRemoving group size: %d\n",root->group_size);
//        printf("------------------------------------\n");


        if (result ==1){
            add_group_to_final_cluster(root, final_cluster_p);
            pop(&root);
            continue;
        }
        pop(&root);
        ///remove element from linked list




        if ((g1_p->group_size == 1)&&(g2_p->group_size == 1)){
            add_group_to_final_cluster(g1_p, final_cluster_p);
            add_group_to_final_cluster(g2_p, final_cluster_p);
        }
        else if (g1_p->group_size == 1){
            add_group_to_final_cluster(g1_p, final_cluster_p);
//
//            printf("------------------------------------\n");
//            printf("Adding group size: %d\n",g2_p->group_size);
//            printf("------------------------------------\n");

            push(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&root);
        }
        else if (g2_p->group_size == 1){


//            printf("------------------------------------\n");
//            printf("Adding group size: %d\n",g1_p->group_size);
//            printf("------------------------------------\n");


            push(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&root);
            add_group_to_final_cluster(g2_p, final_cluster_p);
        }
        else {

//            printf("------------------------------------\n");
//            printf("Adding group size: %d\n",g2_p->group_size);
//            printf("------------------------------------\n");

            push(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&root);


//            printf("------------------------------------\n");
//            printf("Adding group size: %d\n",g1_p->group_size);
//            printf("------------------------------------\n");

            push(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&root);
        }
        free(g1_p->indices);
        free(g2_p->indices);
        free(g1_p->Adj_indices);
        free(g2_p->Adj_indices);

    }


    ///print final set O
//    printf("\n  ");
//    printf("%d  ", final_cluster_p->total_groups);
//    printf("\n  ");
//    for (i=0; i<final_cluster_p->total_nodes;i++){
//        printf("%d  ", final_cluster_p->nodes_group_ind[i]);
//    }

    ///write into output file
    writeToFile(argv[2],final_cluster_p);

    ///check what was written into the file
    printf("\n  ");
    int temp;
    FILE *f = fopen(argv[2], "r");
//    FILE *f = fopen("groups.out", "r");

        while (fread(&temp, 1, sizeof(int), f) == sizeof(int)) {
            printf("%d  " , temp);
        }
        fclose(f);

    printf("\n-----------------End of program------------------\n");

    ///free memory
    free(myGraph_p->deg_vec->data);
    free(myGraph_p->adj_matrix->row);
    free(myGraph_p->adj_matrix->col);
    free(g.Adj_indices);
    free(g.indices);
    free(final_cluster.nodes_group_ind);

    return 0;
}

