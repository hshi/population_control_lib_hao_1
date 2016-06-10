#include <iomanip>
#include <algorithm>
#include "random_hao.h"
#include "pop_control.h"

using namespace std;

void pop_configuration_test()
{
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
    int L_chunk=5; int L=L_chunk*MPISize();
    vector<double> walker(L_chunk);
    vector<int> table;

    if(MPIRank()==0) 
    {
        table.reserve(L);
        for(int i=0; i<L; i++) table.push_back(i);
        random_shuffle ( table.begin(), table.end() );
        for(int i=0; i<L; i++) cout<<table[i]<<" "; cout<<endl;
    }
    pop_control(walker, table); 
}


void pop_control_test()
{
    pop_configuration_test();
    pop_control_double_test();
}
