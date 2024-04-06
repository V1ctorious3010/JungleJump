#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
bool BossAt1=0;
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
    void reset()
    {
        x=800;
        y=500;
    }
    void render();
    void move();

} Dirt;
struct boss
{
    int xx,yy;
    int x,y;
    int status;
    int Rest=0;
    int HP=0;
    int stt=0;
    int add=0;
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
} BOSS;
