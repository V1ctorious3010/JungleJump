#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
struct boss
{
    int x,y;
    int status;
    int LastActionTime=0;
    int HP=100;
    int stt=0;
    void heal()
    {
        HP=100;
    }
    void render_idle(int x);
    void render_slashing(int x);
    void render_throwing(int x);
    void bot()
    {
        if(!HP)  return;
        if(status==0&&LastActionTime>=60)
        {
            LastActionTime=0;
            status=rnd(1,3);
            stt=0;
        }
        else LastActionTime++;
        action(status);
    }
    void action(int type)
    {
        if(type==0)   render_idle(stt);
        if(type==1)   render_slashing(stt);
        if(type==2)   render_throwing(stt);
        stt++;
        if(stt==98)
        {
            status=0;
            stt=0;
        }
    }
    void hurt(){HP-=15;}
}BOSS;
