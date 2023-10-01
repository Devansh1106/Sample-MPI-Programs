//Summation of elements from 1 to 100 by dividing it in
//groups of 25 for each rank and for 4 ranks in total
//using scatter and gather

//If Allgather is used then result array "temp" will be at all ranks
//so remove if (rank == 0) things then print.

#include<iostream>
#include"mpi.h"
using namespace std;

int main(int argc, char** argv)
{
	int rank, size,sum=0;
	int* send_buffer;
	int* recv_buffer;
	int* temp;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	temp = NULL;
	send_buffer = NULL;
	if (rank == 0)
	{
		send_buffer = new int [100];
		for (int i = 0; i < 100; i++)
		{
			send_buffer[i] = i+1;
		}
	}
	recv_buffer = new int [25];
	MPI_Scatter(send_buffer,25,MPI_INT,recv_buffer,25,MPI_INT,0,MPI_COMM_WORLD);

	for (int i=0; i < 25; i++)
	{
		sum = recv_buffer[i] + sum;
	}
		temp = new int [4];
	// if (rank == 0)
	// {
	// }
	MPI_Allgather(&sum,1,MPI_INT,temp,1,MPI_INT,MPI_COMM_WORLD);
	//if (rank == 0)
	//{
		for (int i=0; i < 4; i++)
		{
			cout<<rank<<" "<<temp[i]<<"\n";
		}
		delete [] send_buffer;
	//}
	delete [] recv_buffer;
	delete [] temp;
	MPI_Finalize();
}