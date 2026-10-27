/*
Write a program that takes data from process zero and
sends it to all of the other processes by sending it in a ring.
That is, process i should receive the data and send it to
process i+1, until the last process is reached
*/

#include "mpi.h"
#include "stdio.h"
#include "string.h"

int MAX_STRING_SIZE = 100;

void get_data(char* msg, size_t *size);

int main(int argc, char** argv) {
	int rank;
	int size;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	if (rank == 0) {
		size_t msg_size = 0;
		char msg[MAX_STRING_SIZE];
		get_data(msg, &msg_size);
		
		printf("Im the process %d of %d and im sending the message: %s\n", rank+1, size, msg);
		MPI_Send(msg, msg_size, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
	} else {
		char msg[MAX_STRING_SIZE];
		MPI_Recv(msg, MAX_STRING_SIZE, MPI_CHAR, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			
		// send if is not last
		if (rank < size - 1) {
			printf("Im the process %d of %d, and im passing on the message: %s\n", rank+1, size, msg);
			MPI_Send(msg, strlen(msg) + 1 , MPI_CHAR, rank+1, 0, MPI_COMM_WORLD);
		}
		
		if(rank == size - 1) {
			printf("Im the process %d of %d, and i received the message: %s\n", rank+1, size, msg);
		} 
	}

	MPI_Finalize();	
	return 0;
}

void get_data(char* msg, size_t *size) {
	FILE* fptr;
	fptr = fopen("input.txt", "r");
	fgets(msg, MAX_STRING_SIZE, fptr);
	*size = strlen(msg)+1;
}
