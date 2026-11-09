/*
        Make a simple program that calls hello word function
        with a number of thread specified as input parameter.
        Execute with PBS on the cluster and experiment with
        the number of threads allocated to the program.
        Look how the output changes.
*/

#include "omp.h"
#include "stdio.h"
#include "stdlib.h"

void hello();

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("wrong param count. Please specify the thread count\n");
    return 1;
  }

  int thread_count = strtol(argv[1], NULL, 10);
  if (thread_count <= 0) {
    return 1;
  }

#pragma omp parallel num_threads(thread_count)
  hello();

  return 0;
}

void hello() {
  int thread_count = omp_get_num_threads();
  int thread_rank = omp_get_thread_num();
  printf("Hello world from thread %d out of %d!\n", thread_rank, thread_count);
}
