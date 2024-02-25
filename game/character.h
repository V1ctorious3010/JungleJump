#pragma once

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

using namespace std;
class Char
{
public:
    int Char_VEL = 30;
    Char(int x,int y,int w,int h);
    void handleEvent( SDL_Event& e );
    void move(SDL_Rect &a);
    void render();
private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect box;
};
Char::Char(int x,int y,int w,int h)
{
    mPosX=x;
    mPosY=y;
    box = {x,y,w,h};
    mVelX = 0;
    mVelY = 250;
}

void Char::handleEvent( SDL_Event& e )
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            mVelX -= DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX += DOT_VEL;
            break;
        }
    }
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
        case SDLK_LEFT:
            mVelX += DOT_VEL;
            break;
        case SDLK_RIGHT:
            mVelX -= DOT_VEL;
            break;
        }
    }
}
