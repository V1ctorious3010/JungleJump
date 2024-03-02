class nhanvat
{
public:
    const int character_WIDTH = 43;
    const int character_HEIGHT = 60;
    const int character_speed = 20;
    nhanvat()
    {
        mPosX=200,x_vel=0;
        mPosY=250,y_vel=0;
        jump_pressed=0;
        left_pressed=0;
        right_pressed=0;
        can_jump=0;
        on_ground=0;
    }
    void handleEvent( SDL_Event EV)
    {
        if(EV.type== SDL_KEYDOWN)
        {
            switch (EV.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                jump_pressed = true;
                break;
            case SDL_SCANCODE_A:
                left_pressed = true;
                direction=0;
                break;
            case SDL_SCANCODE_D:
                right_pressed = true;
                direction=1;
                break;
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
            case SDL_SCANCODE_A:
                left_pressed = false;
                break;
            case SDL_SCANCODE_D:
                right_pressed = false;
                break;
            default:
                break;
            }
        }

    }
    void move();
    void render();

private:
    double mPosX, mPosY;
    double x_vel,y_vel;
    int direction;
    bool jump_pressed;
    bool left_pressed;
    bool right_pressed;
    bool can_jump;
    bool on_ground;
};
