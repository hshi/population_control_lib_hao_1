#ifndef DOUBLE_POP_TYPE_H
#define DOUBLE_POP_TYPE_H

#include <iostream>
#include <vector>

class Double_pop
{
   public:
    static int Nbuf;
    double* number;

    Double_pop();
    Double_pop(double& number_in);
    ~Double_pop();

    Double_pop& operator  = (const Double_pop& x);

#ifdef MPI_HAO
    std::vector<char> pack() const;
    void unpack(const std::vector<char>& buf);
#endif
};

#endif
