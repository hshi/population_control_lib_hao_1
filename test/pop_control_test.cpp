#include "pop_control.h"

using namespace std;

void pop_configuration_test()
{
    vector<double> a(3); a[0]=1.0;a[1]=2.0; a[2]=3.0;
    vector<long> b=pop_configuration(a);
}

void pop_control_test()
{
    pop_configuration_test();
}
