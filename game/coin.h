#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>

int rate_coin[10]={1,1,1,0,0,0,2,2,2,2};
// 3 la gold
struct coin
{
    int x,y,t;
    int score;
    int upblood;
    coin();
    coin(int x,int t);
    void render();
    void move();
    void reset();
    void change(int a, int b);// ham lay vi tri cua gold
    SDL_Rect get()
    {
        if(!t) return {x,y,42,50};
        return {x,y,50,40};
    }
};

int number_skill[100]={1,2,2,3};
// 1 la ki nang bay
// 2 la ki nang teleport
// 3 la tia laze bien object to gold
struct skill{
    int x,y,t;
    double mPosY_skill2, mPosX_skill2; // vi tri cua qua cau dich chuyen skill2
    double skill2_vel;
    double mPosX_top_skill3,mPosY_top_skill3;
    double mPosX_bottom_skill3,mPosY_bottom_skill3;
    skill();
    void render();
    void move();
    void reset();
    SDL_Rect get()
    {
        return {x,y,50,50};
    }
};
