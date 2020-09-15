#include "Maximization.h"
#include "structures.h"

//int bs(Graph* graph,Group* g_p,int *s_p, double* bs_p) {
//    int i=0, ind1=0,ind2=0;
//    long double cons=0.0, *comp2; double* comp;
//
//    int* indices_set;
//    indices_set = (int*)malloc(graph->number_of_nodes*sizeof(int));
//    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, indices_set);
//
//    int* Adj_indices_set;
//    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
//    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set);
//
//    ///step1 - calculate A *  s_vector - O(m)
//    for (i=0; i<graph->adj_matrix->size; i++){
//        if (Adj_indices_set[i]==1) {
//            ind1 = graph->adj_matrix->row[i];
//            ind2 = graph->adj_matrix->col[i];
//            bs_p[ind1] += s_p[ind2];
//            bs_p[ind2] += s_p[ind1];
//        }
////        printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
//    }
////    printf("\n\n%f  %f  %f  %f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2],row_norm[3],row_norm[4],row_norm[5]);
////    printf("\n\n%f  %f  %f\n", rand_vec[0],rand_vec[1],rand_vec[2]);
////    printf("\n\n%d  %d  %d\n", graph->adj_matrix->row[0],graph->adj_matrix->row[1],graph->adj_matrix->row[2]);
////    printf("\n\n%d  %d  %d\n", graph->deg_vec->data[0],graph->deg_vec->data[1],graph->deg_vec->data[2]);
////    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
//
//    ///step2 - to calculate Constant = s_vector * k^T - O(n)
//    for (i=0; i<graph->number_of_nodes; i++){
//        cons+=(long double)(s_p[i])*(long double)(graph->deg_vec->data[i]);
//    }
////    printf("\n%Lf  \\n", cons);
//
//    ///step3 - multiply Constant (s_vector * k^T earlier calculated) by k and divide by M  - O(n)
//    comp2 = (long double*)malloc(graph->number_of_nodes* sizeof(long double));
//    for (i=0; i<graph->number_of_nodes; i++){
//        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
//    }
////    printf("\n\n%Lf  %Lf  %Lf\n", comp2[0],comp2[1],comp2[2]);
//
//    ///step4 - combine 3 steps - O(n)
//    for (i=0; i<graph->number_of_nodes; i++){
//        bs_p[i] = bs_p[i]-(double)comp2[i];
//    }
////    printf("\n\n%f  %f  %f\n", row_norm[0],row_norm[1],row_norm[2]);
//
//    ///step6 - multiply the obtained vector by ST from the left  - O(n)
//    for(i=0; i<graph->number_of_nodes;i++){
//        *dq_p += bs_p[i]*s_p[i];
//    }
//
//    free(comp);
//    free(comp2);
//    free(indices_set);
//    free(Adj_indices_set);
//
//    return 0;
//}
//
//
//int maximize(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p){
//    int *unmoved, i;
//    double *score, *bs_p;
//
//    ///initialized with zeroes
//    unmoved = (int*)calloc(g_p->group_size,sizeof(int));
//    score = (double*)calloc(graph->number_of_nodes,sizeof(int));
//    bs_p = (double *) calloc(graph->number_of_nodes, sizeof(double));
//
//    bs(graph,g_p, s_p, bs_p);
//
//    while (IS_POSITIVE(*dq_p)){
//        memset(unmoved, 0,  g_p->group_size*sizeof(int));
//
//        for (i=0; i<g_p->group_size;i++){
//            s_p[g_p->indices[i]] = - s_p[g_p->indices[i]];
//            score[i] = 4*s_p[g_p->indices[i]]*bs_p[i]+4.0*graph->deg_vec->data[g_p->indices[i]]*graph->deg_vec->data[g_p->indices[i]]/graph->M;
//
//        }
//    }
//    return 0;
//}