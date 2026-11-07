#include "mpi.h"

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

const int MAX_MSG_SIZE = 1024 * 1024;

int main (int argc, char** argv) {
	int rank, comm_size;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	if (rank > 1) {
		return 0;
	}

	if (rank == 0) {
		printf("size,time,rate\n");
	}

	char* buffer = malloc(MAX_MSG_SIZE);
	memset(buffer, '0', MAX_MSG_SIZE);

	// warm up
	for (int size = 1; size <= MAX_MSG_SIZE; size *= 2) {
			if (rank == 0) {
				MPI_Send(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			} else {
				MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}
	}

	for (int size = 1; size <= MAX_MSG_SIZE; size *= 2) {

		double total_run_time = 0;
		double repetition_count = 5.0;

		for (int i  = 0; i < repetition_count; ++i) {
			double start = MPI_Wtime();

			if (rank == 0) {
				MPI_Send(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(buffer, size, MPI_CHAR, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			} else {
				MPI_Recv(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				MPI_Send(buffer, size, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
			}

			double end = MPI_Wtime();
			double took = end - start;
			total_run_time += took;
		}
		
		if (rank == 0) {
			total_run_time /= (2.0 * repetition_count);
			double rate = size / (total_run_time * 1e6);

			printf("%d,%.9f,%.9f\n", size, total_run_time, rate);
		}
	}

	
	MPI_Finalize();
	free(buffer);
 	return 0;
}
