/** Structures module summary:
 *
 * this module includes all struct (composite data type) declarations
 *
 * The module defines the following structs:
 *   SparseMatrix - stores only non-zero elements of the matrix in the form of row index, column index arrays
 *   Pair - allows to keep one element of type double and one double pointer (array of type double);
 *   used to maintain eigenpair, i.e. eigenvalue and eigenvector
 *   Graph - input data about the graph is converted into the element of struct Graph data type,
 *   which holds number of nodes in the graph (n), degree vector, sum of degrees M and Adj matrix in sparse format
 *   Group - while initial graph is divided into the groups, each group is stored and manipulated in the format
 *   of struct Group data type, with the size of the group, indices of the elements from initial graph, indices of
 *   the elements from Adj matrix and its size, as well as pointer to the next group in the set left
 *   Final_List - for the groups added to this composite data type stores number of nodes, number of groups
 *   and their indices respectively; used in order to maintain the final set to be written in the output file
 *
 */

#ifndef PROJECT_TOHNA_STRUCTURES_H
#define PROJECT_TOHNA_STRUCTURES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IS_POSITIVE(X) ((X) > 0.00001)
#define NEGINFINITY -1000000000.0

typedef struct Vector_int {
    int size;
    int *data;
}Vector_int;

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

typedef struct Group{
    int *indices;
    int group_size;
    int *Adj_indices;
    int Adj_size;
    struct Group* next;
}Group;


typedef struct Final_List_{
    int total_nodes;
    int total_groups;
    int* nodes_group_ind;
}Final_List;

#endif


