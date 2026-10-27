#include "mpi/mpi.h"
#include <stddef.h>
#include <stdio.h>

int main(int argc, char** argv) {
    	int world_size;
    	int world_rank;

   	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	printf("hello from process rank %d out of %d processors\n", world_rank, world_size);

    	MPI_Finalize();
}
