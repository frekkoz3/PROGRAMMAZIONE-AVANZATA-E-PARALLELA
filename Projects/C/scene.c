#include <stdlib.h> 
#include <stdio.h>
#include "scene.h"

int load_scene(char * path, scene_info * scene_file){

    FILE * fd = fopen(path, "r+");
    scene_file->fd = fd;
    if (fd == NULL){
        return -2;
    }
    if (fscanf(fd, "VP %f %f %f\n", &(scene_file->vp.x), &(scene_file->vp.y), &(scene_file->vp.z)) != 3){
        fclose(fd);
        return -3;
    }
    if (fscanf(fd, "BG %d %d %d\n", &(scene_file->bg.r), &(scene_file->bg.g), &(scene_file->bg.b)) != 3){
        fclose(fd);
        return -3;
    }
    if (fscanf(fd, "OBJ_N %d\n", scene_file->obj_n) != 1){
        fclose(fd);
        return -3;
    }
    scene_file->objects = (sphere *)malloc(scene_file->obj_n * sizeof(sphere));
    for(int i = 0; i < scene_file->obj_n; i++){
        float x;
        float y;
        float z;
        float r;
        struct rgb * col;
        if (fscanf(fd, "S %f %f %f %f %u %u %u\n", &x, &y, &z, &r, col->r, col->g, col->b) != 7){
            fclose(fd);
            return -3;
        }
    }
}