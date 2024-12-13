#ifndef _PPM_H
#define _PPM_H

#include <stdio.h>

typedef struct __attribute__ ((packed)) rgb {
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
}rgb;

typedef struct ppm_p6{
    int width;
    int height;
    int offset;
    int size;
    FILE * fd;
    struct rgb * data;
}ppm;

typedef struct ppm_p6 * ppm_ptr;

int map_image(char * path, ppm_ptr img);

int empty_image(char * path, ppm_ptr img, int width, int height);

struct rgb * pixel_at(ppm_ptr file, int x, int y);

int close_image(ppm_ptr img);

#endif
