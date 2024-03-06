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
const int deadY=620;
SDL_Rect san= {0,600,800,10};
const int Width=1280;
const int Height=824;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int Bar_Num=8;
LTexture Character_Texture;
LTexture Background_Texture;
LTexture Bar[20];
////
double down_speed=1.5;
int VELOCITY=0;
double GRAVITY=18;
double SPEED=240;
const int FPS=60;
////
nhanvat wizard;
const int gd[]= {0,700,600,500,400,300,200,100};
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
    int x,y;
    bar() {}
    bar(int X)//
    {
        x=rnd(0,Width-250);
        y=gd[X];
    }
};
bar A[20];
SDL_Rect get(bar X)
{
    return {X.x,X.y,145,26};
}
void nhanvat::move()
{
    if(!on_ground)  y_vel += GRAVITY;
    if (jump_pressed && can_jump)
    {
        on_ground=0;
        can_jump = false;
        y_vel = -700;
    }
    double foot=mPosY+129;
    double nxtfoot=mPosY+y_vel/60+130;

    if(foot<deadY&&nxtfoot>=deadY)
    {
        mPosY=deadY-character_HEIGHT;
        y_vel=0;
        can_jump=1;
        on_ground=1;
    }
    else on_ground=0,can_jump=0;
    mPosY+= y_vel/60;
}

void nhanvat::render()
{
    add+=1;
    if(add==5)   add=0,status=(status+1)%8;
    if(!status)       status++;
    if(status==1)     Character_Texture.LoadImage("run1.png");
    if(status==2)     Character_Texture.LoadImage("run2.png");
    if(status==3)     Character_Texture.LoadImage("run3.png");
    if(status==4)     Character_Texture.LoadImage("run4.png");
    if(status==5)     Character_Texture.LoadImage("run5.png");
    if(status==6)     Character_Texture.LoadImage("run6.png");
    if(status==7)     Character_Texture.LoadImage("run7.png");
    if(!on_ground)    Character_Texture.LoadImage("run0.png");
    Character_Texture.render(300,mPosY);
   // SDL_Delay(100);
}
