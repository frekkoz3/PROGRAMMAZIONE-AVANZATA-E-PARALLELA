#include <stdio.h>
#include "scene.h"
#include "ppm.h"
#include "utils.h"

int main(){
   char * scene_path = "scene_test.txt";
   scene_info scena;
   load_scene(scene_path, &scena);

   int width = 1080;
   int height = 1920;

   vector * raggi = rays(scena.vp, width, height);
   printf("%f\n", raggi->x);
   
    return 0;
}