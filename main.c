#include "Algo2.h"
#include "structures.h"

int main(int argc,char* argv[]) {
    int** output={NULL}; int*** output_p;
    output_p = &output;

    ///check command line args
    if (argc<3){
        printf("Command line arguments missing\n");
        return 1;
    }
    divide_network(argv, output_p);


////    create new file with the nodes
//    int k[11] = {6,1,5,1,3,0,1,1,0,1,0};
//    FILE * f2 = NULL; int n;
//    f2 = fopen("graph_test4.in", "wb");
//    assert(f2 != NULL);
//    n = fwrite(&k, sizeof(int), 11, f2);
//    assert(n==11);
//    fclose(f2);


    return 0;

}
