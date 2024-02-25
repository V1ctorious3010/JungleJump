#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#include<SDL.h>
#include<SDL_image.h>
#include"LTexture.h"
#include"character.h"
vector<int>TYPE={0,0,0,1,2};

int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
const int deadY=650;
const int Dai=600;
const int Rong=800;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int PosX,PosY;
const int Acceleration=30;
const int gravity=10;
const int FPS=60;
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

void Char::render()
{
    Character_Texture.render( mPosX, mPosY );
}
void Char::move()
{
    mPosX += mVelX;
    if( ( mPosX < 0 ) || ( mPosX + Char_WIDTH > Dai ) ) mPosX -= mVelX;
    mPosY += mVelY;
    if( ( mPosY < 0 ) || ( mPosY + Char_HEIGHT > Rong ) ) mPosY -= mVelY;
}

