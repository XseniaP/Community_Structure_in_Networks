#include "Algo2.h"
#include "structures.h"

int main(int argc,char* argv[]) {

    /*check command line args*/
    if (argc<3){
        printf("Command line arguments missing\n");
        return 1;
    }
    divide_network(argv);
    return 0;
}
