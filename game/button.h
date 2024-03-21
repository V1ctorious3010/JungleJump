#pragma once
#include <SDL.h>
#include<bits/stdc++.h>
#include"LTexture.h"
class Button
{
public:
    Button() {}
    Button(int t,int x,int y,int u,int v)
    {
        Rect= {x,y,u,v};
        isHovered=0;
        render();
        type=t;
        if(type==1)
        {
            if(!nHTexture.LoadImage("new_game_button.png"))
            {
                cout<<"cant load play button";
            }
            if(!HTexture.LoadImage("new_game_button1.png"))
            {
                cout<<"cant load play button2";
            }
        }
        if(type==0)
        {
            if(!nHTexture.LoadImage("exit_button.png"))
            {
                cout<<"cant load exit button";
            }
            if(!HTexture.LoadImage("exit_button1.png"))
            {
                cout<<"cant load exit button2";
            }
        }
        if(type==4)
        {
            if(!nHTexture.LoadImage("last_game_button.png"))
            {
                cout<<"cant load last button";
            }
            if(!HTexture.LoadImage("last_game_button1.png"))
            {
                cout<<"cant load last button2";
            }
        }
        if(type==3)
        {
            if(!nHTexture.LoadImage("pause_button.png"))
            {
                cout<<"cant load pause button";
            }
            if(!HTexture.LoadImage("pause_button1.png"))
            {
                cout<<"cant load pause button2";
            }
        }
        if(type==6)
        {
            if(!nHTexture.LoadImage("resume_button.png"))
            {
                cout<<"cant load resume button";
            }
            if(!HTexture.LoadImage("resume_button1.png"))
            {
                cout<<"cant load resume button2";
            }
        }
        if(type==7)
        {
            if(!nHTexture.LoadImage("replay_button.png"))
            {
                cout<<"cant load replay button";
            }
            if(!HTexture.LoadImage("replay_button1.png"))
            {
                cout<<"cant load replay button2";
            }
        }
        if(type==8)
        {
            if(!nHTexture.LoadImage("tutorial_button.png"))
            {
                cout<<"Can't load tutorial button";
            }
            if(!HTexture.LoadImage("tutorial_button2.png"))
            {
                cout<<"can't load tutorial button";
            }
        }
        if(type==9)
        {
            if(!nHTexture.LoadImage("home_button.png"))
            {
                cout<<"Can't load home button";
            }
            if(!HTexture.LoadImage("home_button1.png"))
            {
                cout<<"can't load home button";
            }
        }
    }
    void HandleEvent(const SDL_Event Event)
    {
        bool press=0;
        if (Event.type == SDL_MOUSEBUTTONDOWN &&Event.button.button == SDL_BUTTON_LEFT &&isHovered)
        {
            press=1;
        }
        else if(Event.type == SDL_MOUSEBUTTONUP )
        {

        }
        else if (Event.type==SDL_MOUSEMOTION)
        {
            if (isHovered!=IsWithinBounds(Event.motion.x, Event.motion.y))
            {
                isHovered=!isHovered;
                render();
            }
        }
        if(press)    Upd();
    }
    void Upd();
    void render();
    void RePos(int a,int b)
    {
        int w=Rect.w;
        int h=Rect.h;
        Rect= {a,b,w,h};
    }
private:
    bool IsWithinBounds(int x, int y)
    {
        if (x < Rect.x) return false;// Too far left
        if (x > Rect.x + Rect.w) return false; // Too far right
        if (y < Rect.y) return false; // Too high
        if (y > Rect.y + Rect.h) return false; // Too low
        return true;   // Inside rectangle
    }
    bool isHovered;
    SDL_Rect Rect;
    int type;
    LTexture nHTexture;
    LTexture HTexture;
};
