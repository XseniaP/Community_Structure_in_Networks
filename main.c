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
//    int k[191] = {30,5,1,6,7,11,15,5,0,6,14,22,27,5,4,17,22,24,25,4,6,16,17,20,3,2,11,17,5,9,10,22,26,29,6,0,1,3,7,18,25,4,0,6,16,18,5,11,15,16,19,22,5,5,14,15,24,27,7,5,11,14,22,27,28,29,8,0,4,8,10,12,13,26,28,6,11,14,17,18,19,28,5,11,14,18,26,29,8,1,9,10,12,13,17,25,28,5,0,8,9,21,29,4,3,7,8,23,5,2,3,4,12,14,6,6,7,12,13,23,26,4,8,12,24,29,3,3,23,27,4,15,23,27,29,8,1,2,5,8,10,26,27,29,6,16,18,20,21,24,29,5,2,9,19,23,28,3,2,6,14,5,5,11,13,18,22,6,1,9,10,20,21,22,6,10,11,12,14,24,29,9,5,10,13,15,19,21,22,23,28};
//    FILE * f2 = NULL; int n;
//    f2 = fopen("graph_test_30m.in", "wb");
//    assert(f2 != NULL);
//    n = fwrite(&k, sizeof(int), 191, f2);
//    assert(n==191);
//    fclose(f2);


    return 0;

}
