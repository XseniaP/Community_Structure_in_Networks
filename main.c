#include "fileHandler.h"
#include "Algo2.h"
//start

int main() {
    printf("Hello, World!\n");
    Graph new = {0,NULL};
    struct Graph *myGraph = &new;
//    myGraph = { 0, NULL };

    int a = readFile("graph.in", myGraph);
    assert(a == 0);
    if(a)
        return 1;
    else
        divide_in_two(myGraph);

    printf("Exiting...\n");
    return 0;
}