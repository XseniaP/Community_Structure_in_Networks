//
// Created by Ksenia Polonsky on 8/18/20.
//

#ifndef PROJECT_TOHNA_STRUCTURES_H
#define PROJECT_TOHNA_STRUCTURES_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define IS_POSITIVE(X) ((X) > 0.00001)

typedef struct Vector {
    int size;
    int *data;
}Vector;

typedef struct SymMatrix {
    int col_row_n;
    double *value;
}SymMatrix;

typedef struct SparseMatrix {
    int size;
    int *row;
    int *col;
    double *value;
}SparseMatrix;

typedef struct Pair {
    double eigenvalue;
    double *eigenvector;
}Pair;

typedef struct Graph {
    int number_of_nodes;
    int M;
    Vector *deg_vec;
    SparseMatrix *adj_matrix;
}Graph;

#endif //PROJECT_TOHNA_STRUCTURES_H
