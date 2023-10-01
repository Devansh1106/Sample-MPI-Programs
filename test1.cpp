#include <iostream>
#include"mpi.h"
using namespace std;
int main(int argc, char** argv) {
  int rank, n_ranks;

  // First call MPI_Init
  MPI_Init(&argc, &argv);

  // Check that there are two ranks
  //MPI_Comm_size(MPI_COMM_WORLD,&n_ranks);
  // if( n_ranks != 2 ){
  //   cout<<"This example requires exactly two ranks\n";
  //   MPI_Finalize();
  //  }

  // Get my rank
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if( rank % 2 == 0 )
	{
		char* message = "Hello, world!\n";
	    MPI_Send(message, 16, MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
	}

	if( rank % 2 !=0 )
	{
		char message[16];
	    MPI_Status  status;
	    MPI_Recv(message, 16, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD, &status);
	    cout<<message;
	}

  // Call finalize at the end
  MPI_Finalize();
}
