
//use while in this program for exiting after 1 million times!


#include<iostream>
#include"mpi.h"
using namespace std;
int main(int argc, char** argv)
{
	int rank,size,count0=0,count1=0;
	char* msg = "ball";
	int bored = 0;
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if ( size != 2)
	{
		cout<<"Total number of processes should be 2!";
		MPI_Finalize();
	}
	while(bored == 0)
	{
		if (rank == 0)
		{
			MPI_Send(&msg,8,MPI_CHAR,1,10,MPI_COMM_WORLD);
			MPI_Recv(&msg,8,MPI_CHAR,1,20,MPI_COMM_WORLD,&status);
			count0 += 1;
			if (count0 >= 1000000)
			{
				bored = 1;
			}
		}

		if (rank == 1)
		{
			MPI_Recv(&msg,8,MPI_CHAR,0,10,MPI_COMM_WORLD,&status);
			count1 += 1;
				if ( count1 >= 1000000)
			{
				bored = 1;
			}
			MPI_Send(&msg,8,MPI_CHAR,0,20,MPI_COMM_WORLD);
		}
	}
	MPI_Finalize();
	if (count1==1000000)
	{
		cout<<"Rank 1 gave up!\n";
	}
	else
	{
		cout<<"Rank 0 gave up!\n";
	}
}