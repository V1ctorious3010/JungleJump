#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
struct bar
{
    SDL_Texture *mBar;
    int type;
    int mWidth,mHeight;
    int x,y;
    bar(){}
    bar(int bor1,int bor2){}
    int getW()
    {
        return mWidth;
    }
    int getH()
    {
        return mHeight;
    }
    SDL_Rect getbox()
    {
        return {x,y,x-mWidth,y-mHeight};
    }
    void render(int x,int y);
    void reuse(int dist);
};
bar BAR[20];
