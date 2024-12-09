#include "merge.h"
#include <string.h>
#include <stdio.h>

void merge(int * v1, int n1, int * v2, int n2, int * results)
{
  int int_size = sizeof(int);
  int i = 0, j = 0, k = 0;
  while (i < n1 && j < n2){
        if (v1[i] < v2[j]){
          results[k] = v1[i];
          i++;
        }else{
          results[k] = v2[j];
          j++;
        }
        k++;
   }
    memcpy(results + k, v2 + j, (n2-j) * int_size);
    memcpy(results + k, v1 + i, (n1-i) * int_size);
}

void merge_branchless(int * v1, int n1, int * v2, int n2, int * results)
{
  int int_size = sizeof(int);
  int i = 0, j = 0, k = 0;
  while (i < n1 && j < n2){
    int p = v1[i] < v2[j];
    results[k] = v1[i]*p + v2[j]*(1-p);
    i = i + p;
    j = j + (1 - p);
    k++;
  }
  memcpy(results + k, v2 + j, (n2-j) * int_size);
  memcpy(results + k, v1 + i, (n1-i) * int_size);
}