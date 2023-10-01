//creating a array pointer at each rank from number 1 to 10,11 to 20,
//21 to 30, 31 to 40. Then find summaton and maximum number of all.





#include<iostream>
#include "mpi.h"
using namespace std;
int main(int argc , char** argv)
{
	int n_numbers=10;
	int* vector;
	int rank,size;
	int* recv_buffer;
	int* max;
	int* recv_buffer_1;
	int* recv_buffer_2;

	recv_buffer_2 = new int [1];
	recv_buffer_1 = new int [10];
	recv_buffer = NULL;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	vector = new int[n_numbers];
	for (int i = (rank*n_numbers)+1; i<= (rank+1)*n_numbers; i++)
	{
		vector[i-1] = i;		//for filling the array with numbers
	}

	MPI_Reduce_local(vector, recv_buffer_1,n_numbers, MPI_INT, MPI_SUM);
	if (rank == 0)
	{
		recv_buffer = new int [1];
		max = new int [1];
	}
	MPI_Reduce(recv_buffer_1, recv_buffer,1, MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);
	if ( rank == 0)
	{
		cout<<"Summation of the numbers is:"<<" "<<recv_buffer<<"\n";
	}
	MPI_Reduce_local(vector,recv_buffer_2,1,MPI_INT,MPI_MAX);
	MPI_Reduce(recv_buffer_2, max,1,MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		cout<<"Maximum of the numbers is:"<<" "<<max<<"\n";
	}
	MPI_Barrier(MPI_COMM_WORLD);
	delete [] vector;
	delete [] recv_buffer_1;
	if ( rank ==0 )
	{
		delete [] recv_buffer;
		delete [] max;
	}
	
	MPI_Finalize();
}