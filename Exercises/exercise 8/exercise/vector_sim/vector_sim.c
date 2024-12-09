#include <math.h>
#include <omp.h>
#include "vector_sim.h"

float cos_sim(float * v1, float * v2, int len)
{
    float product = 0;
    float sum_squared_v1 = 0;
    float sum_squared_v2 = 0;
    for(int i = 0; i < len; i ++){
      product += v1[i]*v2[i];
      sum_squared_v1 += v1[i]*v1[i];
      sum_squared_v2 += v2[i]*v2[i];
    }
    return product/(sqrtf(sum_squared_v1)*sqrtf(sum_squared_v2));
}

int most_similar(float * v, float * M, int nrows, int ncols)
{
  float most_similarity_value = -INFINITY;
  int most_similarity_index = -1;
  for(int i = 0; i < nrows; i ++){
    float similarity = cos_sim(v, M + (i*ncols), ncols);
    most_similarity_value = (similarity > most_similarity_value) ? similarity : most_similarity_value;
    most_similarity_index = (similarity > most_similarity_value) ? i : most_similarity_index;
  }
  return most_similarity_index;
}

int omp_most_similar(float * v, float * M, int nrows, int ncols)
{
  float most_similarity_value = -INFINITY;
  int most_similarity_index = -1;
  #pragma omp parallel
  {
    float local_most_similarity_value = -INFINITY;
    int local_most_similarity_index = -1;
    #pragma omp for nowait
      for(int i = 0; i < nrows; i ++){
        float similarity = cos_sim(v, M + (i*ncols), ncols);
        local_most_similarity_value = (similarity > local_most_similarity_value) ? similarity : local_most_similarity_value;
        local_most_similarity_index = (similarity > local_most_similarity_value) ? i : local_most_similarity_index;
      }
    #pragma omp critical
    {
      most_similarity_value = (local_most_similarity_value > most_similarity_value) ? local_most_similarity_value : most_similarity_value;
      most_similarity_index = (local_most_similarity_value > most_similarity_value) ? local_most_similarity_index : most_similarity_index;
    }
  }
  return most_similarity_index;
}