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
    PosY=660;
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
    SDL_SetRenderDrawColor(gRenderer,0,255,0,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    bool up=1,down=0;
    for(int i=1; i<=Bar_Num; i++)
    {
        A[i]=bar(i);
        cout<<A[i].x<<" "<<A[i].y<<endl;
    }
    A[1].x=200;
    for(int i=1; i<=Bar_Num; i++)
    {
        if(A[i].t==0&&!Bar[i].LoadImage("bar.png"))
        {
            cout<<"Can't load bar"<<endl;
        }
        if(A[i].t==1&&!Bar[i].LoadImage("trap.png"))
        {
            cout<<"Can't load image"<<endl;
        }
    }
    int mVelX=0;
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
                switch( EV.key.keysym.sym )
                {
                case SDLK_LEFT:
                    mVelX -= 2;
                    break;
                case SDLK_RIGHT:
                    mVelX += 2;
                    break;
                }
            }
            else if( EV.type == SDL_KEYUP && EV.key.repeat == 0 )
            {
                switch( EV.key.keysym.sym )
                {
                case SDLK_LEFT:
                    mVelX += 2;
                    break;
                case SDLK_RIGHT:
                    mVelX -= 2;
                    break;
                }
            }
        }
        PosX+=mVelX;
        SDL_Rect hitbox= {PosX+10,PosY+10,24,41};
        //////
        //can chia 2 giai doan
        if(PosY>=gd[2])    VELOCITY=3;
        if(PosY>=gd[3]&&PosY<=gd[2])   VELOCITY=2;
        if(PosY<=gd[3]-50)   VELOCITY=1;
        for(int i=1; i<=Bar_Num; i++)   if(down)
            {
                if(checkCollision(hitbox,get(A[i])))
                {
                    up=1,down=0;
                    Move_down=Calc(i);
                    down_bar=i;
                    break;
                }
            }
        if(PosY<=gd[3]-50-21)     down=1,up=0;
        if(up)   PosY-=VELOCITY;
        else PosY+=VELOCITY;
        for(int i=1; i<=Bar_Num; i++)      push(i,A[i],Move_down);
        for(int i=1; i<=Bar_Num; i++)      if(A[i].y>700)
        {
            A[i].y=gd[7];
            A[i].x=rnd(0,300);
            if(i==down_bar)
            {
                Move_down=0;
                down_bar=0;
            }
        }
        /////////////////////////
        SDL_RenderClear(gRenderer);
        Background_Texture.render(0,0);
        Character_Texture.render(PosX,PosY);
        for(int i=1; i<=Bar_Num; i++)    Bar[i].render(A[i].x,A[i].y);
        SDL_RenderPresent( gRenderer );
        ///////////
        SDL_Delay(10);
    }
    close();
    return 0;
}
