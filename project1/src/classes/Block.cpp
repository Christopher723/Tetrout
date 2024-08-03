
#include <SDL2/SDL.h>

#include "Block.h"
#include "../core/config.h"
#include "../core/global.h"
#include "../core/collision.h"





void Shape::update() {
	if (bounce) {
		y -= 2;
	}
	else{y += 2;}
    
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
                    bounce = true;
                }
            }
        }
    }
}