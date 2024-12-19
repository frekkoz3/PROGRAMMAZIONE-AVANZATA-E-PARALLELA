#ifndef _SCENE_H
#define _SCENE_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int load_scene(char * path, scene_info * scene_file);
int free_scene(scene_info * scene_file);

#endif