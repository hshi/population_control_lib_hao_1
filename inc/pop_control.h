#ifndef POP_CONTROL_H
#define POP_CONTROL_H

#include <iostream>
#include <vector>
#include "mpi_fun.h"

//size is MPISize(), only call pop_configuration for one thread
std::vector<int> pop_configuration(int size, const std::vector<double>& weight);

void deter_send_number(int& send_number, std::vector<int>& send_number_list, const std::vector<int>& table);

void deter_table_send(int send_number, const std::vector<int>& send_number_list, const std::vector<int>& table, std::vector<int>& table_send);

template<class T >
void pop_control(std::vector<T>& walker, const std::vector<int>& table)
{
    int rank=MPIRank(); int size=MPISize(); int L_chunk=walker.size();
    int L=0; if(rank==0) L=table.size(); MPIBcast(L);
    if( (L_chunk*size) !=  L ) {std::cout<<"ERROR!!! Size of table can not be divided by MPISize."<<std::endl; exit(1);}

    if(size==1) //Serial
    {
        int j;
        for(int i=0; i<L; i++)
        {
            j=table[i]; //j is the parent 
            if(i!=j) walker[i]=walker[j]; 
        }
    }
    else if(size>1) //MPI
    {
        //Determine table_recv
        std::vector<int> table_recv(L_chunk);
        MPI_Scatter(table.data(), L_chunk, MPI_INT, table_recv.data(), L_chunk, MPI_INT, 0, MPI_COMM_WORLD);

        //Determine the number each thread will send out, send_number_list is the list only in main thread
        int send_number;
        std::vector<int> send_number_list;
        deter_send_number(send_number, send_number_list, table);

        //Determine_table_send
        std::vector<int> table_send; //Parent is 0~send_number, child is send_number~2*send_number
        deter_table_send(send_number, send_number_list, table, table_send);
    }
    else
    {
        std::cout<<"ERROR!!!Something is wrong with size, must be >=1."<<std::endl; exit(1);
    }
}

#endif
