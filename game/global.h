#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#include<SDL.h>
#include<SDL_image.h>
#include"LTexture.h"
vector<int>TYPE= {0,0,1};
int VelX=0;
LTexture BAR[20];
/*void Game_Over()
{
    cout<<"GAME OVER";
    return 0;
}*/
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
const int deadY=650;
SDL_Rect san={0,650,800,10};
const int Width=600;
const int Height=800;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int PosX,PosY;
int V0=-547;
const int gravity=500;
const int FPS=60;
int Bar_Num=8;
LTexture Character_Texture;
LTexture Background_Texture;
void LTexture ::  render(int x,int y)
{
    SDL_Rect tmp= {x,y,mWidth,mHeight};
    SDL_RenderCopy(gRenderer,mTexture,NULL,&tmp);
}
bool LTexture ::  LoadImage(string file_path)
{
    free();
    SDL_Surface* Sur=IMG_Load(file_path.c_str());
    if(Sur==NULL)   return 0;

    SDL_SetColorKey( Sur, SDL_TRUE, SDL_MapRGB( Sur->format, 255, 255, 255 ) );
    SDL_Texture *newTexture=SDL_CreateTextureFromSurface(gRenderer,Sur);
    if(newTexture==NULL) return 0;
    mWidth=Sur->w;
    mHeight=Sur->h;
    mTexture=newTexture;
    return (mTexture!=NULL);
}
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    if( bottomA <= topB ) return false;
    if( topA >= bottomB ) return false;
    if( rightA <= leftB ) return false;
    if( leftA >= rightB ) return false;
    return true;
}
struct bar
{
    int t;
    int x,y;
    bar(){}
    bar(int bor1,int bor2)//
    {
         t=TYPE[rnd(0,2)];
         x=rnd(0,Width-100);
         y=rnd(bor1,bor2);
    }
};
void push(bar &X,int dist)
{
    if(X.y+dist<=deadY+55)      X.y+=dist;
    else
    {
        X.y=rnd(100,350);
    }
}
SDL_Rect get(bar X)
{
    return {X.x,X.y,132,21};
}
