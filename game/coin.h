#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
struct coin
{
    int x,y,t;
    int score;
    coin();
    coin(int x,int t);
    void render();
    void move();
    void reset();
    SDL_Rect get()
    {
        if(!t) return {x,y,42,50};
        return {x,y,50,40};
    }
};
