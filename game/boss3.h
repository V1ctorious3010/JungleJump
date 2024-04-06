#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
int a[1500][1500];
vector<pair<int,int>>flame={{900,200},{890,590},{810,400},{750,500},{650,500},{990,400},{810,300}};
struct spirit_flame
{
    int x,y,x_vel=1200;
    bool exist=1;
    spirit_flame(){}
    void render();
    void move();
    void reset(int type)
    {
        x=flame[type].first;
        y=flame[type].second;
        a[x/40][y/25]=1;
    }
    SDL_Rect get()
    {
        return {x,y,94,40};
    }
}FLAME[7];
struct boss3
{
    int xx,yy;
    int x,y;
    int status,HP=0,add=0;
    bool attack=1;
    int stt;
    boss3()
    {
        x=1000,y=300;
    }
    void heal()
    {
        stt=0;
        status=1;
        add=0;
        HP=600;
        attack=0;
    }
    void render_idle();
    void render_at(int x);
    void bot()
    {
        if(!HP)  return;
        action();
    }
    void action();
    void hurt();
} BOSS3;

