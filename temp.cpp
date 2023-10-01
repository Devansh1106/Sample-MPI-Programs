#include <iostream>
#include "mpi.h"
using namespace std;

int main(int argc, char** argv)
{
   int rank, n_ranks;
   char send_message[40] = "Hello world by rank\n";
   char *recv_message;
   MPI_Init(&argc,&argv);
   recv_message = new char [40];

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);
   MPI_Gather(send_message,40,MPI_CHAR,recv_message,40,MPI_CHAR,0,MPI_COMM_WORLD);
   if (rank == 0)
   {
    for (int i =0; i < n_ranks; i++)
    {
      cout<<recv_message;
    }
   }
   delete[] recv_message;
   MPI_Finalize();
}