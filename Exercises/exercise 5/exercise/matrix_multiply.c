#include "matrix_multiply.h"

void simple_multiply(float* A, float* B, float* C, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void transposed_multiply(float * A, float * B, float * C, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

void kernel(float* A, float* B, float* C, int x, int dx, int y, int dy, int z, int dz, int n)
{
  /*
   * Moltiplicazione di blocchi:
   * si prende il blocco A[x:x+dx, z:z+dz] e si moltiplica con B[z:z+dz, y+dy]
   * sommando il risultato nelle posizioni C[x:x+dx, y:y+dy].
   * Prestare attenzione che x+dx, y+dy e z+dz potrebbero essere maggiori di n,
   * nel qual caso bisogna limitarsi ad n.
   */
  for (int i = x; i < n && i < (x + dx); i++){
    for (int j = y; j < n && j < (y + dy); j++){
      for (int k = z; k < n && k < (z + dz); k++){
        C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

int s = 16; // Dimensione dei blocchi, provare inizialmente con 2 o 4

void blocked_multiply(float* A, float* B, float* C, int n)
{
  const int s1 = s;
  const int s2 = s;
  const int s3 = s;
  for (int i = 0; i < n; i += s){
    for (int j = 0; j < n; j += s){
      for (int k = 0; k < n; k += s){
        kernel(A, B, C, i, s, j, s, k, s, n);
      }
    }
  }
}