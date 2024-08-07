
#include <SDL2/SDL.h>

#include <array>
#include "Block.h"
#include "../core/config.h"
#include "../core/global.h"
#include "../core/collision.h"


// Shape::Shape(SDL_Color color, std::array<std::array<bool, 4>, 4> grid, int x, int y, int w, int h, int bounceAmount, bool active)
// {
//     color = color;
    // for (int i = 0; i < 4; ++i) {
    //         for (int j = 0; j < 4; ++j) {
    //             matrix[i][j] = grid[i][j];
    //         }
    //     }
//     x = x;
//     y = y;
//     w = w;
//     h = h;
//     bounceAmount = bounceAmount;
//     bounce = active;
// }

Shape::Shape(SDL_Color color, bool grid[4][4], int x, int y, int w, int h, int bounceAmount){
    this->color = color;
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->bounceAmount = bounceAmount;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = grid[i][j];
        }
    }
}





void Shape::update() {

    // printf("bounceAmount: %d\n", bounceAmount);
	y += bounceAmount;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (matrix[i][j]) {
                mColliders[i][j].x = x + j * TILE_SIZE;
                mColliders[i][j].y = y + i * TILE_SIZE;
                mColliders[i][j].w = TILE_SIZE;
                mColliders[i][j].h = TILE_SIZE;
            }
        }
    }

}

void Shape::draw(SDL_Rect rect) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (matrix[i][j]) {
                rect.x = x + j * TILE_SIZE;
                rect.y = y + i * TILE_SIZE;
                rect.w = TILE_SIZE;
                rect.h = TILE_SIZE;

                SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 255);
                SDL_RenderFillRect(gRenderer, &rect);

                SDL_SetRenderDrawColor(gRenderer, 219, 219, 219, 255);
                SDL_RenderDrawRect(gRenderer, &rect);

                // Render the collider for debugging
                SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255); // Red color
                SDL_RenderDrawRect(gRenderer, &mColliders[i][j]);
            }
        }
    }
}

void Shape::checkPaddleCollision(SDL_Rect paddleCollider){
        for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (matrix[i][j]) {
                if (checkCollision(mColliders[i][j], paddleCollider)) {
                    bounce = bounceAmount = -2;
                }
            }
        }
    }
}

bool Shape::checkWallCollision(SDL_Rect wall){
        for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (matrix[i][j]) {
                if (checkCollision(mColliders[i][j], wall)) {
                    bounceAmount = 0;
                    return true;
                }
            }
        }
    }
    return false;
}
