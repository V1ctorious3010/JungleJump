#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

#include"character.h"
#include"button.h"
vector<int>TYPE= {0,0,1};
int VelX=0;
int Move_down=0;
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
const int deadY=620;
SDL_Rect san= {0,600,800,10};
const int Width=1200;
const int Height=800;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
LTexture Character_Texture;
LTexture Background_Texture;
LTexture bullet;
LTexture st1,st2;
nhanvat wizard;
fireball Fire;
bool running=1;
TTF_Font *gFont;
bool PauseGame=0;
////
LTexture FireBall;
LTexture ScoreText;
LTexture MenuBackground;
LTexture Ammo[4];
double down_speed=1.5;
int VELOCITY=0;
double SPEED=240;
const int FPS=60;
int Score=0;
int ScrollSpeed=5;
int scrollingOffset=0;
bool bullet_on_screen=1;
bool VaoGame=0;
LTexture Board;
////button color

///

void LTexture ::  render(int x,int y)
{
    SDL_Rect tmp= {x,y,mWidth,mHeight};
    SDL_RenderCopy(gRenderer,mTexture,NULL,&tmp);
}
bool LTexture ::  LoadImage(string file_path)
{
    free();
    SDL_Surface* Sur=IMG_Load(file_path.c_str());
    if(Sur==NULL)   return 0;
    SDL_SetColorKey( Sur, SDL_TRUE, SDL_MapRGB( Sur->format, 255, 255, 255 ) );
    SDL_Texture *newTexture=SDL_CreateTextureFromSurface(gRenderer,Sur);
    if(newTexture==NULL) return 0;
    mWidth=Sur->w;
    mHeight=Sur->h;
    mTexture=newTexture;
    return (mTexture!=NULL);
}
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    free();
    SDL_Surface* textSurface=TTF_RenderText_Solid(gFont,textureText.c_str(),textColor );
    if(textSurface==NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",TTF_GetError());
    }
    else
    {
        mTexture=SDL_CreateTextureFromSurface(gRenderer,textSurface);
        if(mTexture==NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n",SDL_GetError());
        }
        else
        {
            mWidth=textSurface->w;
            mHeight=textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture!=NULL;
}
void LoadTexture()
{
    if(!Background_Texture.LoadImage("bg.png"))
    {
        cout<<"can't load bg";
        return ;
    }
    if(!Board.LoadImage("bang.png"))
    {
        cout<<"can't load bg";
        return ;
    }
    if(!MenuBackground.LoadImage("menu_background.png"))
    {
        cout<<"can't load menu bg";
        return ;
    }
    if(!bullet.LoadImage("bullet.png"))
    {
        cout<<"can't load bullet";
        return ;
    }
    if(!FireBall.LoadImage("fire/fire2.png"))
    {
        cout<<"can't load fire";
        return ;
    }
    for(int i=1; i<=4; i++)
    {
        if(!Ammo[i].LoadImage("ammo.png"))   cout<<"Can't load ammo";
    }
}
bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    if( bottomA <= topB ) return false;
    if( topA >= bottomB ) return false;
    if( rightA <= leftB ) return false;
    if( leftA >= rightB ) return false;
    return true;
}
void nhanvat::move()
{
    if(!on_ground)  y_vel += GRAVITY;
    if (jump_pressed && can_jump)
    {
        on_ground=0;
        can_jump = false;
        y_vel = -700;
    }
    double foot=mPosY+129;
    double nxtfoot=mPosY+y_vel/60+130;
    if(foot<deadY&&nxtfoot>=deadY)
    {
        mPosY=deadY-character_HEIGHT;
        y_vel=0;
        can_jump=1;
        on_ground=1;
    }
    else on_ground=0,can_jump=0;
    mPosY+= y_vel/60;
}

void nhanvat::render()
{
    add+=1;
    if(add==5)        add=0,status=(status+1)%8;
    if(!status)       status++;
    if(status==1)     Character_Texture.LoadImage("run/run1.png");
    if(status==2)     Character_Texture.LoadImage("run/run2.png");
    if(status==3)     Character_Texture.LoadImage("run/run3.png");
    if(status==4)     Character_Texture.LoadImage("run/run4.png");
    if(status==5)     Character_Texture.LoadImage("run/run5.png");
    if(status==6)     Character_Texture.LoadImage("run/run6.png");
    if(status==7)     Character_Texture.LoadImage("run/run7.png");
    if(!on_ground)    Character_Texture.LoadImage("run/run0.png");
    /*else
    {
        add2++;
        if(add2==7)        add2=0,status2=(status2+1)%7;
        if(!status2)       status2++;
        if(status2==0)     Character_Texture.LoadImage("attack/fire0.png");
        if(status2==1)     Character_Texture.LoadImage("attack/fire1.png");
        if(status2==2)     Character_Texture.LoadImage("attack/fire2.png");
        if(status2==3)     Character_Texture.LoadImage("attack/fire3.png");
        if(status2==4)     Character_Texture.LoadImage("attack/fire4.png");
        if(status2==5)     Character_Texture.LoadImage("attack/fire5.png");
        if(status2==6)     Character_Texture.LoadImage("attack/fire6.png"),attack=0,status2=0;
    }*/
    Character_Texture.render(240,mPosY);
    // SDL_Delay(100);
}
///////ball;
struct ball
{
    double x;
    double y;
    const double x_vel=1200;
    ball()
    {
        x=Width-100;
        int t=rnd(0,1);
        if(t)y=deadY-200;
        else y=deadY-80;
    }
    void render()
    {
        bullet.render(x,y);
    }
    void move()
    {
        x-=x_vel/60;
    }
    void reset()
    {
        x=Width-100;
        int t=rnd(0,1);
        if(t)y=deadY-200;
        else y=deadY-80;
    }
    SDL_Rect get()
    {
        return {(int)x,(int)y,50,50};
    }

} A;
struct CucDa
{
    double x;
    double y;
    LTexture stone;
    CucDa() {}
    CucDa(int t)
    {
        x=t;
        y=deadY-73;
        if(!stone.LoadImage("stone.png"))
        {
        }
    }
    void render()
    {
        stone.render(x,y);
    }
    void move()
    {
        x-=ScrollSpeed;
        if(x<0)
        {
            int t=rnd(0,2);
            if(!t)     x=Width+700;
            if(t==1)   x=Width+100;
            if(t==2)   x=Width+1300;
        }
    }
    SDL_Rect get()
    {
        return {(int)x,(int)y,120,60};
    }

};
CucDa Da1(Width+20);
CucDa Da2(Width+500);
void fireball::render()
{
    if(x<Width) FireBall.render(x,y);
    else
    {
        wizard.cooldown();
        x=255;
        y=525;
    }
}
void Button::render()
{
    if(isHovered)     HTexture.render(Rect.x,Rect.y);
    else nHTexture.render(Rect.x,Rect.y);
}
void Button::Upd()
{
    if(type==1)      VaoGame=1;
    if(type==0)      running=0;
    if(type==3||type==6)
    {
        PauseGame^=1;
        cout<<PauseGame<<endl;
    }
}
