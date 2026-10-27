#include "mpi.h"
#include "stdio.h"
#include "string.h"

const int MAX_STRING = 100; 

int main(int argc, char** argv) {
	char greeting[MAX_STRING];
	int comm_size;
	int rank;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		

	if (rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d!", rank, comm_size);
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	} else {
		printf("Greetings from process %d of %d!\n", rank, comm_size);
		for (int i = 1; i < comm_size; ++i) {
			MPI_Status status;
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);

			int recv_size = 0;
			MPI_Get_count(&status, MPI_CHAR, &recv_size);
			printf("Received %d chars: %s\n", recv_size, greeting);
		}
	}

	MPI_Finalize();
	return 0;
}
