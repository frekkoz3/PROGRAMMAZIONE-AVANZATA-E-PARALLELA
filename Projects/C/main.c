#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "scene.h"
#include "ppm.h"

int main(){
    char * scene_path = "scene_test.txt";
    scene_info scena;
    int errn = load_scene(scene_path, &scena);
    printf("%d \n", errn);
    int width = 1080;
    int height = 1920;

    vector * raggi = rays(scena.vp, width, height);
    printf("%f\n", raggi->x);

    char * img_path = "img_test.ppm";
    ppm img;
    errn = empty_image(img_path, &img, width, height);
    for (int x = 0; x < width; x ++){
        for (int y = 0; y < height; y ++){
            rgb * c = pixel_at(&img, x, y);
            c -> r = 255;
        }
    }
    errn = close_image(&img);
    return 0;
}