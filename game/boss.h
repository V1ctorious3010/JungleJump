#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
bool BossAt1=0; // kich hoat tan cong cua boss
struct dirtball
{
    int x=800;
    int y=500;
    void Handle()
    {
       if(BossAt1)
       {
           render();
           move();
       }
    }
    void reset();
    void render();
    void move();
    SDL_Rect get()
    {
        return {x,y,100,100};
    }

} Dirt;
struct boss
{
    int x,y;
    int status; // cac trang thai cua boss tan cong hay nghi
    int Rest=0; // thoi gian nghi giua 2 lan tan cong
    int HP=0;   // mau cua boss
    int stt=0; // render trang thai thu stt cua boss
    int add=0; // delay chuyen dong cua boss
    boss()
    {
        x=800;
        y=270;
    }
    void heal()
    {
        stt=0;
        status=0;
        add=0;
        HP=500;
        Rest=0;
    }
    void render_idle(int x);
    void render_throwing(int x);
    void bot()
    {
        if(!HP)  return;
        //if(Rest>0)  status=0;
        if(Rest<=0)
        {
            status=1;
            stt=0;
            Rest=100;
        }
        HP--;
        if(!HP)   Dirt.reset();
        Rest--;
        action();
    }
    void action();
    void reset()
    {
        stt=0;
        status=0;
        add=0;
        HP=0;
        Rest=0;
        BossAt1=0;
    }
} BOSS;
