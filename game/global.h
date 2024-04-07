#include<bits/stdc++.h>
using namespace std;

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include"character.h"
#include"button.h"
#include"coin.h"

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l,int r)
{
    return l+rng()%(r-l+1);
}
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
skill SKILL;
coin GOLD[10];
int gold_number=-1;
bool running=1;
TTF_Font *gFont;
bool PauseGame=0;
bool Died=0;
bool Rep;
int blood = 246;
///
LTexture BloodBar;
LTexture Character_Texture[9];
LTexture Tutorial_Texture;
LTexture Background_Texture[3];
LTexture bullet[2];
//LTexture st1,st2;
LTexture FireBall;
LTexture ScoreText;
LTexture HighScoreText;
LTexture MenuBackground;
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
bool bullet_on_screen=1;
bool VaoGame=0;
LTexture Board;
int HighScore=0;
bool HuongDan=0;
bool ShowMenu=1;
bool Choitiep=0;
int CurrentBackground;
LTexture Gem;
LTexture Gem1;
LTexture Heart;
LTexture Skill;
LTexture Cloud;
LTexture Teleport;
LTexture Position_teleport;
LTexture Laze_gun_bottom;
LTexture Laze_gun_top;
LTexture Laze;
LTexture Gold;
void LTexture ::render(int x,int y)
{
    SDL_Rect tmp= {x,y,mWidth,mHeight};
    SDL_RenderCopy(gRenderer,mTexture,NULL,&tmp);
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
    if(!bullet[0].LoadImage("bullet.png"))
    {
        cout<<"can't load bullet";
        return ;
    }
    if(!bullet[1].LoadImage("bullet1.png"))
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
    if(!BloodBar.LoadImage("bloodbar.png"))
    {
        cout<<"can't load bloodbar";
        return ;
    }
    if(!Heart.LoadImage("traitim.png"))
    {
        cout<<"can't load heart";
        return ;
    }
    if(!Skill.LoadImage("skill.png"))
    {
        cout<<"can't load skill";
        return ;
    }
    if(!Cloud.LoadImage("cloud.png"))
    {
        cout<<"can't load cloud";
        return ;
    }
    Teleport.LoadImage("teleport.png");
    Position_teleport.LoadImage("position_teleport.png");
    Laze_gun_bottom.LoadImage("laze_gun_bottom.png");
    Laze_gun_top.LoadImage("laze_gun_top.png");
    Gold.LoadImage("gold.png");
    Laze.LoadImage("laze.png");
    if(!Gem.LoadImage("bronze.png"))    cout<<"Can't load ruby"<<endl;
    if(!Gem1.LoadImage("sliver.png")) cout<<"Can't load diamond"<<endl;
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
    if(activate_skill==0||SKILL.t==3){
        if(mPosX>240){
            mPosX-=5;
        }
        if(mPosX<240){
            mPosX=240;
        }
        SKILL.mPosX_skill2=240+150;
        if(!on_ground)  y_vel += GRAVITY;
        if (jump_pressed && on_ground)
        {
            Mix_PlayChannel(-1,JumpSound,0);
            on_ground=0;
            y_vel = -700;
        }
        double foot=mPosY+129;
        double nxtfoot=mPosY+y_vel/60+130;
        if(foot<=deadY&&nxtfoot>=deadY)
        {
            mPosY=deadY-character_HEIGHT;
            y_vel=0;
            on_ground=1;
        }
        else on_ground=0;
        mPosY+= y_vel/60;
    }
    if (activate_skill==1){
        if(SKILL.t==1){
            if(!on_ground){
                mPosY+=5;
            }
            if(jump_pressed){
                mPosY-=15;
                on_ground=0;
            }

            double foot=mPosY+129;
            double nxtfoot=mPosY+5+130;
            if(foot<=deadY&&nxtfoot>=deadY)
            {
                mPosY=deadY-character_HEIGHT;
                on_ground=1;
            }
            else{
                on_ground=0;
                Cloud.render(270,mPosY+119);
            }
        }
        else if(SKILL.t==2){
            if(tele_pressed==true){
                if(SKILL.mPosX_skill2<850){
                    mPosX=SKILL.mPosX_skill2;
                    mPosY=SKILL.mPosY_skill2-70;//do lech anh
                    SKILL.mPosX_skill2+=150;
                    tele_pressed=false;
                }
                else{
                    mPosY=SKILL.mPosY_skill2-70;
                    tele_pressed=false;
                }
            }
            if(mPosX>240){
                mPosX-=5;
                SKILL.mPosX_skill2-=5;
            }
            if(mPosX<240){
                mPosX=240;
                SKILL.mPosX_skill2=mPosX+150;
            }
        }
        else if(SKILL.t==3){
            if(SKILL.mPosY_top_skill3==0){
                Laze.render(710,0);
            }
            Laze_gun_bottom.render(SKILL.mPosX_bottom_skill3,SKILL.mPosY_bottom_skill3);
            Laze_gun_top.render(SKILL.mPosX_top_skill3,SKILL.mPosY_top_skill3);
            if(SKILL.mPosY_top_skill3 > 0){
                SKILL.mPosY_top_skill3-=15;
                SKILL.mPosY_bottom_skill3+=15;
            }
            if(SKILL.mPosY_top_skill3 < 0){
                SKILL.mPosY_top_skill3 = 0;
                SKILL.mPosY_bottom_skill3 = 690;
            }

        }
    }
}

void nhanvat::render()
{
    if(SKILL.t==2 && activate_skill==1){
        Teleport.render(mPosX,mPosY);
        Position_teleport.render(SKILL.mPosX_skill2,SKILL.mPosY_skill2);
        SKILL.mPosY_skill2+=SKILL.skill2_vel;
        if(SKILL.mPosY_skill2+50>=deadY) SKILL.skill2_vel=-7;
        if(SKILL.mPosY_skill2<=0) SKILL.skill2_vel=7;
    }
    else{
        add+=1;
        if(add==5)        add=0,status=(status+1)%8;
        if(!status)       status++;
        if(PauseGame)
        {

        }
        else
        {
            if(on_ground)     Character_Texture[status].render(mPosX,mPosY);
            else    Character_Texture[0].render(mPosX,mPosY);
        }
    }
}
///////ball;
struct ball
{
    double x;
    double y;
    int cnt;
    int CurState=0;
    double x_vel=1200;
    ball()
    {
        x=Width-100;
        int t=rnd(0,1);
        if(t)y=deadY-200;
        else y=deadY-80;
    }
    void render()
    {
        bullet[CurState].render(x,y);
    }
    void move()
    {
        x-=x_vel/60;
        cnt++;
        if(cnt>=10)  CurState^=1,cnt=0;
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
//CucDa Da1;
//CucDa Da2;

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
    if(type== 4)  Choitiep=1,VaoGame=1,ShowMenu=0,PauseGame=0,Died=0;
    if(type==0)   running=0;
    if(type==3)   PauseGame=1;
    if(type==6)   PauseGame=0;
    if(type==7)   Died=0,Rep=1;
    if(type==9)   HuongDan=0,ShowMenu=1,VaoGame=0,PauseGame=0,Died=0;
    if(type==8)   HuongDan=1;
}
coin::coin()
{
    t=rate_coin[rnd(0,9)];
    x=Width+100;
    y=400;
    if(t==1)   score=50;
    if(t==0)   score=25;
    if(t==2)   upblood = 80;
}
void coin::render()
{
    if(t==0)    Gem.render(x,y);
    if(t==1)    Gem1.render(x,y);
    if(t==2)    Heart.render(x,y);
    if(t==3)    Gold.render(x,y);
}
void coin::move()
{
    x-=ScrollSpeed;
    if(x<=-50)   reset();
}
void coin::reset()
{
    x=Width+100;
    t=rate_coin[rnd(0,9)];
    if(t==1)   score=50;
    if(t==0)   score=25;
    if(t==2)   upblood=80;
}
void coin::change(int a, int b){
    x = a;
    y = b;
    score = 100;
    t = 3;
}
coin::coin(int a,int c)
{
    x=a;
    t=c;
    if(t==1)   score=50;
    if(t==0)   score=25;
    if(t==2)   upblood=80;
}
skill::skill(){
    t = number_skill[rnd(0,3)];
    x = -100;
    y = 400;
    mPosY_skill2 = 400;//vi an skill o vi tri y = 400
    mPosX_skill2 = wizard.mPosX+150;
    skill2_vel=7;
    mPosX_top_skill3 = 700, mPosY_top_skill3 = 363;
    mPosX_bottom_skill3=700, mPosY_bottom_skill3=400;
}
void skill::render(){
    Skill.render(x,y);
}
void skill::move(){
    x-=ScrollSpeed;
}
void skill::reset(){
    t = number_skill[rnd(0,3)];
    x = -100;
    y = 400;
    mPosY_skill2 = 400;//vi an skill o vi tri y = 400
    mPosX_skill2 = wizard.mPosX+150;
    skill2_vel=7;
    mPosX_top_skill3=700, mPosY_top_skill3=326;
    mPosX_bottom_skill3=700, mPosY_bottom_skill3=363;
}
