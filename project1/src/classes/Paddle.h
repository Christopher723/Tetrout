//The dot that will move around on the screen
#ifndef PADDLE_H
#define PADDLE_H

#include <SDL2/SDL.h>
class Paddle
{
    public:
		//The dimensions of the dot
		static const int PADDLE_WIDTH = 40;
		static const int PADDLE_HEIGHT = 20;

		//Maximum axis velocity of the dot
		static const int PADDLE_VEL = 10;

		//Initializes the variables	
		Paddle();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move( SDL_Rect& wall );

		//Shows the dot on the screen
		void render(SDL_Renderer *renderer);

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;

		SDL_Rect mCollider;
};
#endif