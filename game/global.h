#include<bits/stdc++.h>
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"character.h"
#include"button.h"
#include"coin.h"
#include"boss.h"
#include"boss2.h"
vector<int>TYPE= {0,0,1};
int VelX=0;
int Move_down=0;
const int deadY=660;
SDL_Rect san= {0,600,800,10};
const int Width=1200;
const int Height=740;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;

nhanvat wizard;
bool running=1;
TTF_Font *gFont;
bool PauseGame=0;
bool Died=0;
bool Rep;
///
LTexture Character_Texture[9];
LTexture Tutorial_Texture;
LTexture Background_Texture[3];
LTexture bullet;
LTexture st1,st2;
LTexture FireBall;
LTexture ScoreText;
LTexture HighScoreText;
LTexture MenuBackground;
LTexture IdleBoss[6],SlashingBoss[6],ThrowingBoss[6];
LTexture IdleBoss2,AttackingBoss2[4];
LTexture DirtBall;
LTexture Ammo[4];
LTexture Title;
Mix_Music *GameMusic=NULL;
Mix_Chunk *BlastSound=NULL;
Mix_Chunk *GainSound=NULL;
Mix_Chunk *LoseSound=NULL;
double down_speed=1.5;
int VELOCITY=0;
double SPEED=240;
const int FPS=60;
int Score=0;
int ScrollSpeed=12;
int scrollingOffset=5;
bool VaoGame=0;
LTexture Board;
int HighScore=0;
bool HuongDan=0;
bool ShowMenu=1;
int CurrentBackground;
LTexture Gem;
LTexture Gem1;
SDL_Color Black= {0,0,0};
SDL_Color White= {255,255,255};
void LTexture ::render(int x,int y,SDL_RendererFlip flip)
{
    SDL_Rect tmp= {x,y,mWidth,mHeight};
    SDL_RenderCopyEx(gRenderer,mTexture,NULL,&tmp,0.0,NULL, flip );

}
bool LTexture ::LoadImage(string file_path)
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
    if(!Background_Texture[0].LoadImage("bg2.png"))
    {
        cout<<"can't load bg";
        return ;
    }
    if(!Background_Texture[1].LoadImage("bg3.png"))
    {
        cout<<"can't load bg";
        return ;
    }
    if(!Board.LoadImage("bang.png"))
    {
        cout<<"can't load bang";
        return ;
    }
    if(!MenuBackground.LoadImage("background2.png"))
    {
        cout<<"can't load menu bg";
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
    if(!Title.LoadImage("new_title.png"))
    {
        cout<<"can't load title";
        return ;
    }
    if(!Tutorial_Texture.LoadImage("tutorial.png"))
    {
        cout<<"can't load tutor";
        return ;
    }
    if(!Gem.LoadImage("ruby.png"))    cout<<"Can't load ruby"<<endl;
    if(!Gem1.LoadImage("diamond.png")) cout<<"Can't load diamond"<<endl;
    Character_Texture[1].LoadImage("run/run1.png");
    Character_Texture[2].LoadImage("run/run2.png");
    Character_Texture[3].LoadImage("run/run3.png");
    Character_Texture[4].LoadImage("run/run4.png");
    Character_Texture[5].LoadImage("run/run5.png");
    Character_Texture[6].LoadImage("run/run6.png");
    Character_Texture[7].LoadImage("run/run7.png");
    Character_Texture[0] .LoadImage("run/run0.png");
    JumpSound=Mix_LoadWAV( "jumpsound.wav" );
    AttackSound=Mix_LoadWAV("AttackSound.wav");
    ButtonSound=Mix_LoadWAV("button_sound.wav");
    GameMusic=Mix_LoadMUS("bgm.wav");
    BlastSound=Mix_LoadWAV("blast.wav");
    Mix_VolumeChunk(ButtonSound,30);
    Mix_VolumeChunk(AttackSound,30);
    Mix_VolumeChunk(JumpSound,30);
    Mix_VolumeMusic(50);
    GainSound=Mix_LoadWAV("gainsound.wav");
    LoseSound=Mix_LoadWAV("losesound.wav");
    string s="Idle/0_Golem_idle_00";
    for(int i=0; i<=5; i++)
    {
        string tmp=s;
        tmp+=to_string(i);
        tmp+=".png";
        if(!IdleBoss[i].LoadImage(tmp))  cout<<"CANT";
    }
    s="Slashing/0_Golem_Slashing_00";
    for(int i=0; i<=5; i++)
    {
        string tmp=s;
        tmp+=to_string(i);
        tmp+=".png";
        // cout<<tmp<<endl;
        if(!SlashingBoss[i].LoadImage(tmp)) cout<<"CANT";
    }
    s="Throwing/0_Golem_Throwing_00";
    for(int i=0; i<=5; i++)
    {
        string tmp=s;
        tmp+=to_string(i);
        tmp+=".png";
        ThrowingBoss[i].LoadImage(tmp);
    }
    DirtBall.LoadImage("dirtball.png");
    bullet.LoadImage("boss2/Charge_1.png");
    s="boss2/Attack_";
    for(int i=1; i<=4; i++)
    {
        string tmp=s;
        tmp+=to_string(i);
        tmp+=".png";
        AttackingBoss2[i-1].LoadImage(tmp);
    }
    if(!IdleBoss2.LoadImage("boss2/Idle1.png"));

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
    mPosX+=x_vel/60;
    if(mPosX<20)   mPosX=20;
    if(mPosX>800)   mPosX=800;

    if(!on_ground)  y_vel += GRAVITY;
    if (jump_pressed&&can_jump)
    {
        GRAVITY=18;
        Mix_PlayChannel(-1,JumpSound,0);
        on_ground=0;
        can_jump = false;
        y_vel = -700;
    }
    double foot=mPosY+129;
    double nxtfoot=mPosY+y_vel/60+130;
    if(foot<=deadY&&nxtfoot>=deadY)
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
    if(PauseGame)
    {

    }
    else
    {
        if(on_ground)     Character_Texture[status].render(mPosX,mPosY,flip);
        else    Character_Texture[0].render(mPosX,mPosY,flip);
    }
}
struct CucDa
{
    double x;
    double y;
    LTexture stone[2];
    CucDa() {}
    CucDa(int t)
    {
        x=t;
        y=deadY-80;
        stone[0].LoadImage("stone.png");
        stone[1].LoadImage("stone1.png");
    }
    void render(int Cur)
    {
        stone[Cur].render(x,y);
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
    void reset(int t)
    {
        x=t;
        y=deadY-80;
    }

};
CucDa Da1(Width+20);
CucDa Da2(Width+500);

void fireball::render(int a)
{
    if(x<Width) FireBall.render(x,y);
    else
    {
        wizard.cooldown(a);
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
    Play.sink();
    LoadGame.sink();
    Tutorial.sink();
    Exit.sink();
    Pause.sink();
    Resume.sink();
    Replay.sink();
    Home.sink();
    SDL_Delay(125);
    if(type==1)   Rep=1,VaoGame=1,ShowMenu=0,PauseGame=0,Died=0;
    if(type==0)   running=0;
    if(type==3)   PauseGame=1;
    if(type==6)   PauseGame=0;
    if(type==7)   Died=0,Rep=1;
    if(type==9)   HuongDan=0,ShowMenu=1,VaoGame=0,PauseGame=0,Died=0;
    if(type==8)   HuongDan=1;
}
coin::coin()
{
    t=rnd(0,1);
    x=Width+100;
    y=400;
    if(t==1)   score=50;
    if(t==0)   score=25;
}
void coin::render()
{
    if(t==0)    Gem.render(x,y);
    if(t==1)    Gem1.render(x,y);
}
void coin::move()
{
    x-=ScrollSpeed;
    if(x<=-50)   reset();
}
void coin::reset()
{
    x=Width+100;
    t=rnd(0,1);
    if(t==1)   score=50;
    if(t==0)   score=25;
}
coin::coin(int a,int c)
{
    x=a;
    t=c;
    if(t==1)   score=50;
    if(t==0)   score=25;
}
void boss::render_idle(int stt)
{
    int tmp=stt%6;
    IdleBoss[tmp].render(x,y);
}
void boss::render_slashing(int stt)
{
    int tmp=stt%6;
    SlashingBoss[tmp].render(x,y);
}
void boss::render_throwing(int stt)
{
    int tmp=stt%6;
    ThrowingBoss[tmp].render(x,y);
}
void dirtball::render()
{
    DirtBall.render(x,y);
}

void dirtball:: move()
{
    if(BossAt2)
    {
        x-=15;
        if(x<0)     BossAt2=0,x=800,y=500;
    }
    if(BossAt1)
    {
        y+=10;
        if(y>deadY)     BossAt1=0,x=800,y=500;
    }
}
void boss::action()
{
    //render_idle(stt);
    if(!status)   render_idle(stt);
    if(status==1)   render_slashing(stt);
    if(status==2)   render_throwing(stt);
    add++;
    if(add>5)   stt++,add=0;
    if(stt==6)
    {
        if(status==2)     BossAt2=1;
        if(status==1)     BossAt1=1,Dirt= {wizard.getX(),0};
        if(status)  Rest=100;
        stt=0;
        add=0;
        status=0;
    }
    Dirt.Handle();
}
void thunder::render()
{
    bullet.render(x,y);
}
void thunder::move()
{
    x-=x_vel/60;
    for (int i = 1; i <= 3; i++)
    {
        if(wizard.get_attack(i))
        {
            if (checkCollision(FIRE[i].get(),get()))
            {
                Mix_PlayChannel(-1,AttackSound,0);
                reset();
                BOSS2.attack=0;
                wizard.cooldown(i);
            }
        }
    }
    if(x<0)   reset(),BOSS2.attack=0;

}
void boss2::action()
{
    if(!status)     render_idle(stt);
    if(status==1)   render_at(stt);
    add++;
    if(add>7)   stt++,add=0;
    if(stt==4&&status==1)
    {
        BOSS2.attack=1;
        Rest=100;
        stt=0;
        add=0;
        status=0;
    }
}
void boss2::render_idle(int tmp)
{
    IdleBoss2.render(x,y);
}
void boss2::render_at(int stt)
{
    int tmp=stt%4;
    AttackingBoss2[tmp].render(x,y);
}
