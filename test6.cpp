//Summation of elements from 1 to 100 by dividing it in
//groups of 25 for each rank and for 4 ranks in total
//using gather only


#include<iostream>
#include"mpi.h"
using namespace std;

int main(int argc,char **argv)
{
	int sum=0,rank,size,limit,steps,final_sum=0;
	int* send_buffer;
	int* recv_buffer;

	limit = 100;

	MPI_Init(&argc,&argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	steps = limit/size;
	for(int i=(steps*rank)+1; i<=steps*(rank+1); i++)
	{
		sum = i + sum;
	}
	send_buffer = &sum;
	recv_buffer = NULL;
	if (rank == 0)
	{
		recv_buffer = new int [4];
	}
	MPI_Gather(send_buffer,1,MPI_INT,recv_buffer,1,MPI_INT,0,MPI_COMM_WORLD);
	if (rank == 0)
	{
		for (int i=0; i < 4; i++)
		{
			final_sum = recv_buffer[i] + final_sum;
		}
		cout<<final_sum<<"\n";
	}
	if (rank == 0)
	{
		delete [] recv_buffer;
	}
	MPI_Finalize();
}