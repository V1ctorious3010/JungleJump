

double GRAVITY=18;
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
            case SDL_SCANCODE_S:
                GRAVITY=300;
                break;
            case SDL_SCANCODE_J:
                attack=1;
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
    void cooldown()
    {
        attack=0;
    }
    int get_attack()
    {
        return attack;
    }
private:
    double mPosY;
    double y_vel;
    bool jump_pressed;
    bool can_jump;
    bool on_ground;
    short add,add2;
    short status;
    bool attack=0;
};
