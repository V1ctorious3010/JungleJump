#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#include<SDL.h>
#include<SDL_image.h>
#include"LTexture.h"
#include"character.h"
vector<int>TYPE= {0,0,1};
int VelX=0;
LTexture BAR[20];
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
int Bar_Num=7;
LTexture Character_Texture;
LTexture Background_Texture;
LTexture Bar[20];
////
int VELOCITY=0;
const int GRAVITY=10;
const int SPEED=240;
const int FPS=60;
////
nhanvat wizard;
const int gd[]= {0,700,575,450,325,200,85};
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

    SDL_SetColorKey( Sur, SDL_TRUE, SDL_MapRGB( Sur->format, 36, 121, 126 ) );
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
        x=rnd(0,Width/2-65);
        y=gd[X];
    }
};
bar A[20];
void push(bar &X,int dist)
{
    X.y+=dist;
    if(X.y>700)  X.y=gd[6];
}
SDL_Rect get(bar X)
{
    return {X.x,X.y,50,8};
}
void nhanvat::move()
{
    x_vel = (right_pressed - left_pressed)*SPEED;
    if(!on_ground)  y_vel += GRAVITY;
    if (jump_pressed && can_jump)
    {
        on_ground=0;
        can_jump = false;
        y_vel = -480;
    }
    mPosX += x_vel / 60;
    if ( mPosX+x_vel/60 <= 0)    mPosX = 0;
    if ( mPosX+x_vel/60 >= Width - character_WIDTH)   mPosX = Width - character_WIDTH;
    double foot=mPosY+50;
    double nxtfoot=mPosY+y_vel/60+50;
    for(int i=1; i<=Bar_Num; i++)
    {
        if(foot<A[i].y&&nxtfoot>=A[i].y&&A[i].x<=mPosX+character_WIDTH&&A[i].x+50>=mPosX)
        {
            mPosY=A[i].y-character_HEIGHT;
            y_vel=0;
            can_jump=1;
            on_ground=1;
            return ;
        }
        else on_ground=0,can_jump=0;
    }
    mPosY+= y_vel / 60;
}
void nhanvat::render()
{
    if(!direction&&!Character_Texture.LoadImage("character_left.png"))
    {
        cout<<"Q1";
    }
    if(direction&&!Character_Texture.LoadImage("character_right.png"))
    {
        cout<<"Q1";
    }
    Character_Texture.render(mPosX,mPosY);
}
