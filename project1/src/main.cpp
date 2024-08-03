/*This source code copyrighted by Lazy Foo' Productions 2004-2024
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include "classes/Paddle.h"
#include "core/global.h"
#include "core/config.h"
#include <string>
#include "classes/Block.h"




//Texture wrapper class





// //individual block
// struct block {
//  SDL_Color color;
//  bool active;
// };

// //shape such as I, T, L, etc
// struct shape {
//  SDL_Color color;
//  bool matrix[4][4];
//  double x, y;
//  int w, h;
//  SDL_Rect mCollider;
//  int size;
//  bool bounce;
// };

Shape blocks[7] = {{{255,165,0},
{{0,0,1,0} // L BLOCK
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3,2,3, false}
,{{255,0,0}, // Z BLOCK
{{1,1,0,0}
,{0,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3,2,3,false}
,{{224,255,255}, // I BLOCK
{{1,1,1,1}
,{0,0,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,4,2,3,false}
,{{0,0,255}, // J BLOCK
{{1,0,0,0}
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3,2,3,false}
,{{255,255,0}, // O BLOCK
{{1,1,0,0}
,{1,1,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,2,2,3,false}
,{{0,0,255}, // S BLOCK
{{0,1,1,0}
,{1,1,0,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3,2,3,false}
,{{128,0,128}, // T BLOCK
{{0,1,0,0}
,{1,1,1,0}
,{0,0,0,0}
,{0,0,0,0}
},5,4,3,2,3,false}}, cur;




//The application time based timer
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

void render();
void draw(Shape s);

bool checkCollision( SDL_Rect a, SDL_Rect b );




SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gPaddleTexture;




SDL_Rect rect;


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gPaddleTexture.loadFromFile( "src/assets/Paddle.bmp" ) )
	{
		printf( "Failed to load Paddle texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	gPaddleTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
//CHANGE THIS TO TAKE MULTIPLE CLASSES
// void renderScreen(Paddle myObject){
//     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
//     SDL_RenderClear( gRenderer );

    

//     myObject.render();
//     SDL_RenderPresent( gRenderer );

// }
				

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Paddle paddle;

			SDL_Rect wall;
			wall.x = 300;
			wall.y = 40;
			wall.w = 40;
			wall.h = 400;
			cur = blocks[1];
			rect.w=rect.h=TILE_SIZE;
			cur.x = 5;
			cur.y = 1;
			

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the paddle
					paddle.handleEvent( e );

				}

				//Move the dot
				paddle.move( wall );

				cur.checkPaddleCollision(paddle.mCollider);
				
				
				// SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );        
                // SDL_RenderDrawRect( gRenderer, &wall );
				//dont know what this does?
				

				cur.update();
				

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear(gRenderer);  // Clear the screen with black

				cur.draw(rect);  // Draw the shape `cur`
				paddle.render(gRenderer);  // Draw the paddle

				SDL_RenderPresent(gRenderer); 
				

				
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
