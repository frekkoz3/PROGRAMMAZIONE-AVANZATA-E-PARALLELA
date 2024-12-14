#include <stdlib.h> 
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
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
    if (fscanf(fd, "BG %hhu %hhu %hhu\n", &(scene_file->bg.r), &(scene_file->bg.g), &(scene_file->bg.b)) != 3){
        fclose(fd);
        return -3;
    }
    if (fscanf(fd, "OBJ_N %d\n", &(scene_file->obj_n)) != 1){
        fclose(fd);
        return -3;
    }
    scene_file->objects = (sphere *)malloc(scene_file->obj_n * sizeof(sphere));
    for(int i = 0; i < scene_file->obj_n; i++){
        float xi;
        float yi;
        float zi;
        float ri;
        rgb * col = (rgb *)malloc(sizeof(rgb));
        if (fscanf(fd, "S %f %f %f %f %hhu %hhu %hhu\n", &xi, &yi, &zi, &ri, &(col->r), &(col->g), &(col->b)) != 7){
            fclose(fd);
            return -3;
        }
        scene_file->objects[i].x = xi;
        scene_file->objects[i].y = yi;
        scene_file->objects[i].z = zi;
        scene_file->objects[i].radius = ri;
        scene_file->objects[i].color = *col;
    }

    fclose(fd);
    return 0;
}

void print_sphere(sphere s){
    printf("CENTER AT (%f, %f, %f) w/ RADIUS OF %f\n", s.x, s.y, s.z, s.radius);
}

int main(){

    char * p = "scene_test.txt";
    scene_info scena;
    load_scene(p, &scena);
    sphere * sfere = scena.objects;
    for(int i = 0; i < scena.obj_n; i++ ){
        print_sphere(sfere[i]);
    }
    return 0;
}