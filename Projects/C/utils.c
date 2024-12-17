#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "utils.h"
#include <math.h>

void print_color(rgb c){
    printf("R %hhu G %hhu B %hhu\n", c.r, c.g, c.b);
}

void print_sphere(sphere s){
    printf("CENTER AT (%f, %f, %f) w/ RADIUS OF %f ", s.x, s.y, s.z, s.radius);
    print_color(s.color);
}

void print_vector(vector v){
    printf("X %f Y %f Z %f \n", v.x, v.y, v.z);
}

int normalize(vector * v){
    float norm = sqrt((pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2)));
    if (norm == 0){
        return -1;
    }
    v->x /= norm;
    v->y /= norm;
    v->z /= norm;
    return 0;
}

vector * rays(viewport v, int width, int height){
    vector * all_rays = (vector *)malloc(width * height * sizeof(vector));
    for (int i = 0; i < width; i ++ ){
        for (int j = 0; j < height; j ++){
            all_rays[i*width + j].x = ((v.x/(width-1))*i - v.x/2);
            all_rays[i*width + j].y = ((v.y/(height-1))*j - v.y/2);
            all_rays[i*width + j].z = 1;
            int errn = normalize(all_rays + i*width + j);
            if (errn != 0){
                printf("ERROR OCCURRED");
            }
        }
    }
    return all_rays;
}