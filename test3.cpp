#include<iostream>
#include"mpi.h"
using namespace std;

int main(int argc, char** argv) {
   int rank, n_ranks, neighbour;
   int n_numbers = 10000;
   int *send_message;
   int *recv_message;
   MPI_Status status;

   send_message = new int [n_numbers];
   recv_message = new int [n_numbers];

   // First call MPI_Init
   MPI_Init(&argc, &argv);

   // Get my rank and the number of ranks
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &n_ranks);

   // Check that there are exactly two ranks
   if( n_ranks != 2 ){
        printf("This example requires exactly two ranks\n");
        MPI_Finalize();
        return(1);
   }

   // Call the other rank the neighbour
   if( rank == 0 ){
      neighbour = 1;      
   } 
   else {
      neighbour = 0;
   }

   // Generate numbers to send
   for( int i=0; i<n_numbers; i++){
      send_message[i] = i;
   }

   // Send the message to other rank
   MPI_Send(send_message, n_numbers, MPI_INT, neighbour, 0, MPI_COMM_WORLD);

   // Receive the message from the other rank
   MPI_Recv(recv_message, n_numbers, MPI_INT, neighbour, 0, MPI_COMM_WORLD, &status);
   cout<<"Message received by "<<rank<<" "<<"\n";

   delete[] send_message;
   delete[] recv_message;

   // Call finalize at the end
   MPI_Finalize();
}