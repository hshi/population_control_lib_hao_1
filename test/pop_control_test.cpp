#include <iomanip>
#include <algorithm>
#include "random_hao.h"
#include "double_pop_type.h"
#include "pop_control.h"

using namespace std;

void pop_configuration_test()
{
    random_hao_init(985456376,1); //Random number seed is important for the test
    int L=100; int size=4;
    vector<double> a(L); for(int i=0; i<L; i++) a[i]=i+1.0;
    if(MPIRank()==0) 
    {
        vector<int> b_exact(L); //Exact results from old fortran code
        b_exact={60,62,66,69,71,73,75,8,77,80,82,82,13,14,84,85,87,88,90,20,92,22,23,92,25,32,44,28,93,30,94,32,96,34,
           35,97,37,38,39,40,98,42,99,44,45,100,47,48,49,50,51,52,53,53,55,56,57,58,59,60,55,62,63,64,65,66,67,68,
           69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
        vector<int> b=pop_configuration(size, a);

        int flag=0;
        for(int i=0; i<L; i++) 
        {
            if( (b[i]+1-b_exact[i]) !=0 ) flag++;
        }
        if(flag==0) cout<<"Pop_configuration passed the test!\n";
        else cout<<"Warning!!!!Pop_configuration failed the test!\n";
    }
}

void pop_control_double_test()
{
    random_hao_init(0,1);

    int rank=MPIRank(); int size=MPISize(); 
    int L_chunk=100; int L=L_chunk*size;
    vector<double> walker(L_chunk);
    vector<int> table;

    //Set walker
    for(int i=0; i<L_chunk; i++) walker[i]=1.0*i+rank*L_chunk;

    if(rank==0) 
    {
        //Random set weight
        vector<double> weight(L); for(int i=0; i<L; i++) weight[i]=5.0*uniform_hao();
        table=pop_configuration(size,weight);
        //for(int i=0; i<L; i++) cout<<table[i]<<" "; cout<<endl;
    }

    vector<Double_pop> walker_pop; 
    walker_pop.reserve(L_chunk); for(int i=0; i<L_chunk; i++) walker_pop.push_back( Double_pop(walker[i]) );
    pop_control(walker_pop, table);

    vector<double> walker_gather; if(rank==0) walker_gather.resize(L);
#ifdef MPI_HAO
    MPI_Gather(walker.data(), L_chunk, MPI_DOUBLE, walker_gather.data(), L_chunk, MPI_DOUBLE, 0, MPI_COMM_WORLD);
#else
    walker_gather=walker;
#endif

    if(rank==0)
    {
        int flag=0;
        for(int i=0; i<L; i++)
        {
            if(std::abs(walker_gather[i]-table[i]*1.0)>1e-15) flag++;
        }
        if(flag==0) cout<<"Pop_control passed double test!\n";
        else cout<<"Warning!!!!Pop_control failed double test!\n";
    } 
    //if(rank==0) for(int i=0; i<L; i++) cout<<walker_gather[i]<<" "; cout<<endl; 
}


void pop_control_test()
{
    pop_configuration_test();
    pop_control_double_test();
}
