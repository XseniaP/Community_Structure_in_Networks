

#ifndef PROJECT_TOHNA_FILEHANDLER_H
#define PROJECT_TOHNA_FILEHANDLER_H

#include "structures.h"


int readFile(char *fileName, struct Graph *graph);
int produce_input_set(struct Graph *graph);


int writeToFile(char* fileName, struct Graph *graph);


#endif //PROJECT_TOHNA_FILEHANDLER_H
