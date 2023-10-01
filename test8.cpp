//MPI_Bcast don't require recv_buffer. It sends the copy of the data.
//hence for printing used loop over send_buffer for printing whole 
//content.


#include<iostream>
#include"mpi.h"
using namespace std;

int main(int argc, char** argv)
{
	int rank,size;
	int* send_buffer;


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	send_buffer = new int [2];
	if (rank == 0)
	{
		send_buffer[0] = 1;
	 	send_buffer[1] = 3; 
	}

	
	MPI_Bcast(send_buffer,2,MPI_INT,0,MPI_COMM_WORLD);
	for (int i = 0;i < 2; i++)
	{
		cout<<rank<<" "<<send_buffer[i]<<"\n";
	}

	delete [] send_buffer;

	MPI_Finalize();
}