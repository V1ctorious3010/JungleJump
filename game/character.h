
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;
class Char
{
public:
    static const int Char_WIDTH = 58;
    static const int Char_HEIGHT = 87;
    static const int Char_VEL = 10;
    Char();
    void handleEvent( SDL_Event& e );
    void move();
    void render();

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect
};
Char::Char()
{
    mPosX = 0;
    mPosY = 0;
    mVelX = 0;
    mVelY = 0;
}

void Char::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:
            mVelY -= Char_VEL;
            break;
        case SDLK_LEFT:
            mVelX -= Char_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += Char_VEL;
            break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_UP:
            mVelY += Char_VEL;
            break;
        case SDLK_LEFT:
            mVelX += Char_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= Char_VEL;
            break;
        }
    }
}
