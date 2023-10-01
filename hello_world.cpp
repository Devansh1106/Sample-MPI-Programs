#include<iostream>
#include "mpi.h"
using namespace std;
int main(int argc , char **argv)
{
	MPI_Init(&argc,&argv);
	int my_rank;
	int process;
	MPI_Comm_size(MPI_COMM_WORLD, &process);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	cout<<"Hello World is from rank "<<my_rank<<" process out of "<<process<<" Processes.";
	cout<<"\n";
	MPI_Finalize();

}