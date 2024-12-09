#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include "matrix.h"
#include "graph.h"

double test_shortcut(void (*f) (float *, float *, int), float * m, float * d, int n, int r)
{
  double t = 0;
  for (int i = 0; i < r; i++) {
    double start = omp_get_wtime();
    f(m, d, n);
    double end = omp_get_wtime();
    t += (end - start);
  }
  return 1000 * t / r;
}

int main(int argc, char * argv[])
{
  srand(time(NULL));
  const int repetitions = 3;
  const int n = 1000;
  float * m = zero_matrix(n);
  float * d = random_matrix(n);
  double t;
  t = test_shortcut(shortcut_std, m, d, n, repetitions);
  printf("Tempo per shortcut standard: %f ms\n", t);
  t = test_shortcut(shortcut_trs, m, d, n, repetitions);
  printf("Tempo per shortcut con trasposta: %f ms\n", t);
  t = test_shortcut(shortcut_omp, m, d, n, repetitions);
  printf("Tempo per shortcut OpenMP: %f ms\n", t);
  t = test_shortcut(shortcut, m, d, n, repetitions);
  printf("Tempo per shortcut: %f ms\n", t);
  free(m);
  free(d);
  return 0;
}