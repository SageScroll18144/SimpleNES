#ifndef FIND_GAME_H
#define FIND_GAME_H

#include "raylib.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILES 512

void list_files(const int screenWidth, const int screenHeight, char ** name_file);

#endif
