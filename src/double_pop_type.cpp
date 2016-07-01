#include "mpi_fun.h"
#include "double_pop_type.h"

using namespace std;
int Double_pop::Nbuf = 8;

Double_pop::Double_pop() {}

Double_pop::Double_pop(double& number_in) {number=&number_in;}

Double_pop::~Double_pop() {}

Double_pop& Double_pop::operator  = (const Double_pop& x)
{
    *number=*(x.number);
    return *this;
}

#ifdef MPI_HAO

vector<char> Double_pop::pack() const
{
    vector<char> buf(Nbuf);

    int posit=0;
    MPI_Pack(number, 1, MPI_DOUBLE, buf.data(), Nbuf, &posit, MPI_COMM_WORLD);
    if(posit!=Nbuf) {cout<<"ERROR in pack!!! posit does not equal Nbuf! "<<endl; exit(1);}

    return buf;
}

void Double_pop::unpack(const vector<char>& buf)
{
    int Nbuf_test=buf.size();
    if(Nbuf_test!=Nbuf) {cout<<"ERROR in unpack!!! Size of input buf does not equal Nbuf! "<<endl; exit(1);}

    int posit=0;
    MPI_Unpack(buf.data(), Nbuf, &posit, number, 1, MPI_DOUBLE, MPI_COMM_WORLD);
    if(posit!=Nbuf) {cout<<"ERROR in unpack!!! posit does not equal Nbuf! "<<endl; exit(1);}
}

#endif
