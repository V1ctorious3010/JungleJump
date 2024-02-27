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
    PosY=deadY+88;
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
    int NumberOfBar=15;

    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,0,255,0,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    int lastCollide=0;
    int lastUpd=0;
    bool up=1,down=0;
    int VELOCITY_DOWN=2,VELOCITY_UP=2;
    while(running)
    {
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                running=0;
                break;
            }

        }
        SDL_Rect hitbox= {PosX,PosY,58,87};
        PosY=min(PosY,deadY+85);
        SDL_Rect nextHitbox= {PosX,PosY,58,87};
        //////

        //can chia 2 giai doan
        if(PosY>=500&&down)    VELOCITY_DOWN=2;
        if(PosY>=500&&up)      VELOCITY_UP=2;
        if(PosY<=500&&up)      VELOCITY_UP=1;
        if(PosY<=500&&down)    VELOCITY_UP=1;
        if(PosY<=355)  down=1,up=0;
        if(PosY>=352&&up)   PosY-=VELOCITY_UP;
        else PosY+=VELOCITY_DOWN;
        if(PosY>=deadY+85&&down)   up=1,down=0;
        /////////////////////////
        SDL_RenderClear(gRenderer);
        Background_Texture.render(0,0);
        Character_Texture.render(PosX,PosY);
        SDL_RenderPresent( gRenderer );
        ///////////
        SDL_Delay(4);
    }
    close();
    return 0;
}
