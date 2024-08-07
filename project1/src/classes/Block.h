#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>


struct Block {
    SDL_Color color;
    bool active;
};

//shape such as I, T, L, etc
struct Shape {

    // Shape(SDL_Color color, std::array<std::array<bool, 4>, 4> grid, int x, int y, int w, int h, int bounceAmount, bool active);
    Shape(SDL_Color color, bool grid[4][4], int x, int y, int w, int h, int bounceAmount);
    // Shape(bool grid[4][4]);
    void update();
    void draw(SDL_Rect rect);
    void checkPaddleCollision(SDL_Rect otherCollider);
    bool checkWallCollision(SDL_Rect otherCollider);


    SDL_Color color;
    bool matrix[4][4];
    SDL_Rect mColliders[4][4];
    int x, y;
    int w, h;
    int bounceAmount;
    bool bounce;
    
};

#endif 
