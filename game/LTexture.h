#pragma once

#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>

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
    ~LTexture()
    {
        free();
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
    void render(int x,int y,SDL_RendererFlip flip=SDL_FLIP_NONE);
    int getWidth()
    {
        return mWidth;
    }
    int getHeight()
    {
        return mHeight;
    }
    void setAlpha( Uint8 alpha );
    bool LoadImage(string file_path);
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

};

