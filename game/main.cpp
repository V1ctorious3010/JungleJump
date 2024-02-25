#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>
#include"global.h"
#include"LTexture.h"
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)   cout<<"Can't init"<<endl;
    gWindow = SDL_CreateWindow( "DoodleJump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN );
    if(gWindow==NULL)    return 0;
    gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    if(gRenderer==NULL)   return 0;
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }
    return 1;
}
void close()
{
    //Free loaded images
    Character_Texture.free();
    Background_Texture.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
int main(int argc,char * argv[])
{
    if(!init())
    {
        cout<<"Can't init"<<endl;
        return 0;
    }
    PosX=250;
    PosY=deadY+87;
    if(!Character_Texture.LoadImage("character.png"))
    {
        cout<<"Q1";
        return 0;
    }
    if(!Background_Texture.LoadImage("background.png"))
    {
        cout<<"Q2";
        return 0;
    }
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    int lastCollide=0;
    int lastUpd=0;
    while(running)
    {
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                running=0;
                break;
            }
            if( EV.type == SDL_KEYDOWN && EV.key.repeat == 0 )
            {
                //Adjust the velocity
                switch( EV.key.keysym.sym )
                {
                case SDLK_LEFT:
                    VelX -= 30;
                    break;
                case SDLK_RIGHT:
                    VelX += 30;
                    break;
                }
            }
            else if( EV.type == SDL_KEYUP && EV.key.repeat == 0 )
            {
                switch( EV.key.keysym.sym )
                {
                case SDLK_LEFT:
                    VelX += 1;
                    break;
                case SDLK_RIGHT:
                    VelX -= 1;
                    break;
                }
            }
        }
        SDL_Rect hitbox= {PosX,PosY,58,87};
        int cur=SDL_GetTicks();

        bool jump=0;
        double dT=1.0*(cur-lastUpd)/1000.0f;
        double dT2=1.0*(cur-lastCollide)/1000.0f;
        PosY=650+V0*dT2-(gravity*dT2*dT2)/2;
        PosX+=VelX;
        if( ( PosX < 0 ) || ( PosX + 58 > Width ) )
        {
            PosX -= VelX;
        }
        PosY=min(PosY,deadY+87);
        SDL_Rect nextHitbox= {PosX,PosY,58,87};
        if(checkCollision(nextHitbox,san))   V0=-547,lastCollide=cur;
        //////
        //can chia 2 giai doan


        /////////////////////////
        SDL_RenderClear(gRenderer);
        Background_Texture.render(0,0);
        Character_Texture.render(PosX,PosY);
        SDL_RenderPresent( gRenderer );
        ///////////
        lastUpd=cur;
    }
    close();
    return 0;
}
