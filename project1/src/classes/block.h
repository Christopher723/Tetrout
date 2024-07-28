
#ifndef BLOCKS_H
#define BLOCKS_H

#include <SDL2/SDL.h>




//taken from https://github.com/jarreed0/retroremake/blob/master/tetris/tetris.cpp
struct block {
 SDL_Color color;
 bool active;
};

struct shape {
 SDL_Color color;
 bool matrix[4][4];
 double x, y;
 int size;
};

#endif