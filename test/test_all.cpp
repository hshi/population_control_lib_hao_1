#ifdef MPI_HAO
#include <mpi.h>
#endif
#include <iostream>

//#include "thread_mc_data_manipulate.h"

using namespace std;

//void mc_data_manipulate_test();

int main(int argc, char** argv)
{
    int rank=0;

#ifdef MPI_HAO
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#endif

    if(rank==0) cout<<"\n\n\n=======Testing======="<<endl;
    //mc_data_manipulate_test();

#ifdef MPI_HAO
    MPI_Finalize();
#endif

    return 0;
}
