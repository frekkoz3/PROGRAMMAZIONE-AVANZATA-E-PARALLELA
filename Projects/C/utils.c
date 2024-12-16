#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include "utils.h"

void print_color(rgb c){
    printf("R %hhu G %hhu B %hhu\n", c.r, c.g, c.b);
}

void print_sphere(sphere s){
    printf("CENTER AT (%f, %f, %f) w/ RADIUS OF %f ", s.x, s.y, s.z, s.radius);
    print_color(s.color);
}