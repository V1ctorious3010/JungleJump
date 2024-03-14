#pragma once
#include <SDL.h>

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
    }
    void HandleEvent(const SDL_Event Event)
    {
        if (Event.type == SDL_MOUSEBUTTONDOWN &&Event.button.button == SDL_BUTTON_LEFT &&isHovered)
        {
            Upd();
        }
        else if (Event.type==SDL_MOUSEMOTION)
        {
            if (isHovered!=IsWithinBounds(Event.motion.x, Event.motion.y))
            {
                isHovered=!isHovered;
                render();
            }
        }
    }
    void Upd();
    void render();
    void RePos(int a,int b)
    {
        int w=Rect.w;
        int h=Rect.h;
        Rect={a,b,w,h};
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
};
