#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
class bar
{
private:

    SDL_Texture *mBar;
    int type;
    int mWidth,mHeight;
    int x,y;

public:
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
    bar(int bor1,int bor2);//duoi,tren;
    void free()
    {
        mBar=NULL;
    };
    void down(int dist);
    bool LoadImage(int TT);
};
