#ifndef _SCENE_H
#define _SCENE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct __attribute__ ((packed)) rgb {
    u_int8_t r;
    u_int8_t g;
    u_int8_t b;
}rgb;

typedef struct viewport{
    float x;
    float y;
    float z;
}viewport;

typedef struct sphere{
    float x;
    float y;
    float z;
    float radius;
    struct rgb color;
}sphere;

typedef struct scene_info{
    struct viewport vp;
    struct rgb bg;
    int obj_n;
    struct sphere * objects;
    FILE * fd;
}scene_info;

int load_scene(char * path, scene_info * scene_file);

#endif