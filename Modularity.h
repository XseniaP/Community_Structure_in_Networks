//
// Created by Ksenia Polonsky on 8/17/20.
//

#ifndef PROJECT_TOHNA_MODULARITY_H
#define PROJECT_TOHNA_MODULARITY_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct SparseMatrix {
    int number_of_cols;
    int **values;
}Matrix;

typedef struct Pair {
    int eigenvalue;
    int *eigenvector;
}Pair;

int modularity_matrix();
int degree_vector();
int adjacency_matrix();
int modularity_hat_matrix();
int modularity_value();
int power_iteration();
int compute_s();
int correction();

#endif //PROJECT_TOHNA_MODULARITY_H
