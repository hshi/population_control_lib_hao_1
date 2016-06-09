#include <iomanip>
#include "random_hao.h"
#include "mpi_fun.h"
#include "pop_control.h"

using namespace std;

vector<long> pop_configuration(long size, const vector<double>& weight)
{
    //Set size
    long L=weight.size(); long L_chunk=L/size;
    if( (L_chunk*size) !=  L ) {cout<<"ERROR!!! Size of weight can not be divided by Size (suppose to be MPISize) "<<endl; exit(1);}

    //Probability function: normalized weight
    double sum=0.0; for(long i=0; i<L; i++) sum+=weight[i];
    vector<double> prob(L); for(long i=0; i<L; i++) prob[i]=weight[i]/sum;

    //Set num transfer
    vector<long> number(L,0); 
    double prob_sum_new;
    int index_old=0; double prob_sum_old=prob[0];
    for(long i=0; i<L; i++)
    {
        prob_sum_new=( i+uniform_hao() ) / (L*1.0);
        while( prob_sum_new>prob_sum_old )
        {
            index_old++;
            prob_sum_old+=prob[index_old]; 
        }
        number[index_old]++;
        //We used to only use following formula
        //table[i]=index_old; 
        //Currently change to vector<long> number to get high efficiency
    }

    //Initial table
    vector<long> table(L);
    for(long i=0; i<L; i++) { if(number[i] !=0 ) table[i]=i; }

    long zero_i, one_i, max_i;

    //Exchange between one thread
    for(long i=0; i<size; i++)
    {
        zero_i=L_chunk*i; one_i=L_chunk*i; max_i=L_chunk*(i+1);
        while(number[zero_i] !=0 && zero_i<max_i ) zero_i++; //number[zero_i]=0 or zero_i is out of range
        while(number[one_i]  <=1 && one_i<max_i  ) one_i++;  //number[one_i]>1  or one_i  is out of range

        while(zero_i<max_i && one_i<max_i)
        {
            table[zero_i]=one_i; 
            number[zero_i]++;
            number[one_i]--;
 
            while(number[zero_i] !=0 && zero_i<max_i ) zero_i++;
            while(number[one_i]  <=1 && one_i<max_i  ) one_i++;
        }
    }

    //Exchange between threads
    if(size>1)
    {
        zero_i=0; one_i=0; max_i=L;
        while(number[zero_i] !=0 && zero_i<max_i ) zero_i++; //number[zero_i]=0 or zero_i is out of range
        while(number[one_i]  <=1 && one_i<max_i  ) one_i++;  //number[one_i]>1  or one_i  is out of range

        while(zero_i<max_i && one_i<max_i )
        {
            table[zero_i]=one_i; 
            number[zero_i]++;
            number[one_i]--; 

            while(number[zero_i] !=0 && zero_i<max_i ) zero_i++;
            while(number[one_i]  <=1 && one_i<max_i  ) one_i++;
        }
    }

    //Check
    for(long i=0; i<L; i++) 
    {
        if(number[i]!=1) {cout<<"ERROR!!!! After pop configuration, number of each walker is not 1!"<<endl; exit(1);}
    }

    return table;
}
