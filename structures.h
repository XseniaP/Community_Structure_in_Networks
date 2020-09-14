

#ifndef PROJECT_TOHNA_STRUCTURES_H
#define PROJECT_TOHNA_STRUCTURES_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#define IS_POSITIVE(X) ((X) > 0.00001)

typedef struct Vector_int {
    int size;
    int *data;
}Vector_int;

typedef struct Vector_double {
    int size;
    double *data;
}Vector_double;

typedef struct SparseMatrix {
    int size;
    int *row;
    int *col;
}SparseMatrix;

typedef struct Pair {
    double eigenvalue;
    double *eigenvector;
}Pair;

typedef struct Graph {
    int number_of_nodes;
    int M;
    Vector_int *deg_vec;
    SparseMatrix *adj_matrix;
}Graph;

typedef struct Group_{
    int *indices;
    int group_size;
    int *Adj_indices;
    int Adj_size;
}Group;

#endif //PROJECT_TOHNA_STRUCTURES_H
