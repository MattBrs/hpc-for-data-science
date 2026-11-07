/*
	benchmark with scatter, pack and excl the
	matrix vector multiplication algorithm we have 
	seen in class.
*/

#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * Compute this rank's part of y = A * x. All ranks in comm call together.
 * local_A: local_m complete rows of A, stored consecutively (local_m * n doubles).
 * local_x: this rank's consecutive block of x (local_n doubles).
 * local_y: output buffer for this rank's rows (local_m doubles).
 * local_m: number of rows of A held by this rank.
 * n: number of columns of A, also the length of the full x vector.
 * local_n: number of x entries per rank (n / number of ranks).
 * comm: communicator whose rank order defines the order of the x blocks.
 *
 * The caller distributes A and x and allocates local_y before calling.
 * This version assumes n is divisible by the number of ranks in comm.
 */
void Mat_vect_mult(
	double local_A[],
	double local_x[],
	double local_y[],
	int local_m,
	int n,
	int local_n,
	MPI_Comm comm
);

void Get_input(double local_A[], double* x, double* y);

int main (int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, comm_size;
	MPI_Comm_size(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &comm_size);
	
	



	MPI_Finalize();
	return 0;
}

void Mat_vect_mult(
	double local_A[],
	double local_x[],
	double local_y[],
	int local_m,
	int n,
	int local_n,
	MPI_Comm comm
) {
	double* x;
	int local_i, j;
	int local_ok = 1;

	/* Every rank needs all of x to compute the dot products for its rows. */
	x = malloc(n *sizeof(double));
	/* Each rank sends local_n values and receives local_n from each rank. */
	MPI_Allgather(local_x, local_n, MPI_DOUBLE, x, local_n, MPI_DOUBLE, comm);
	
	for (local_i = 0; local_i < local_m; local_i++) {
		local_y[local_i] = 0.0;
		for (j=0; j<n; j++) {
			/* Skip local_i complete rows, then move to column j. */
			local_y[local_i] += local_A[local_i*n+j] * x[j];
		}
	}

	free(x);
}

void Get_input(double** local_A, double* x, double* y) {
	
}
