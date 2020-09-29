
/** Power_iter module summary:
 *
 * this module implements Power Iteration methods and its supporting functions
 *
 * The module implements the following Functions:
 * create_vec - creates random vector
 * vec_mult_B_shifted - multiplies vector by symmetric shifted matrix B; the multiplication is done in O(m+n) time
 *                      in a step-by-step manner -> Bx = Ax - k(kT * x)/M - delta*I*x + ||C||*I*x
 * norm_vec - normalize vector
 * check_difference - checks the difference between two vectors and compares to the tolerance level in order to keep
 * iterating or to return leading eigenvector
 * matrix_shift_C_new - ||C|| (max abs values sum of the column) calculation for the shifted matrix
 * indices_to_indices_set - function which gets list of indices included in specific sub-group and returns binary vector
 * according to the nodes indices of the original graph - i.e. indices marked with 1 are the elements in the subgroup, 0 otherwise
 * calculate_dq - calculate delta Q (modularity change)
 * powerIteration - power iteration method which call the rest of the function from this module: starts with the random vector,
 * and keeps multiplying by matrix before reaching the convergence; the error code is returned and program is interrupted
 * if the convergence didn't happen
 */

#ifndef PROJECT_TOHNA_POWER_ITER_H
#define PROJECT_TOHNA_POWER_ITER_H
#include "structures.h"
#include <math.h>
#include <time.h>
#include "safe_memory.h"

int create_vec(Group* g, int size, double *vec);
int vec_mult_B_shifted(Graph* graph,Group* g_p, double *rand_vec, double max,double *row_norm,Vector_double *row_sums_p);
int norm_vec (Graph* graph,Group* g_p, double *rand_vec, double max, double *row_norm,Vector_double *row_sums_p);
int check_difference(int height ,double *temp ,double *next);
int powerIteration(Graph* graph, Group* g, Pair* pair_p, Vector_double *row_sums_p);
int matrix_shift_C_new(Graph* graph,Group* g, double* max_p, Vector_double *row_sums_p);
int indices_to_indices_set(Group* group, int *indices, int size, int* indices_set, int marker);
int calculate_dq(Graph* graph,Group* g_p, int *s_p, Vector_double *row_sums_p, double* dq_p);

#endif


