/*
Implement a reduce by using send and receive.
Execute average, min and max over the set of data collected.
*/

#include "mpi.h"
#include "stdio.h"

int main (int argc, char** argv) {
	int rank;
	int comm_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	int value, min, max;
	int local_value = rank;

	MPI_Reduce(&local_value, &value, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_value, &min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	MPI_Reduce(&local_value, &max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

	if (rank == 0) {
		printf("the global value is: %d\n", value);
		printf("the min is: %d\n", min);
		printf("the max is: %d\n", max);
		printf("the avg is: %d\n", value/comm_size);
	}

	
	MPI_Finalize();
}
