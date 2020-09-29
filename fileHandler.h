/** File_handler module summary:
 *
 * this module allows to read from the input file and write into the output file
 *
 * The module implements the following Functions:
 *
 * readFile - reads the graph from the input file and creates an element of type struct Graph (incl. Adjacency matrix,
 *            Degree vector, Number of nodes, M listed)
 * writeToFile - writes into the output file the number of indivisible groups identified in the network followed
 *            by the nodes of each group respectively
 */

#ifndef PROJECT_TOHNA_FILEHANDLER_H
#define PROJECT_TOHNA_FILEHANDLER_H

#include "structures.h"
#include "safe_memory.h"


int readFile(char *fileName, Graph *graph);
//int writeToFile(char* fileName, Final_List* final_cluster_p);
int writeToFile(char* fileName, Group* final_cluster_p);

#endif
