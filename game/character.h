#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include"SDL_mixer.h"
double GRAVITY=18;
Mix_Chunk *JumpSound=NULL;
Mix_Chunk *AttackSound=NULL;
class fireball
{
    double x;
    double y;
    const int speed=600;
public:
    fireball()
    {
        x=250;
        y=525;
    }
    void  move()
    {
        x+=speed/60;
    }
    SDL_Rect get()
    {
        return {(int)x,(int)y,30,50};
    }
    void render(int a);
    void set_y(int T)
    {
        y=T;
    }
} FIRE[4];

class nhanvat
{
public:
    const int character_WIDTH = 90;
    const int character_HEIGHT = 130;
    const int character_speed = 20;
    nhanvat()
    {
        mPosY=250,y_vel=0;
        jump_pressed=0;
        can_jump=0;
        on_ground=0;
        add=0;
        status=1;
        ammo=3;
    }
    void handleEvent( SDL_Event &EV)
    {
        if(EV.type== SDL_KEYDOWN)
        {
            switch (EV.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                jump_pressed = true;
                break;
            case SDL_SCANCODE_S:
                GRAVITY=300;
                break;
            case SDL_SCANCODE_J:
                if (ammo == 3)
                {
                    Mix_PlayChannel(-1,AttackSound,0);
                    attack[3] = 1;
                    ammo--;
                    FIRE[3].set_y(mPosY+20);
                }
                else if (ammo == 2)
                {
                    Mix_PlayChannel(-1,AttackSound,0);
                    attack[2] = 1;
                    ammo--;
                    FIRE[2].set_y(mPosY+20);
                }
                else if (ammo == 1)
                {
                    Mix_PlayChannel(-1,AttackSound,0);
                    attack[1] = 1;
                    ammo--;
                    FIRE[1].set_y(mPosY+20);
                }
            default:
                break;
            }
        }
        if(EV.type== SDL_KEYUP)
        {
            switch (EV.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                jump_pressed = false;
                break;
            case SDL_SCANCODE_S:
                GRAVITY=18;
                break;
            default:
                break;
            }
        }
    }
    void move();
    void render();
    int getY()
    {
        return mPosY;
    }
    void cooldown(int a)
    {
        attack[a]=0;
    }
    int get_attack(int a)
    {
        return attack[a];
    }
    int get_ammo()
    {
        return ammo;
    }
    void add_ammo()
    {
        ammo++;
        if(ammo>3)   ammo=3;
    }
    void reset()
    {
        mPosY=250,y_vel=0;
        ammo=3;
        can_jump=0;
        jump_pressed=0;
        on_ground=0;
    }
private:
    double mPosY;
    double y_vel;
    bool jump_pressed;
    bool can_jump;
    bool on_ground;
    short add,add2;
    short status;
    bool attack[4]= {0,0,0,0};
    short ammo;
};
