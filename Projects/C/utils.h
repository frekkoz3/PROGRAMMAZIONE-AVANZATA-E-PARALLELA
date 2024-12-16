#ifndef _VECTORS_H
#define _VECTORS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct viewport{
    float x;
    float y;
    float z;
}viewport;

typedef struct __attribute__ ((packed)) rgb {
    uint8_t r;
    uint8_t g;
    uint8_t b;
}rgb;

typedef struct vector{
    float x;
    float y;
    float z;
}vector;

typedef struct sphere{
    float x;
    float y;
    float z;
    float radius;
    rgb color;
}sphere;

float difference(vector a, vector b);
int normalize(vector * v);
void print_sphere(sphere s);
void print_color(rgb c);
void print_vector(vector v);
vector * rays(viewport v, int width, int height);

#endif