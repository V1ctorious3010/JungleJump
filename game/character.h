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
            default:
                break;
            }
        }

    }
    void move();
    void render();

private:
    double mPosX, mPosY;
    double y_vel;
    int direction;
    bool jump_pressed;
    bool can_jump;
    bool on_ground;
    int add;
    int status;
};
