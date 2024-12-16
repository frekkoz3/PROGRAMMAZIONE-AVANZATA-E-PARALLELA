#ifndef _SCENE_H
#define _SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

typedef struct viewport{
    float x;
    float y;
    float z;
}viewport;

typedef struct scene_info{
    struct viewport vp;
    struct rgb bg;
    int obj_n;
    sphere * objects;
    FILE * fd;
}scene_info;

int load_scene(char * path, scene_info * scene_file);


#endif