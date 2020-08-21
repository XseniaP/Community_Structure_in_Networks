
#include "Modularity.h"

int modularity_matrix(Graph *g, SymMatrix *b_matrix_p){
    int i=0, j=0, count=0, count2=0;

    //number of elements in lower part of the symmetric matrix
    count = (int)(pow(g->number_of_nodes,2) + g->number_of_nodes)/2;

    //storing only lower part of b_matrix in the array in the following order {b00,b10,b11,b20,b21,b22...} for j<=i bij can be retrieved using the formula bij=b[i(i+1)/2+j] , and bij=bji thus for j>i
    // calculating first -KK/M matrix
    //adding 1 only in the places where ADJ matrix is non-empty

    b_matrix_p->value = (double*) malloc( count * sizeof(double));
    b_matrix_p->col_row_n = g->number_of_nodes;
    count = 0;
    for (i=0; i<b_matrix_p->col_row_n; i++){
        for (j=0; j<=i; j++){
            b_matrix_p->value[count] =  - (((double)g->deg_vec->data[i]) * ((double)g->deg_vec->data[j]) / (double)g->M);
            count++;
            }
        }

    for (i=0; i<g->M/2; i++){
            count2 = (g->adj_matrix->row[i])*(g->adj_matrix->row[i]+1)/2+(g->adj_matrix->col[i]);
            b_matrix_p->value[count2] +=1 ;
        }

    printf("\n%d", count);
    for (i=0; i<count; i++){
        printf("%c",'\n');
        printf("%f", b_matrix_p->value[i] );
    }
    return 0;
}

int matrix_bg(SymMatrix *b_matrix_p,Vector* input_set_p, SymMatrix *bg_matrix_p){
    int n=0, size=0, i=0,j=0;
    n = input_set_p->size;
    size = (int)(pow(n,2) + n)/2;
    bg_matrix_p->col_row_n = n;
    bg_matrix_p->value = (double*)malloc(size* sizeof(double));
    //bij=b[i(i+1)/2+j]
    for (i=0; i<input_set_p->size;i++){
        for (j=0; j<=i;j++) {
            bg_matrix_p->value[i*(i+1)/2+j] = b_matrix_p->value[(input_set_p->data[i])*(input_set_p->data[i]+1)/2+(input_set_p->data[j])];
        }
    }
//        printf("\n%d", size);
//        for (i=0; i<size; i++){
//            printf("%c",'\n');
//            printf("%f", bg_matrix_p->value[i] );
//        }
return 0;
}

int modularity_hat_matrix(SymMatrix *bg_matrix_p,SymMatrix *bg_hat_matrix_p){
    int i=0, j=0, size=0; double sum=0.0;
    size = (int)(pow(bg_matrix_p->col_row_n,2) + bg_matrix_p->col_row_n)/2;
    bg_hat_matrix_p->col_row_n = bg_matrix_p->col_row_n;
    bg_hat_matrix_p->value = (double*)malloc(size* sizeof(double));
    for (i=0;i<bg_matrix_p->col_row_n;i++){
        sum=0.0;
        for (j=0; j<bg_matrix_p->col_row_n; j++){
            //formula of retrieving elements from the matrix bij=b[i(i+1)/2+j]
            bg_hat_matrix_p->value[i*(i+1)/2+j] = bg_matrix_p->value[i*(i+1)/2+j];
            if (i>=j){
                sum += bg_matrix_p->value[i*(i+1)/2+j];
            }
            else{
                sum += bg_matrix_p->value[j*(j+1)/2+i];
            }
        }
        bg_hat_matrix_p->value[i*(i+1)/2+i] = bg_matrix_p->value[i*(i+1)/2+i] - sum;
    }
    return 0;
}


