
#include "fileHandler.h"

int readFile(char *fileName, struct Graph *graph) {
    int buffer,n = 0, numberOfNodes = 0, big_array_count = 0, i = 0;
    int **array = NULL;

    FILE * stream;
    stream = fopen(fileName, "r");
    if(stream == NULL){
        printf("Error reading the file\n");
        return 1;
    }

    fread(&n, sizeof(int), 1, stream);
    printf("There are %d nodes in the graph\n",n);
    graph->number_of_nodes = n;

    array = (int**) malloc( n * sizeof(int*));

    while (!feof(stream)){
        unsigned long a = fread(&buffer, sizeof(int), 1, stream);
        //assert(a == 1);
        if (a == 0)
            break;

        printf("V: %d\n", buffer);
        numberOfNodes = buffer;
        array[big_array_count] = (int*)malloc(numberOfNodes * sizeof(int));
        printf("nodes:[");

        for (i=0; i<numberOfNodes; i++){
            fread(&buffer, sizeof(int), 1, stream);
            array[big_array_count][i] = buffer;
            printf("%d ", buffer);
        }

        big_array_count++;
        printf("]\n");
    }

    graph->data = array;
    fclose(stream);
    return 0;

}

int writeToFile(char* fineName){

    return 0;
}