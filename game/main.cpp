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
    if(!Background_Texture.LoadImage("background.png"))
    {
        cout<<"Q2";
        return 0;
    }
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,36,121,126,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    for(int i=1; i<=Bar_Num; i++)
    {
        A[i]=bar(i);
    }
    A[1].x=200;
    for(int i=1; i<=Bar_Num; i++)
    {
        if(!Bar[i].LoadImage("bar.png"))
        {
            cout<<"Can't load bar"<<endl;
        }
    }
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
        wizard.move();
        for(int i=1;i<=Bar_Num;i++)   push(A[i]);
        /////////////////////////
        SDL_RenderClear(gRenderer);
        Background_Texture.render(0,0);
        for(int i=1; i<=Bar_Num; i++)    Bar[i].render(A[i].x,A[i].y);

        wizard.render();

        SDL_RenderPresent( gRenderer );
        ///////////
        int cur=SDL_GetTicks();
        if(cur%1800==0)   down_speed+=1,SPEED+=1;
        if(down_speed>=243)    down_speed=243;
        SDL_Delay(1000/60.0f);
    }
    close();
    return 0;
}
