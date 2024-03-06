#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>
#include"global.h"
#include"LTexture.h"

bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)   cout<<"Can't init"<<endl;
    gWindow = SDL_CreateWindow( "Game_nhay_nhay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN );
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
    if(!Background_Texture.LoadImage("bg.png"))
    {
        cout<<"Q2";
        return 0;
    }
    if(!bullet.LoadImage("bullet.png"))
    {
        cout<<"can't load bullet";
        return 0;
    }
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,36,121,126,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    int scrollingOffset=0;
    bool bullet_on_screen=1;
    while(running)
    {
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                running=0;
                break;
            }
            wizard.handleEvent(EV);
        }
        scrollingOffset-=5;
        if( scrollingOffset <- Background_Texture.getWidth() )
        {
            scrollingOffset = 0;
        }
        wizard.move();
        /////////////////////////
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);
        Background_Texture.render( scrollingOffset, 0 );
        Background_Texture.render( scrollingOffset + Background_Texture.getWidth()-3, 0 );
        wizard.render();
        SDL_Rect hitbox={230,wizard.getY(),1,110};
        if(!bullet_on_screen)
        {
            int n=rnd(1,10);
            if(n>1)     A.reset(),bullet_on_screen=1;
        }
        if(bullet_on_screen)
        {
            A.move();
            A.render();
            if(checkCollision(hitbox,A.get()))
            {
                return 0;
            }
            if(A.x<0)   bullet_on_screen=0;

        }
        /*8for(int i=1;i<=Stones;i++)
        {
            St[i].move;
            St[i].render();
            if(checkCollision(hitbox,St[i].get()))
            {
                return 0;
            }
        }*/
        //cout<<bullet_on_screen<< " ";
        SDL_RenderPresent( gRenderer );
        /////////////////////////
        SDL_Delay(1000/60.0f);
    }
    close();
    return 0;
}
