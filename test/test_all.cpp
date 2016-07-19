#include <iostream>
#include "mpi_fun.h"
#include "random_hao.h"

using namespace std;

void pop_control_test();

int main(int argc, char** argv)
{
    MPIInitFunnel(argc,argv);

    if( MPIRank()==0 ) cout<<"\n\n\n=======Testing======="<<endl;
    pop_control_test();

    MPIFinalize();

    return 0;
}
