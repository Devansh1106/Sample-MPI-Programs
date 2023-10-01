#include<iostream>
#include"mpi.h"
using namespace std;
int main(int argc , char** argv)
{
	MPI_Init(&argc,&argv);
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank!=0)
	{
		char *msg = "hello again, world!\n";
		MPI_Send(msg,25,MPI_CHAR,0,10,MPI_COMM_WORLD);
	}
	 if (rank == 0)
	 {
	 	for (int i =1;i < size; i++)
	 	{
	 	char buffer[25];
	 	MPI_Status status;
	 	MPI_Recv(buffer, 25,MPI_CHAR, i,10,MPI_COMM_WORLD,&status);
	 	cout<<buffer;	 		
	 	}
	 }
	 MPI_Finalize();
}