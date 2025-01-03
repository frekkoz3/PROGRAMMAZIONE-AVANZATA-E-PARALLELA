#ifndef _MATRIX_MULTIPLY_H
#define _MATRIX_MULTIPLY_H

void simple_multiply(float * A, float * B, float * C, int n);

void transposed_multiply(float * A, float * B, float * C, int n);

void blocked_multiply(float * A, float * B, float * C, int n);

#endif