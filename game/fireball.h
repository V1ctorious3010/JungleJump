#pragma once
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
    void render();
}FIRE;
