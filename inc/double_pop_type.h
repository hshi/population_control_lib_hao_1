#ifndef DOUBLE_POP_TYPE_H
#define DOUBLE_POP_TYPE_H

#include <iostream>
#include <vector>

class Double_pop
{
   public:
    int Nbuf;
    double* number;

    Double_pop();
    Double_pop(double& number_in);
    ~Double_pop();

    Double_pop& operator  = (const Double_pop& x);

    std::vector<char> pack();
    void unpack(const std::vector<char>& buf);
};


#endif
