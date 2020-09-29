
/** Group_handler module summary:
 *
 * this module allows to manage the set of groups which have to be divided yet (aka "set P")
 * and the indivisible groups which are ready to be written to the output file (aka "set O")
 *
 * The module implements the following Functions:
 *
 * add_group_to_final_cluster - adds indivisible group to the final set / "set O"
 * push - adds the group to "set P" (stack of groups to be divided)
 * pop -  removes the group from "set P", doesn't return the group (!)
 * top - returns first group in the "set P"
 */

#ifndef PROJECT_TOHNA_GROUP_HANDLER_H
#define PROJECT_TOHNA_GROUP_HANDLER_H
#include "structures.h"
#include "safe_memory.h"

void push(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack);
void pop(struct Group** stack);
Group* top(struct Group* stack);
int add_group_to_final_set(int Adj_size,int group_size,int* indices, int *Adj_indices, struct Group** stack);

#endif


