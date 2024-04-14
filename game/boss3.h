#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
int a[1500][1500];
vector<pair<int,int>>flame= {{900,200},{890,590},{810,400},{750,500},{650,500},{990,400},{810,300}};
struct spirit_flame
{
    int x,y,x_vel=1200;
    bool exist=1;
    spirit_flame() {}
    void render();
    void move();
    void reset(int type)
    {
        x=flame[type].first;
        y=flame[type].second;
    }
    SDL_Rect get()
    {
        return {x,y,94,40};
    }
} FLAME[10];
struct spirit_shield
{
    int x,y;
    bool exist=1;
    spirit_shield() {}
    void render();
    void smth();
    SDL_Rect get()
    {
        return {x,y,94,40};
    }
} SHIELD[4];
struct boss3
{
    int xx,yy;
    int x,y;
    int status,HP=0,add=0;
    bool attack=1;
    int stt;
    int shield=1;
    boss3()
    {
        x=875,y=225;
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
        if(!shield)
        {
            SHIELD[1].render();
            SHIELD[2].render();
            SHIELD[0].exist=0;
            SHIELD[1].exist=1;
            SHIELD[2].exist=1;
        }
        if(shield)
        {
            SHIELD[0].render();
            SHIELD[0].exist=1;
            SHIELD[1].exist=0;
            SHIELD[2].exist=0;
        }
        for(int i=1; i<=3; i++)    SHIELD[i].smth();
        action();
        hurt();
    }
    void action();
    void hurt();
    SDL_Rect get()
    {
        return {x+50,y+50,150,150};
    }
    void reset()
    {
        stt=0;
        status=0;
        add=0;
        HP=0;
        attack=0;
    }
} BOSS3;

