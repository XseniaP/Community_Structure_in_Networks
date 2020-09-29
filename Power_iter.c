#include "Power_iter.h"


int indices_to_indices_set(Group* group,int *indices, int size, int* indices_set, int marker){
    int i, count =0;

    /** O(n) time complexity */
    for (i=0; i<size; i++){
        if ((marker == 1) && (group->group_size != 0)) {      /** this is the case of the group indides  */
            if ((count < group->group_size)&&(indices[count] == i)) {
                indices_set[i] = 1;
                count += 1;
            } else {
                indices_set[i] = 0;
            }
        }
        else if ((group->Adj_size != 0)&&(marker == 2)){             /** this is the case of the Adj indices*/
            if ((count < group->Adj_size)&&(indices[count] == i)) {
                indices_set[i] = 1;
                count += 1;
            } else {
                indices_set[i] = 0;
            }
        }
    }
    return 0;
}



/** create random vector for initialization of power iteration ; O(n) */
int create_vec(Group* g, int size, double *vec){
    int i;
    int* indices_set;
    indices_set = (int*)safe_malloc(size*sizeof(int));

    /** O(n) time complexity */
    indices_to_indices_set(g,g->indices, size, indices_set,1);

    /** O(n) time complexity */
    srand(time(NULL));
    for (i=0; i<size; i++){
        if (indices_set[i] == 0){
            vec[i] = 0;
        }
        else if (indices_set[i] == 1){
            vec[i] = (double)rand();
        }
        else{
            printf("unknown character instead of index; only 0,1 are allowed");
            return 1;
        }
    }
    free(indices_set);
    return 0;
}

/** calculate ||C|| (sum of max column) /// optionally add it to diagonal elements of symmetric matrix B to create b^, but we dont need to keep b^
/// complexity O(m+n)*n , sparse graphs with m ~ n are in in the focus thus the resulting complexity would be O(n^2) */
int matrix_shift_C_new(Graph* graph, Group* g, double* max_p, double *row_sums_p){
    int i,j;
    double sum, max;
    double * temp;
    int* indices_set;    int* Adj_indices_set;
    temp = (double*) safe_calloc( graph->number_of_nodes , sizeof(double));
    sum=0, max=0;

    indices_set = (int*)safe_malloc(graph->number_of_nodes*sizeof(int));
    /** O(n) */
    indices_to_indices_set(g,g->indices, graph->number_of_nodes, indices_set,1);


    Adj_indices_set = (int*)safe_malloc(graph->M/2*sizeof(int));
    /** O(m) */
    indices_to_indices_set(g,g->Adj_indices, graph->M/2, Adj_indices_set,2);


    /** the loop is O(n*(m+n))  */
    for (i=0; i<graph->number_of_nodes; i++){

        /** the loop is O(m); going over Adj matrix and adding 1 where appropriate */
        for (j=0; j<graph->adj_matrix->size;j++) {
            if (Adj_indices_set[j] == 1) {
                if ((graph->adj_matrix->row[j] == i) || (graph->adj_matrix->col[j] == i)) {
                    if (graph->adj_matrix->row[j] == i) {
                        temp[graph->adj_matrix->col[j]] += 1.0;
                    } else {
                        temp[graph->adj_matrix->row[j]] += 1.0;
                    }
                }
            }
        }

        /** the loop is O(n); deducting kikj/M  */
        for (j=0; j<graph->number_of_nodes; j++){
            temp[j] +=  - (((double)graph->deg_vec->data[i]) * ((double)graph->deg_vec->data[j]) / (double)graph->M);
        }

        /** the loop is O(n); multiplying by the indices , not relevant elements will turn zero */
        for (j=0; j<graph->number_of_nodes; j++){
            temp[j] = temp[j]*indices_set[i]*indices_set[j];
            sum += temp[j];
        }

        row_sums_p[i]=sum;
        sum=0;

        /** the loop is O(n) */
        for (j=0; j<graph->number_of_nodes; j++){
            if(i==j){
                sum += fabs(temp[j]-row_sums_p[i]);
            }
            else {
                sum += fabs(temp[j]);
            }
        }
        if (sum>max){
            max = sum;
        }
        sum=0;

        /** memset is O(n) */
        memset(temp,(double)0.0,(graph->number_of_nodes)*(sizeof(double)));
    }

    free(temp);
    free(indices_set);
    free(Adj_indices_set);
    *max_p = max;
    return 0;

}

/** multiply vector by symmetric shifted matrix B ; O(n+m) time complexity */
int vec_mult_B_shifted(Graph* graph, Group* g_p, double *rand_vec, double max,double *row_norm, double *row_sums_p) {
    int i=0, ind1=0,ind2=0;
    long double cons=0.0, *comp2, *comp3; double* comp;
    int* indices_set;    int* Adj_indices_set;

    /** O(n) */
    indices_set = (int*)safe_malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, indices_set,1);

    /** O(m) */
    Adj_indices_set = (int*)safe_malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set,2);

    /** step1 - calculate A * random vector - O(m) */
    for (i=0; i<graph->adj_matrix->size; i++){
        if (Adj_indices_set[i]==1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            row_norm[ind1] += rand_vec[ind2];
            row_norm[ind2] += rand_vec[ind1];
        }
    }

    /** step2 - to calculate Constant = Random vector * k^T - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(rand_vec[i])*(long double)(graph->deg_vec->data[i]);
    }

    /** step3 - multiply Constant (Random vector * k^T earlier calculated) by k and divide by M  - O(n) */
    comp2 = (long double*)safe_malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        if(graph->M == 0){
            printf("Divide overflow / Division by zero operation");
            exit(1);
        }
        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
    }

    /** step4 - random vector * ||C|| (matrix shift max column sum) - O(n) */
    comp3 = (long double*)safe_malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        comp3[i] = (long double)max * (long double)rand_vec[i];
    }

    /** step5 - combine 4 steps - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i]+(double)comp3[i];
    }

    /** step6 - deduct Row sums of B_hat matrix * Eigenvector  - O(n) */
    comp = (double *)safe_malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p[i]*rand_vec[i];
        row_norm[i] = row_norm[i] - comp[i];
    }

    free(comp);
    free(comp2);
    free(comp3);
    free(indices_set);
    free(Adj_indices_set);
    return 0;
}

/**O(n+m) due to vec_mult_B complexity */
int norm_vec (Graph* graph, Group* g_p, double *rand_vec, double max,double *row_norm,double *row_sums_p){
    int i=0;
    double sum=0.0;

    /**vector-matrix multiplication - O(n+m) */
    vec_mult_B_shifted(graph, g_p,rand_vec,max,row_norm,row_sums_p);

    /**step5 - sum of square of the vector elements - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        sum +=pow(row_norm[i],2);
    }

    /**step6 - normalize - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        if(!IS_POSITIVE(sum)){
            printf("Divide overflow / Division by zero operation");
            exit(1);
        }
        row_norm[i] = row_norm[i]/pow(sum,0.5);
    }
    return 0;
}

/**check if the difference between two vectors is ~0 - O(n) */
int check_difference(int height ,double *temp ,double *next){
    double difference, *pointer1 = NULL, *pointer2 = NULL;
    int i;
    pointer1 = &temp[0]; pointer2 = &next[0];

    for (i = 0; i < height; i++) {
        difference=fabs((*(pointer1 + i))-(*(pointer2 + i)));
        if (!IS_POSITIVE(difference)){
            continue;
        }
        else{
            return 0;
        }
    }
    return 1;
}

/**power iteration which starts with random vector and matrix shift and returns the Pair structure with eigenvector and eigenvalue */
int powerIteration(Graph* graph, Group* g_p, Pair* pair_p, double *row_sums_p){
    double *temp = NULL, *row_norm = NULL,  *vec = NULL, *max =NULL, numerator, max_v;
    int check, true=0, i=0; double value_without_c; double* vect_temp;
    int iteration=0, max_iteration;
    max = &max_v;
    vec = (double *)safe_malloc(graph->number_of_nodes*sizeof(double));

    /** the condition for the power iteration convergence check */
    max_iteration = pow(graph->number_of_nodes,2) + 20000*graph->number_of_nodes+20000;

    /** using calloc to initialize to zero - important! */
    row_norm = (double *)safe_calloc(graph->number_of_nodes,sizeof(double));

    /** create random vector */
    create_vec(g_p,graph->number_of_nodes, vec);

    /** calculate ||C|| and row_sums vector */
    matrix_shift_C_new(graph, g_p, max, row_sums_p);

    temp = vec;
    while ((true == 0)&&(iteration<max_iteration)){
        norm_vec(graph, g_p, temp, max_v, row_norm, row_sums_p);
        check=check_difference(graph->number_of_nodes ,temp ,row_norm);
        iteration +=1;
        if (check==0){
            free(temp);
            temp = row_norm;
            row_norm = (double *)safe_calloc(graph->number_of_nodes,sizeof(double));
        }
        else{
            free(temp);
            true=1;
        }
    }
    if(iteration>=max_iteration){
        printf("the power method did not converge");
        exit(1);
    }

    pair_p->eigenvector = row_norm;

    /** find corresponding eigenvalue of the shifted matrix */
    numerator = 0.0;

    /** important to use calloc here, so that zeroes are initiated */
    vect_temp = (double *)safe_calloc(graph->number_of_nodes,sizeof(double));
    vec_mult_B_shifted(graph, g_p, pair_p->eigenvector , max_v,vect_temp, row_sums_p);

/** dot product of eigenvector and vector with the results from B_hat shifted * eigenvector - O(n) */
    for(i=0; i<graph->number_of_nodes;i++){
        numerator+= vect_temp[i]*pair_p->eigenvector[i];
    }

/** deduct ||C|| to get leading eigenvalue of the original matrix O(1) */
    value_without_c = numerator - max_v;
    pair_p->eigenvalue = value_without_c;

    free(vect_temp);
    return 0;
}


int calculate_dq(Graph* graph,Group* g_p, int *s_p, double *row_sums_p, double* dq_p){
    int i=0, ind1=0,ind2=0; double* row_norm; int* indices_set; int* Adj_indices_set;
    long double cons=0.0, *comp2; double* comp;
    *dq_p=0.0;

    row_norm = (double*)safe_calloc(graph->number_of_nodes,sizeof(double));

    indices_set = (int*)safe_malloc(graph->number_of_nodes*sizeof(int));
    indices_to_indices_set(g_p, g_p->indices, graph->number_of_nodes, indices_set,1);


    Adj_indices_set = (int*)safe_malloc(graph->M/2*sizeof(int));
    indices_to_indices_set(g_p, g_p->Adj_indices, graph->M/2, Adj_indices_set,2);

    /** step1 - calculate A *  s_vector - O(m)  */
    for (i=0; i<graph->adj_matrix->size; i++){
        if (Adj_indices_set[i]==1) {
            ind1 = graph->adj_matrix->row[i];
            ind2 = graph->adj_matrix->col[i];
            row_norm[ind1] += s_p[ind2];
            row_norm[ind2] += s_p[ind1];
        }

    }

    /** step2 - to calculate Constant = s_vector * k^T - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        cons+=(long double)(s_p[i])*(long double)(graph->deg_vec->data[i]);
    }

    /** step3 - multiply Constant (s_vector * k^T earlier calculated) by k and divide by M  - O(n) */
    comp2 = (long double*)safe_malloc(graph->number_of_nodes* sizeof(long double));
    for (i=0; i<graph->number_of_nodes; i++){
        if(graph->M == 0){
            printf("Divide overflow 5/ Division by zero operation");
            exit(1);
        }
        comp2[i] = cons*(graph->deg_vec->data[i])*(indices_set[i])/(graph->M);
    }

    /** step4 - combine 3 steps - O(n) */
    for (i=0; i<graph->number_of_nodes; i++){
        row_norm[i] = row_norm[i]-(double)comp2[i];
    }

    /** step5 - deduct Row sums of B_hat matrix * vector S  - O(n) */
    comp = (double *)safe_malloc(graph->number_of_nodes*sizeof(double));
    for(i=0; i<graph->number_of_nodes;i++){
        comp[i] = row_sums_p[i]*s_p[i];
        row_norm[i] = row_norm[i] - comp[i];
    }

    /** step6 - multiply the obtained vector by S^T from the left  - O(n) */
    for(i=0; i<graph->number_of_nodes;i++){
        *dq_p += row_norm[i]*s_p[i];
    }

    /** step7 - divide by 2 (or 2M according to the original paper) - O(1) */
    *dq_p = *dq_p/(2);

    free(comp);
    free(row_norm);
    free(comp2);
    free(indices_set);
    free(Adj_indices_set);
    return 0;
}
