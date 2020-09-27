#include "Maximization.h"
#include "structures.h"

int score_calc(Graph* graph,Group*  g_p, int *s_p, long double *score, int* moved){
    int i=0, ind1=0,ind2=0, max_index = -1;
    long double cons=0.0, max = NEGINFINITY, *comp2, temp;

    int* Adj_indices_set;
    Adj_indices_set = (int*)malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set,2);

//    memset(score, 0.0, graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        score[i]=0.0;
    }

///step1 - calculate A * S - O(m)
    for (i = 0; i < graph->adj_matrix->size; i++) {
        if (Adj_indices_set[i] == 1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            if (moved[ind1]!=0){
            score[ind1] += s_p[ind2]*moved[ind1];
            }
            if (moved[ind2]!=0){
            score[ind2] += s_p[ind1]*moved[ind2];
            }
        }
    }
//    printf("\n------------------------------------\n");
//    printf("Printing A * s");
//    printf("\n------------------------------------\n");
//    printf("\n %Lf  %Lf   %Lf  %Lf  %Lf   %Lf  \n", score[0],score[1],score[2],score[3],score[4],score[5]);


///step2 - to calculate Constant = S * k^T - O(n)
    for (i = 0; i < graph->number_of_nodes; i++) {
        cons += (long double) (s_p[i]) * (long double) (graph->deg_vec->data[i]);
    }
//    printf("\n------------------------------------\n");
//    printf("Printing constant");
//    printf("\n------------------------------------\n");
//    printf("\n%Lf  ", cons);

///step3 - multiply Constant (Random vector * k^T earlier calculated) by k and divide by M  - O(n)
    comp2 = (long double *) calloc(graph->number_of_nodes,sizeof(long double));
    for (i = 0; i < graph->number_of_nodes; i++) {
        if(moved[i]!=0) {
            comp2[i] =
                    ((cons * (graph->deg_vec->data[i])) - 2 * s_p[i] * pow(graph->deg_vec->data[i], 2)) * (moved[i]) /
                    (graph->M);
        }
    }

//    printf("\n------------------------------------\n");
//    printf("KKs / M");
//    printf("\n------------------------------------\n");
//    printf("\n %Lf  %Lf  %Lf  %Lf  %Lf   %Lf  \n", comp2[0],comp2[1],comp2[2],comp2[3],comp2[4],comp2[5]);

///step4 - calulcating score - O(n)
    for (i = 0; i < graph->number_of_nodes; i++) {
        if (moved[i]!=0) {
            score[i] = 4 * (-s_p[i]) * (score[i] - comp2[i]) +
                       4 * pow(graph->deg_vec->data[i], 2) * (moved[i]) / (graph->M);
            temp = score[i];
            if (score[i] > max) {
                max_index = i;
                max = score[i];

            }
        }
    }
//
//    printf("\n------------------------------------\n");
//    printf("Printing Score");
//    printf("\n------------------------------------\n");
//    printf("\n %Lf  %Lf   %Lf  %Lf  %Lf   %Lf  \n", score[0],score[1],score[2],score[3],score[4],score[5]);

    free(Adj_indices_set);
    free(comp2);

    return max_index;
}

int maximize(Graph* graph,Group* g_p, int *s_p){
    int *moved, *indices_moved; int i; long double* score, *improve, max_improve, dQ = 0.0; int j=0, max_index, max_improve_index;
    moved = (int*)malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, moved,1);

    score = (long double *)calloc(graph->number_of_nodes,sizeof(long double));
    improve = (long double *)calloc(g_p->group_size,sizeof(long double));
    indices_moved = (int *)calloc(g_p->group_size,sizeof(int));

    /// the while loop will finish because we should have either zero improvement or negative at certain point
    /// "do" while will ensure we enter while with dQ=0.0
    do{
        indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, moved,1);
        for(i=0; i<graph->number_of_nodes; i++){
            score[i] = 0.0;
        }
        for(i=0; i<g_p->group_size; i++){
            improve[i] = 0.0;
            indices_moved[i]=0;
        }

        max_improve=0.0;
        max_improve_index = g_p->group_size-1;

        ///overall O(n^2) complexity
        for (i=0; i<g_p->group_size; i++){


            printf("\n------------------------------------\n");
            printf("Printing S");
            printf("\n------------------------------------\n");
            for(j=0; j<graph->number_of_nodes;j++) {
                printf("%d ", s_p[j]);
            }
            printf("\n------------------------------------\n");
            printf("Printing moved");
            printf("\n------------------------------------\n");
            for(j=0; j<graph->number_of_nodes;j++) {
                printf("%d ", moved[j]);
            }

            max_index = score_calc(graph,g_p, s_p, score,moved);  /// O(n+m) time complexity

            printf("\n------------------------------------\n");
            printf("Printing Scores");
            printf("\n------------------------------------\n");
            for(j=0; j<graph->number_of_nodes;j++) {
                printf("%Lf ", score[j]);
            }

            s_p[max_index] = -s_p[max_index];
            indices_moved[i] = max_index;

            printf("\n------------------------------------\n");
            printf("Printing indices of moved elements");
            printf("\n------------------------------------\n");
            for(j=0; j<g_p->group_size;j++) {
                printf("%d ", indices_moved[j]);
            }

            if (i==0){
                improve[i] = score[max_index];
            }
            else{
                improve[i] = improve[i-1]+score[max_index];
                if (improve[i]>max_improve){
                    max_improve=improve[i];
                    max_improve_index = i;
                }
            }
            printf("\n------------------------------------\n");
            printf("Printing Improve");
            printf("\n------------------------------------\n");
            for(j=0; j<g_p->group_size;j++) {
                printf("%Lf ", improve[j]);
            }

            moved[max_index] = 0;  /// moved starts with 0's of the elements that are not in the group and 1's that are in the group and then changes them to 0 after they are moved
        }

        for(i=g_p->group_size-1; i>max_improve_index; i--){
           j = indices_moved[i];
           s_p[j] = -s_p[j];
        }
        if (max_improve_index == g_p->group_size-1){
                dQ = 0.0;
        }
        else{
            dQ = improve[max_improve_index];
        }
        printf("\n------------------------------------\n");
        printf("Printing dQ inside of max algo");
        printf("\n------------------------------------\n");
        printf("%Lf \n",dQ);

    }while (IS_POSITIVE(dQ));

    printf("\n------------------------------------\n");
    printf("Printing S after maximization");
    printf("\n------------------------------------\n");
    for(i=0; i<graph->number_of_nodes;i++) {
        printf("%d ", s_p[i]);
    }

    free(moved);
    free(improve);
    free(score);
    free(indices_moved);
    return 0;
}