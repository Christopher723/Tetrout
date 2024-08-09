

#include "Paddle.h"
#include "../core/config.h"
#include "../core/global.h"
#include "../core/collision.h"



Paddle::Paddle()
{
    //Initialize the offsets
    mPosX = SCREEN_WIDTH/2;
    mPosY = SCREEN_HEIGHT/1.1;

    mCollider.w = PADDLE_WIDTH;
    mCollider.h = PADDLE_HEIGHT;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;
}

void Paddle::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            // case SDLK_UP: mVelY -= DOT_VEL; break;
            // case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= PADDLE_VEL; break;
            case SDLK_RIGHT: mVelX += PADDLE_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            // case SDLK_UP: mVelY += DOT_VEL; break;
            // case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += PADDLE_VEL; break;
            case SDLK_RIGHT: mVelX -= PADDLE_VEL; break;
        }
    }
}

void Paddle::move( SDL_Rect& wall )
{
    //Move the dot left or right
    mPosX += mVelX;
    mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + PADDLE_WIDTH > SCREEN_WIDTH ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
        mCollider.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
    mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + PADDLE_HEIGHT > SCREEN_HEIGHT ) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosY -= mVelY;
        mCollider.y = mPosY;
    }
}

void Paddle::render(SDL_Renderer *renderer)
{
	


    // SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    
    gPaddleTexture.render( mPosX, mPosY );
    // myObject.render();
    // SDL_RenderPresent( gRenderer );
    
}