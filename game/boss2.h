#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
struct thunder
{
    double x;
    double y;
    double x_vel=1200;
    thunder()
    {
        x=1000;
        y=660-85;
    }
    void render();
    void move();
    void reset()
    {
        x=1000;
    }
    SDL_Rect get()
    {
        return {(int)x,(int)y,50,129};
    }
} A;
struct boss2
{
    int xx,yy;
    int x,y;
    int status,Rest=0,HP=0,add=0;
    bool attack=0;
    int stt;
    boss2()
    {
        x=1000,y=660-152;
    }
    void heal()
    {
        stt=0;
        status=0;
        add=0;
        HP=630;
        Rest=100;
        attack=0;
    }
    void render_idle(int x);
    void render_at(int x);
    void bot()
    {
        if(!HP)  return;
        if(Rest<=0)
        {
            status=1;
            stt=0;
            Rest=100;
        }
        HP--;
        if(!HP)    A.reset();
        Rest--;
        action();
    }
    void action();
} BOSS2;
