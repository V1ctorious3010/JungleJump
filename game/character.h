#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include"SDL_mixer.h"
double GRAVITY=18;
Mix_Chunk *JumpSound=NULL;
Mix_Chunk *AttackSound=NULL;
int CURBOSSx;
int CURBOSSy;
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
struct Ulti
{
    bool cast;
    int x=240;
    int y=530;
    void render();
    void move();
    void reset();
    SDL_Rect get()
    {
        return {x,y,25,25};
    }
} R;
class nhanvat
{
public:
    bool activate_skill;
    int timeskill;
    int wait_timeskill;
    double mPosY, mPosX;
    const int character_WIDTH = 90;
    const int character_HEIGHT = 130;
    const int character_speed = 20;
    nhanvat()
    {
        mPosY=250,y_vel=0;
        mPosX=240;
        jump_pressed=0;
        tele_pressed=0;
        check_Q=0;
        on_ground=0;
        activate_skill=0;
        timeskill=0;
        wait_timeskill=600;
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
            case SDL_SCANCODE_Q:
                if(check_Q==false&&tele_pressed==false)tele_pressed=true,check_Q=true;
                else tele_pressed=false;
                break;
            case SDL_SCANCODE_W:
                jump_pressed = true;
                break;
            case SDL_SCANCODE_S:
                GRAVITY=300;
                break;
            case SDL_SCANCODE_K:
                if(ult_cooldown>=300&&CURBOSSx&&CURBOSSy) ult_cooldown=0,R.cast=1,R.reset();
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
            case SDL_SCANCODE_Q:
                tele_pressed=false;
                check_Q=false;
                break;
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
    void update_ammo(int a)
    {
        ammo = a;
    }
    int getX()
    {
        return mPosX;
    }
    void add_ammo()
    {
        ammo++;
        if(ammo>3)   ammo=3;
    }
    void reset()
    {
        mPosY=250,y_vel=0;
        mPosX=240;
        //ammo=3;
        jump_pressed=0;
        tele_pressed=0;
        check_Q=0;
        on_ground=0;
        activate_skill=0;
        timeskill = 0;
        wait_timeskill=600;
    }
    int get_cooldownR()
    {
        return ult_cooldown;
    }
private:

    double y_vel;
    double x_vel;
    bool jump_pressed;
    SDL_RendererFlip flip=SDL_FLIP_NONE;
    bool tele_pressed;
    bool check_Q;
    bool on_ground;
    short add,add2;
    short status;
    bool attack[4]= {0,0,0,0};
    short ammo;
    int ult_cooldown=1000;
};
