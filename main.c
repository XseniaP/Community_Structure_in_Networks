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
//    int k[25] = {8,1,4,3,2,3,5,3,1,3,5,3,1,2,5,1,0,3,1,2,3,1,7,1,6};
//    FILE * f2 = NULL; int n;
//    f2 = fopen("graph_test_7m.in", "wb");
//    assert(f2 != NULL);
//    n = fwrite(&k, sizeof(int), 25, f2);
//    assert(n==25);
//    fclose(f2);


    return 0;

}
