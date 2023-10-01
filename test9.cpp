#include<iostream>
#include"mpi.h"
using namespace std;

int main(int argc, char** argv)
{
	int rank, size,sum=0;
	int* send_buffer;
	int* recv_buffer;
	int* buffer;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0)
	{
		for (int i=0; i < 100; i++)
		{
			send_buffer[i] = i+1; 
		}
	}
	recv_buffer = new int [25];
	MPI_Scatter(send_buffer,25,MPI_INT,recv_buffer,25,MPI_INT,0,MPI_COMM_WORLD);
	buffer = new int [25];
	MPI_Reduce(recv_buffer,buffer,25,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
	if (rank == 0)
	{
		for (int i=0; i < 25; i++)
		{
			sum = sum + buffer[i];
		}
		cout<<rank<<" "<<sum<<"\n";
	}

	delete [] recv_buffer;
	delete [] buffer;
	MPI_Finalize();
}