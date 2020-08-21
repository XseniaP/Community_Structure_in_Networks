
#include "fileHandler.h"

int readFile(char *fileName, struct Graph *graph) {
    int buffer1, buffer2,adj_loc=0,n = 0, i = 0, j=0, m=0;
    FILE * stream;
    stream = fopen(fileName, "r");
    if(stream == NULL){
        printf("Error reading the file\n");
        return 1;
    }

    fread(&n, sizeof(int), 1, stream);
    printf("There are %d nodes in the graph\n",n);
    graph->number_of_nodes = n;
    graph->deg_vec->size = n;
    graph->deg_vec->data = (int*) malloc( n * sizeof(int));

    for (i=0; i<graph->number_of_nodes; i++){
        unsigned long a = fread(&buffer1, sizeof(int), 1, stream);
        if (a == 0)
            break;
        graph->deg_vec->data[i] = buffer1;
        m+= buffer1;
        fseek(stream, buffer1* sizeof(int), SEEK_CUR);
    }
    graph->M = m;

    //size of ADJ matrix will be 1/2 of total degrees M, storing one of the symmetric halves in sparse matrix format, can allocate memory now
    graph->adj_matrix->row = (int*) malloc( graph->M/2* sizeof(int));
    graph->adj_matrix->col = (int*) malloc( graph->M/2* sizeof(int));
    rewind(stream);
    unsigned long a = fread(&buffer1, sizeof(int), 1, stream);
    if (a == 0) {
        printf("error reading the file after rewind\n");
        return 1;
    }

    for (i=0; i<graph->number_of_nodes; i++){
        unsigned long a = fread(&buffer1, sizeof(int), 1, stream);
        if (a == 0)
            break;
        for (j=0; j<buffer1; j++){
            fread(&buffer2, sizeof(int), 1, stream);
            if (i>buffer2){
                graph->adj_matrix->row[adj_loc] = i;
                graph->adj_matrix->col[adj_loc] = buffer2;
                adj_loc+=1;
            }
        }
    }

//    //print adjacency matrix
//    for (i=0; i<=graph->M/2; i++){
//        printf("%c",'\n');
//        printf("%d %d", graph->adj_matrix->row[i],graph->adj_matrix->col[i]);
//    }

    fclose(stream);
    return 0;
}

int writeToFile(char* fineName, struct Graph *graph){



    return 0;
}