#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "graph.h"
#include "matrix.h"


void shortcut_std(float * m, float * d, int n)
{
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      m[i*n + j] = INFINITY;
      for (int k = 0; k < n; k++){
        m[i*n + j] = (m[i*n + j] < (d[i*n + k] + d[k*n + j])) ? m[i*n + j] : (d[i*n + k] + d[k*n + j]);
      }
    }
  }
}

void shortcut_trs(float * m, float * d, int n)
{
  float * td = zero_matrix(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      td[j * n + i] = d[i * n + j];
    }
  }

  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      m[i*n + j] = INFINITY;
      for (int k = 0; k < n; k ++){
        m[i*n + j] = (m[i*n + j] < (d[i*n + k] + td[j*n + k]))? m[i*n + j] : (d[i*n + k] + td[j*n + k]);
      }
    }
  }
  free(td);
}

void shortcut_omp(float * m, float * d, int n)
{
  #pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      m[i*n + j] = INFINITY;
      for (int k = 0; k < n; k++){
        m[i*n + j] = (m[i*n + j] < (d[i*n + k] + d[k*n + j])) ? m[i*n + j] : (d[i*n + k] + d[k*n + j]);
      }
    }
  }
}

void shortcut(float * m, float * d, int n)
{
  float * td = zero_matrix(n);
  #pragma omp parallel for collapse (2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      td[j * n + i] = d[i * n + j];
    }
  }

  #pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
      m[i*n + j] = INFINITY;
      for (int k = 0; k < n; k ++){
        m[i*n + j] = (m[i*n + j] < (d[i*n + k] + td[j*n + k]))? m[i*n + j] : (d[i*n + k] + td[j*n + k]);
      }
    }
  }
  free(td);
}