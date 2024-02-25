#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include"global.h"
using namespace std;
class LTexture
{
private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
public:
    LTexture()
    {
        mTexture=NULL;
        mWidth=0;
        mHeight=0;
    }
    void free()
    {
        if(mTexture!=NULL)
        {
            SDL_DestroyTexture(mTexture);
            mTexture=NULL;
            mWidth=mHeight=0;
        }
    }
    void render(int x,int y)
    {
        SDL_Rect tmp= {x,y,mWidth,mHeight};
        SDL_RenderCopy(gRenderer,mTexture,NULL,&tmp);
    }
    int getWidth()
    {
        return mWidth;
    }
    int getHeight()
    {
        return mHeight;
    }
    bool LoadImage(string file_path)
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
};
