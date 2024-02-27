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
    void free()
    {
        if(mTexture!=NULL)
        {
            SDL_DestroyTexture(mTexture);
            mTexture=NULL;
            mWidth=mHeight=0;
        }
    }
    void render(int x,int y);
    int getWidth()
    {
        return mWidth;
    }
    int getHeight()
    {
        return mHeight;
    }
    bool LoadImage(string file_path);
};
