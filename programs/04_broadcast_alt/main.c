/*
Design a broadcast solution bu using send and recv calls
*/

#include "mpi.h"
#include "stdio.h"

int main(int argc, char** argv) {
	int rank, comm_size;

	MPI_Init(&argc, &argv);	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	if (rank == 0) {
		int data = 64;
		printf("process %d is sending data: %d\n", rank+1, data);
		for (int i = 1; i < comm_size; ++i) {
			MPI_Send(&data, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
	} else {
		int data;
		MPI_Recv(&data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("process %d received data: %d\n", rank+1, data);	
	}


	MPI_Finalize();
	return 0;
}
