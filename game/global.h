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
int down_bar=0;
int Move_down=0;
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
const int deadY=700;
SDL_Rect san= {0,600,800,10};
const int Width=500;
const int Height=800;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int PosX,PosY;
int V0=-547;
const int gravity=500;
const int FPS=60;
int Bar_Num=7;
LTexture Character_Texture;
LTexture Background_Texture;
LTexture Bar[20];
bool dd[20];
int gd1=deadY-100;
int gd2=gd1-100;
int gd3=gd2-100;
int VELOCITY=5;
const int gd[]={0,700,600,500,400,300,200,100};
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
    bar() {}
    bar(int X)//
    {
        t=TYPE[rnd(0,2)];
        x=rnd(0,Width-100);
        y=gd[X];
    }
};
bar A[20];
void push(int idx,bar &X,int dist)
{
      X.y+=dist;
}
int Calc(int x)
{
    if(A[x].y>=gd[1])    return 0;
    if(A[x].y>=gd[2])    return 1;
    return 3;

}
SDL_Rect get(bar X)
{
    return {X.x,X.y,120,20};
}
