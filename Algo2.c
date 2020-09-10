#include "Algo2.h"

/// O(n)
int compute_s(Pair *pair_p, int* s_p, int size){
    int i=0;
    for (i=0; i<size; i++){
        if(pair_p->eigenvector[i]==0.0){
            s_p[i] = 0;
        }
        else if (pair_p->eigenvector[i]>0.0){
            s_p[i] = 1;
        }
        else{
            s_p[i] = -1;
        }
    }
    return 0;
}


int calculate_dq(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p){
    int i=0, ind1=0,ind2=0; double* row_norm;
    long double cons=0.0, *comp2; double* comp;
    *dq_p=0.0;

    row_norm = (double*)calloc(graph->number_of_nodes,sizeof(double));
    int* indices_set;
    indices_set = (int*)malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p->indices, graph->number_of_nodes, indices_set);

    int* Adj_indices_set;
    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p->Adj_indices, graph->M/2, Adj_indices_set);

    ///step1 - calculate A *  s_vector - O(m)
    for (i=0; i<graph->adj_matrix->size; i++){
        if (Adj_indices_set[i]==1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            row_norm[ind1] += s_p[ind2];
            row_norm[ind2] += s_p[ind1];
        }
//        printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
    }
    printf("\n\n%f  %f  %f  %f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);
//    printf("\n\n%f  %f  %f\n", rand_vec[0],rand_vec[1],rand_vec[2]);
//    printf("\n\n%d  %d  %d\n", graph->adj_matrix->row[0],graph->adj_matrix->row[1],graph->adj_matrix->row[2]);
//    printf("\n\n%d  %d  %d\n", graph->deg_vec->data[0],graph->deg_vec->data[1],graph->deg_vec->data[2]);
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step2 - to calculate Constant = s_vector * k^T - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(s_p[i])*(long double)(graph->deg_vec->data[i]);
    }
//    printf("\n%Lf  \\n", cons);

    ///step3 - multiply Constant (s_vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
    }
//    printf("\n\n%Lf  %Lf  %Lf\n", comp2[0],comp2[1],comp2[2]);

    ///step4 - combine 3 steps - O(n)
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    ///step5 - deduct Row sums of B_hat matrix * Eigenvector  - O(n)
    comp = (double *)malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p->data[i]*s_p[i];
        row_norm[i] = row_norm[i] - comp[i];
    }
//    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);

    printf("\n\n%f  %f  %f  %f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);

    ///step6 - multiply the obtained vector by ST from the left  - O(n)
    for(i=0; i<graph->number_of_nodes;i++){
        *dq_p += row_norm[i]*s_p[i];
    }

    free(comp);
    free(comp2);
    free(indices_set);
    free(Adj_indices_set);
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
    for (i=0; i<graph->number_of_nodes; i++){
        printf("%d ", s_p[i]);
    }
    printf("\n ");
    count1=0; count2=0;
    for (i=0; i<graph->number_of_nodes; i++){
        if(s_p[i]==1){
            group1->indices[count1]=i;
            printf("gr1  %d  ",i);
            count1+=1;
        }
        else if(s_p[i]==(-1)){
            group2->indices[count2]=i;
            printf("gr2  %d  ",i);
            count2+=1;
        }
    }
    adj_for_g(graph ,group1);
    adj_for_g(graph ,group2);

    printf("\n");
    return 0;
}

int divide_group_into_two(Graph* graph, Group* g, Group* g1, Group* g2, double *dq_p){
    ///declarations
    Pair pair = {0.0, NULL};Vector_double row_sums = {0,NULL};Vector_double *row_sums_p;
    int* s_p;
    ///pointers
    Pair* pair_p = &pair;row_sums_p=&row_sums;
    int i, count1=0, count2=0;

    row_sums.data = (double *)calloc(graph->number_of_nodes,sizeof(double));
    powerIteration(graph, g, pair_p, row_sums_p);

    s_p = (int*)malloc(graph->number_of_nodes * sizeof(int));
    compute_s(pair_p, s_p, graph->number_of_nodes);

//    printf("\n");
//    for (i=0; i<graph->number_of_nodes; i++){
//        printf("%f  ", row_sums_p->data[i]);
//    }
//    printf("\n");

    calculate_dq(graph,g, s_p, row_sums_p, dq_p);

    if (pair_p->eigenvalue<=0){
        printf("network is non-dividable");
        return 1;
    }
    else if (*dq_p<=0){
        printf("%f  network is non-dividable", *dq_p);
        return 1;
    }
    else{
        split_group_based_on_s(s_p, graph, g1, g2);
        return 0;
    }

    free(pair_p->eigenvector);
    return 0;
}

int divide_network(char* argv[], int*** output_p){
///declarations , initializations, pointers
    Graph new_graph = {NULL,0,0,NULL, NULL};Graph *myGraph_p;
    SparseMatrix adj_matrix = {0, NULL,NULL, NULL};Vector_int deg_vec = {0,NULL};
    Group g ={NULL,NULL};Group g1 ={NULL,NULL};Group g2 ={NULL,NULL};
    Group *g_p, *g1_p, *g2_p; g_p = &g; g1_p = &g1; g2_p = &g2;
    Element p_set ={NULL,NULL}, o_set ={NULL,NULL};
    Element *p_set_head, *o_set_head, next;
    double *dq_p; double dq;

    int i=0, a, result;

    new_graph.deg_vec = &deg_vec; new_graph.adj_matrix = &adj_matrix; myGraph_p = &new_graph;
    p_set_head = &p_set; o_set_head = &o_set; dq_p = &dq;


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
        g.indices[i]=i;
    }

//    g.indices = (int *)malloc(3*sizeof(int));
//    g.group_size = 3;
//    g.indices[0] = 0;
//    g.indices[1] = 2;
//    g.indices[2] = 4;

    ///Initiate Adj matrix indices for default g
    g.Adj_indices = (int *)calloc(myGraph_p->M/2,sizeof(int));
    g.Adj_size = myGraph_p->M/2;
    for (i=0; i<myGraph_p->M/2;i++){
        g.Adj_indices[i]=i;
    }

//    g.Adj_indices = (int *)calloc(3,sizeof(int));
//    g.Adj_size = 3;
//    g.Adj_indices[0] = 1;
//    g.Adj_indices[1] = 3;
//    g.Adj_indices[2] = 4;

///    print indices in the default g
    for (i=0; i<new_graph.number_of_nodes; i++){
        printf("%c",'\n');
        printf("%d", g.indices[i]);
    }

///    print full adjacency matrix
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
    p_set_head = createElement(sizeof(Group));
    p_set_head->data = g_p;
    o_set_head = createElement(sizeof(int**));

    while (!is_empty(p_set_head)){
        g_p = remove_graph_from_list(p_set_head);
        result = divide_group_into_two(myGraph_p,g_p,g1_p, g2_p, dq_p);
        if (result ==1){
            add_group_to_final_set(g_p, o_set_head);
        }
        else{
            if ((g1_p->group_size == 1)&&(g2_p->group_size == 1)){
                add_group_to_final_set(g1_p, o_set_head);
                add_group_to_final_set(g2_p, o_set_head);
            }
            else if (g1_p->group_size == 1){
                add_group_to_final_set(g1_p, o_set_head);
                add_group_to_element(g2_p, p_set_head);
            }
            else if (g2_p->group_size == 1){
                add_group_to_element(g1_p, p_set_head);
                add_group_to_final_set(g2_p, o_set_head);
            }
            else {
                add_group_to_element(g1_p, p_set_head);
                add_group_to_element(g2_p, p_set_head);
            }
        }
    }

//    divide_group_into_two(myGraph_p, g_p, g1_p,g2_p);

//    adj_ind_for_input_set(myGraph_p ,g);


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

