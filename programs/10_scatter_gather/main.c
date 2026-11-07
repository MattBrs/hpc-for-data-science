#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

/*
	scatter and gather to distribute deck of cards to 
	processes. each process modifies the card and returns it 
	to the main process
*/
int main (int argc, char** argv) {
	MPI_Init(&argc, &argv);
	
	int rank, comm_size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	
	
	int my_card; 
	int my_changed_card;
	int* deck = NULL;
	int* collected = malloc(comm_size* sizeof(int));
	
	if (rank == 0) {
		srand(time(NULL));
		deck = malloc(comm_size * sizeof(int));
		for (int i = 0; i < comm_size; ++i) {
			deck[i] = rand() % 500;
		}

		printf("im process %d and i have deck:\n", rank);
		for (int i  = 0; i < comm_size; ++i) {
			printf("%d ", deck[i]);
		}
		printf("\n");
	}



	MPI_Scatter(deck, 1, MPI_INT, &my_card, 1, MPI_INT, 0, MPI_COMM_WORLD);
	my_changed_card = my_card * 2;



	//MPI_Gather(&my_changed_card, 1, MPI_INT, collected, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Allgather(&my_changed_card, 1, MPI_INT, collected, 1, MPI_INT, MPI_COMM_WORLD);
	// if (rank == 0) {
		printf("im process %d and i have collected:\n", rank);
		for (int i  = 0; i < comm_size; ++i) {
			printf("%d ", collected[i]);
		}
		printf("\n");

	//}

		free(collected);

	if (rank == 0) {
		free(deck);
	}

	MPI_Finalize();
	return 0;
}
