#include "Algo2.h"

/** compute s vector based on the eigenvector - O(n) */
int compute_s(Pair *pair_p, int* s_p, int size){
    int i=0;

    for (i=0; i<size; i++){
        if(!IS_POSITIVE(fabs(pair_p->eigenvector[i]))){
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

/** Create array which marks which of the "Adjacency matrix" indices are relevant for the specific group - O(m*n) */
int adj_for_g(Graph* graph ,Group* g){
    int i, j, count1=0,count2=0;
    /** O(m*n) */
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
    g->Adj_indices = (int*)safe_malloc(g->Adj_size* sizeof(int));

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


/** Splits group into two based on the s vector - O(m*n) */
int split_group_based_on_s(int *s_p, Graph *graph, Group* group1, Group* group2){
    int i,count1=0, count2=0;

    /** O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
            if(s_p[i]==1){
                count1+=1;
            }
            else if(s_p[i]==(-1)){
                count2+=1;
            }
    }
    group1->indices = (int*)safe_calloc(count1,sizeof(int));
    group1->group_size = count1;
    group2->indices = (int*)safe_calloc(count2,sizeof(int));
    group2->group_size = count2;

    /** O(n) */
    count1=0; count2=0;
    for (i=0; i<graph->number_of_nodes; i++){
        if(s_p[i]==1){
            group1->indices[count1]=i;
            count1+=1;
        }
        else if(s_p[i]==(-1)){
            group2->indices[count2]=i;
            count2+=1;
        }
    }
    /** O(m*n) */
    adj_for_g(graph ,group1);
    adj_for_g(graph ,group2);

    return 0;
}

/** in case if the initial graph has isolated nodes (singletones) we immediately add them to the output using this function */
int separate_singletons(Graph *graph, Group* group, Final_List* final_cluster_p){
    int i, count = 0;
    /** O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        if (IS_POSITIVE(graph->deg_vec->data[i])){
            count+=1;
        }
    }
    group->group_size = count;
    free(group->indices);
    group->indices = (int*)safe_malloc(group->group_size* sizeof(int));
    count = 0;

    /** O(n) */
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
    /** function receives group and applies Power iteration algorithm, followed by maximization to */
int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2, double *dq_p){
    /** declarations */
    Pair pair = {0.0, NULL};double *row_sums_p = NULL;
    int *s_p;
    /** pointers */
    Pair* pair_p = &pair;

    row_sums_p = (double *)safe_calloc(graph->number_of_nodes,sizeof(double));
    /** O(n^2) * number of iterations needed to converge (regularly expected to be O(n) based on the literature and Newman Paper) */
    powerIteration(graph, g, pair_p, row_sums_p);

    s_p = (int*)safe_calloc(graph->number_of_nodes , sizeof(int));
    /** O(n) */
    compute_s(pair_p, s_p, graph->number_of_nodes);

    /** call for maximization - O(n^2) * number of iterations of the while loop before getting dQ<=0 (Worst case O(n)); */
    maximize(graph, g, s_p);

    calculate_dq(graph, g, s_p, row_sums_p, dq_p);

    if (!IS_POSITIVE(pair_p->eigenvalue)){
        free(pair_p->eigenvector);
        free(row_sums_p);
        free(s_p);
        return 1;
    }
    else if (!IS_POSITIVE(*dq_p)){
        free(pair_p->eigenvector);
        free(row_sums_p);
        free(s_p);
        return 1;
    }
    else{
        split_group_based_on_s(s_p, graph, g1, g2);
        free(pair_p->eigenvector);
        free(row_sums_p);
        free(s_p);
        return 0;
    }

}

int divide_network(char* argv[]){
/** declarations , initializations, pointers */
    Graph new_graph = {0,0,NULL,NULL};Graph *myGraph_p;
    Final_List final_cluster = {0, 0,NULL};
    Group output = {NULL,0,NULL,0,NULL};
    SparseMatrix adj_matrix = {0, NULL,NULL};Vector_int deg_vec = {0,NULL};
    Group g ={NULL,0,NULL,0,NULL};Group g1 ={NULL,0,NULL,0,NULL};Group g2 ={NULL,0,NULL,0,NULL};
    Final_List *final_cluster_p;
    double *dq_p; double dq;
    struct Group *root, *output_root = &output;
    int i=0, a, result;
    int temp;FILE *f;
    Group *g_p, *g1_p, *g2_p;g_p = &g;g1_p = &g1; g2_p = &g2;

    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph; final_cluster_p = &final_cluster;
     dq_p = &dq;


/** reading the file, creating the graph with Adj matrix and degree vector */
    a = readFile(argv[1], myGraph_p);
    if (a){
        printf("Couldn't read the file\n");
        exit(1);
    }

    /** Initiate default group g of initial full graph */
    g.indices = (int *)safe_malloc(myGraph_p->number_of_nodes*sizeof(int));
    g.group_size = myGraph_p->number_of_nodes;
    for (i=0; i<myGraph_p->number_of_nodes;i++){
            g.indices[i] = i;
    }

    /** Initiate Adj matrix indices for default g */
    g.Adj_indices = (int *)safe_calloc(myGraph_p->M/2,sizeof(int));
    g.Adj_size = myGraph_p->M/2;
    for (i=0; i<myGraph_p->M/2;i++){
        g.Adj_indices[i]=i;
    }

    /** Start groups division here
    extracting singletons */
    final_cluster.total_nodes = myGraph_p->number_of_nodes;
    final_cluster.nodes_group_ind = (int *)safe_malloc(myGraph_p->number_of_nodes*sizeof(int));
    separate_singletons(myGraph_p,g_p,final_cluster_p);

    /** create root */
    push(g_p->Adj_size,g_p->group_size,g_p->indices,g_p->Adj_indices,&root);
    root->next = NULL;

    while (top(root) != NULL){

        if(root->group_size == 0){
            printf("\n\n found empty \n\n");
            pop(&root);
        }

        result = divide_group_into_two(myGraph_p,root,g1_p, g2_p, dq_p);

        if (result ==1){
            add_group_to_final_set(root->Adj_size,root->group_size,root->indices,root->Adj_indices,&output_root);

            pop(&root);
            continue;
        }
        pop(&root);  /** remove element from linked list */


        if ((g1_p->group_size == 1)&&(g2_p->group_size == 1)){

            add_group_to_final_set(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&output_root);
            add_group_to_final_set(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&output_root);
        }
        else if (g1_p->group_size == 1){
            add_group_to_final_set(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&output_root);


            push(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&root);
        }
        else if (g2_p->group_size == 1){
            push(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&root);
            add_group_to_final_set(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&output_root);
        }
        else {
            push(g2_p->Adj_size,g2_p->group_size,g2_p->indices,g2_p->Adj_indices,&root);
            push(g1_p->Adj_size,g1_p->group_size,g1_p->indices,g1_p->Adj_indices,&root);
        }
        free(g1_p->indices);
        free(g2_p->indices);
        free(g1_p->Adj_indices);
        free(g2_p->Adj_indices);

    }

    /** write into output file */
    writeToFile(argv[2],output_root);

    /** check what was written into the file */
    printf("\n  ");
    f = fopen(argv[2], "r");

        while (fread(&temp, 1, sizeof(int), f) == sizeof(int)) {
            printf("%d  " , temp);
        }
        fclose(f);

    printf("\n-----------------End of program------------------\n");

    /** free memory */
    free(myGraph_p->deg_vec->data);
    free(myGraph_p->adj_matrix->row);
    free(myGraph_p->adj_matrix->col);
    free(g.Adj_indices);
    free(g.indices);
    free(final_cluster.nodes_group_ind);

    return 0;
}

