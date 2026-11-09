/*
    Estimate pi and parallelize program with openmp.
    For estimation, we can use 4 * sum_from_k_to_n( (-1^k)/(2k+1) )
*/

#include "omp.h"
#include "stdio.h"
#include <stdlib.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("provide [tc: number of threads to use] [n:pi approx length]\n");
    return 1;
  }

  long th_count = strtol(argv[1], NULL, 10);
  long n = strtol(argv[2], NULL, 10);

  if (th_count <= 0 || n <= 0) {
    printf(
        "params are less or equal than 0, please insert a valid parameter\n");
    return 1;
  }

  long i;
  double sum = 0.0;
  double factor = 1.0;

#pragma omp parallel for num_threads(10) reduction(+ : sum) private(factor)
  for (i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      factor = 1.0;
    } else {
      factor = -1.0;
    }

    sum += factor / (2 * i + 1);
  }

  double pi = 4 * sum;

  printf("pi is approx: %0.9f\n", pi);

  return 0;
}
