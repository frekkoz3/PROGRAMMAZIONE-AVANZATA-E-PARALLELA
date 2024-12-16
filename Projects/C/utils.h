#ifndef _VECTORS_H
#define _VECTORS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct point{
    float x;
    float y;
    float z;
}point;

typedef struct direction{
    float x;
    float y;
    float z;
}direction;

typedef struct __attribute__ ((packed)) rgb {
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
}rgb;

typedef struct sphere{
    float x;
    float y;
    float z;
    float radius;
    rgb color;
}sphere;

float difference(point a, point b);
void normalize(direction * d);
void print_sphere(sphere s);
void print_color(rgb c);

#endif