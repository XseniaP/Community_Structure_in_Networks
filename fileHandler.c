
#include "fileHandler.h"
#include "Group_handler.h"

int readFile(char *fileName, struct Graph *graph) {
    int buffer1, buffer2,adj_loc=0,n = 0, i = 0, j=0, m=0;
    FILE * stream; unsigned long a;
    stream = fopen(fileName, "r");
    if(stream == NULL){
        printf("Error reading the file\n");
        return 1;
    }

    fread(&n, sizeof(int), 1, stream);
    graph->number_of_nodes = n;
    graph->deg_vec->size = n;
    graph->deg_vec->data = (int*) safe_malloc( n * sizeof(int));

    for (i=0; i<graph->number_of_nodes; i++){
        a = fread(&buffer1, sizeof(int), 1, stream);
        if (a == 0)
            break;
        graph->deg_vec->data[i] = buffer1;
        m+= buffer1;
        fseek(stream, buffer1* sizeof(int), SEEK_CUR);
    }
    graph->M = m;
    graph->adj_matrix->size = m/2;

    /*size of ADJ matrix will be 1/2 of total degrees M, storing one of the symmetric halves in sparse matrix format, can allocate memory now*/
    graph->adj_matrix->row = (int*) safe_malloc( graph->M/2* sizeof(int));
    graph->adj_matrix->col = (int*) safe_malloc( graph->M/2* sizeof(int));
    rewind(stream);
    a = fread(&buffer1, sizeof(int), 1, stream);
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

    fclose(stream);
    return 0;
}

int writeToFile(char* fileName, Group* final_cluster_p){
    int n=0;
    FILE *f = fopen(fileName, "wb");
    Group *temp = final_cluster_p;

    while(temp != NULL){
        temp = temp->next;
        n++;
    }

    n = fwrite(&n, sizeof(int), 1, f);
    if (n!=1){
        printf("couldn't write number of groups into the file");
        exit(1);
    }

    /** complexity is O(n) */
    temp = final_cluster_p;
    while(temp != NULL){

        n = fwrite(&temp->group_size, sizeof(int), 1, f);
        if (n!=1){
            printf("couldn't write size of group into the file");
            exit(1);
        }

        n = fwrite(&temp->indices[0], sizeof(int), temp->group_size, f);
        if (n!= temp->group_size){
            printf("couldn't write indices of group into the file");
            exit(1);
        }
        pop(&temp);
    }
    fclose(f);
    return 0;
}
