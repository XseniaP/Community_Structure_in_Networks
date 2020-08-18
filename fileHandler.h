

#ifndef PROJECT_TOHNA_FILEHANDLER_H
#define PROJECT_TOHNA_FILEHANDLER_H
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct Graph {
    int number_of_nodes;
    int **data;
}Graph;



int readFile(char *fileName, struct Graph *graph);


int writeToFile(char* fileName);


#endif //PROJECT_TOHNA_FILEHANDLER_H
