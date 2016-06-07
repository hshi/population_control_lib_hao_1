#include "pop_control.h"

using namespace std;

vector<long> pop_configuration(const vector<double>& weight)
{
    long L=weight.size();
    vector<long> table(L);

    double sum=0.0; for(long i=0; i<L; i++) sum+=weight[i];
    vector<double> p_weight(L); for(long i=0; i<L; i++) p_weight[i]=weight[i]/sum;

    for(long i=0; i<L; i++) cout<<p_weight[i]<<" ";
    return table;
}
