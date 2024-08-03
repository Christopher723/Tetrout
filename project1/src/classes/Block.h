#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>


struct Block {
    SDL_Color color;
    bool active;
};

//shape such as I, T, L, etc
struct Shape {

    void update();
    void draw(SDL_Rect rect);
    void checkPaddleCollision(SDL_Rect otherCollider);
    SDL_Color color;
    bool matrix[4][4];
    SDL_Rect mColliders[4][4];
    double x, y;
    int w, h;
    int size;
    bool bounce;
};
#endif 