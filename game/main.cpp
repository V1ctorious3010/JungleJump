#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>
#include"global.h"
#include"LTexture.h"
#include<SDL_ttf.h>
#include<SDL_mixer.h>
int reload=0;
string ScoreStr="Score :";
string HighScoreStr="HighScore :";
int32_t lastUPD=0.0;
int No_Boss_Time=0;
void RenderText(string &s,int score,int x,int y,SDL_Color &X)
{
    string tmp=s;
    tmp+=to_string(score);
    if(!ScoreText.loadFromRenderedText(tmp,X))
    {
        printf( "Failed to render text texture!\n");
    }
    ScoreText.render(x,y);
}
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)   cout<<"Can't init"<<endl;
    gWindow = SDL_CreateWindow( "JungleJump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN );
    if(gWindow==NULL)    return 0;
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(gRenderer==NULL)   return 0;
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        cout<<"SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ;
        return 0;
    }
    if( TTF_Init() == -1 )
    {
        cout<< "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() ;
        return 0;
    }
    gFont = TTF_OpenFont( "dot_to_dot.ttf", 50);
    if( gFont == NULL )
    {
        cout<< "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() ;
        return 0;
    }
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        return 0;
    }

    return 1;
}
void close()
{
    //Free loaded images
    for(int i=0; i<=7; i++)  Character_Texture[i].free();
    Background_Texture[CurrentBackground].free();
    for(int i=1; i<=4; i++)    Ammo.free();
    ScoreText.free();
    FireBall.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    TTF_Quit();
    Mix_Quit();

}
int main(int argc,char * argv[])
{
    ios_base::sync_with_stdio(0);
    // freopen("x.out","w",stdout);
    ifstream in;
    in.open("luugame.txt");
    int so_lg_dan, x_Da1, x_Da2;
    in >> Score >> HighScore >> CurrentBackground >> x_Da1 >> x_Da2 >> so_lg_dan >> blood;
    in >> wizard.activate_skill >> SKILL.t >> wizard.timeskill>>wizard.wait_timeskill;
    wizard.update_ammo(so_lg_dan);
    ofstream out;
    out.open("luugame.txt");
    if(!init())
    {
        cout<<"Can't init"<<endl;
        return 0;
    }
    LoadTexture();
    CucDa Da1(x_Da1);
    CucDa Da2(x_Da2);
    coin COIN;
    for(int i = 0; i <= 99; i++)
    {
        GOLD[i].t=3;
        GOLD[i].change(-100,-100);
        GOLD[i].score = 15;
    }
    Died=0;
    Play.reconstruct(1,450,293,300,75);
    LoadGame.reconstruct(4,450,393,300,75);
    Tutorial.reconstruct(8,453,493,300,75);
    Exit.reconstruct(0,450,593,300,75);
    Pause.reconstruct(3,1200-60,10,50,50);
    Resume.reconstruct(6,510,400,100,100);
    Replay.reconstruct(7,510,400,100,100);
    Home.reconstruct(9,1200-60,10,100,100);
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,36,121,126,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    Mix_PlayMusic(GameMusic,-1);
    while(running)
    {
        //HighScore=0;
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                running=0;
            }
            if(HuongDan)
            {
                Home.HandleEvent(EV);
            }
            if(ShowMenu)           //o menu
            {
                Play.HandleEvent(EV);
                Exit.HandleEvent(EV);
                Tutorial.HandleEvent(EV);
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                MenuBackground.render(0,0);
                Title.render(190,50);
                Play.render();
                Tutorial.render();
                Exit.render();
                LoadGame.render();
                LoadGame.HandleEvent(EV);
            }
            if(PauseGame)
            {
                Resume.HandleEvent(EV);
                Home.HandleEvent(EV);
                Replay.HandleEvent(EV);
            }
            if(VaoGame&&!PauseGame&&!Died)         //dang choi
            {
                wizard.handleEvent(EV);
                Pause.HandleEvent(EV);
            }
            if(Died)
            {
                Replay.HandleEvent(EV);
                Home.HandleEvent(EV);
            }
        }
        if(Choitiep)
        {
            VaoGame=1;
            ScrollSpeed=5;
            scrollingOffset=5;
            GRAVITY=18;
            Choitiep=0;
            reload=0;
        }
        if(Rep)
        {
            blood = 246;
            Score=0;
            CurrentBackground = 0;
            VaoGame=1;
            ScrollSpeed=5;
            scrollingOffset=5;
            Da1.reset(Width+20),Da2.reset(Width+400);
            wizard.reset();
            wizard.update_ammo(3);
            GRAVITY=18;
            Rep=0;
            reload=0;
            No_Boss_Time=0;
            CURBOSSx=0;
            CURBOSSy=0;
            BOSS.reset();
            BOSS2.reset();
            BOSS3.reset();
            Dirt.reset();
            A.reset();
            B.reset();
            for(int i=1;i<=9;i++)     FLAME[i].reset(i);
        }
        if(HuongDan)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Home.RePos(Width-60,10);
            Background_Texture[CurrentBackground].render(0,0);
            Tutorial_Texture.render(200,90);
            Home.render();
        }
        if(VaoGame&&!PauseGame&&!Died)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Background_Texture[CurrentBackground].render( scrollingOffset, 0 );
            Background_Texture[CurrentBackground].render( scrollingOffset + Background_Texture[CurrentBackground].getWidth(), 0 );
            Da1.render(CurrentBackground);
            Da2.render(CurrentBackground);
            wizard.render();
            Pause.render();
            COIN.render();
            SKILL.render();
            for(int i = 0; i <= 99; i++)
            {
                GOLD[i].render();
            }
            Da2.move();
            Da1.move();
            wizard.move();
            COIN.move();
            SKILL.move();
            for(int i = 0; i <= 99; i++)
            {
                GOLD[i].move();
            }
            wizard.wait_timeskill++;
            if(wizard.wait_timeskill==1080)
            {
                SKILL.x = Width +100;
                if(checkCollision(SKILL.get(),COIN.get()))
                {
                    SKILL.x +=100;
                }
                wizard.wait_timeskill=0;
            }
            if(wizard.activate_skill==1)
            {

                wizard.timeskill++;
                if(wizard.timeskill==600)
                {
                    wizard.timeskill=0;
                    wizard.activate_skill=0;
                    SKILL.reset();
                }
            }
            BloodBar.render(10, 10);
            SDL_Rect mau = {71,24,blood,25};
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
            SDL_RenderFillRect( gRenderer, &mau);
            SDL_Rect tia_laze= {710,0,20,700};
            SDL_Rect hitbox= {wizard.getX(),wizard.getY(),1,110};
            bool has_boss=(BOSS.HP>0)||(BOSS2.HP>0)||(BOSS3.HP>0);
            if(!has_boss)  No_Boss_Time++,CURBOSSx=0,CURBOSSy=0;
            if(No_Boss_Time>=300)
            {
                int R=2;
                if(Score>=500)      R=3;
                No_Boss_Time=0;
                int t=rnd(1,R);
                if(t==1)  BOSS.heal();
                if(t==2)  BOSS2.heal();
                if(t==3)  BOSS3.heal(),CURBOSSx=40,CURBOSSy=7;
            }
            if(BOSS2.attack)
            {
                portal.render(900,PortalY);
                A.move();
                A.render();
            }
            if(BOSS3.attack)
            {
                int dem=0;
                for(int i=0; i<=6; i++)
                {
                    if(FLAME[i].exist)
                    {
                        FLAME[i].move();
                        FLAME[i].render();
                    }
                    else
                    {
                        dem++;
                        FLAME[i].reset(i);
                    }
                }
                if(dem==7)   BOSS3.status=1,BOSS3.stt=0,BOSS3.add=0,BOSS3.attack=0;
            }
            if(R.cast&&CURBOSSx&&CURBOSSy&&has_boss)
            {
                R.render();
                R.move();
            }
            if(checkCollision(hitbox,Da1.get())||checkCollision(hitbox,Da2.get()))
            {
                Mix_PlayChannel(-1,LoseSound,0);
                blood -= 3;
                if (blood < 0) Died=1,blood=246;
            }
            if(checkCollision(hitbox,COIN.get()))
            {

                if (COIN.t == 2)
                {
                    blood += COIN.upblood;
                    if (blood > 246) blood = 246;
                }
                else Score+=COIN.score;
                Mix_PlayChannel(-1,GainSound,0);
                COIN.reset();
            }
            if(checkCollision(hitbox,SKILL.get()))
            {
                wizard.activate_skill=1;
                SKILL.x = -100;
            }
            for(int i = 0; i <= 99; i++)
            {
                if(checkCollision(hitbox,GOLD[i].get()))
                {
                    Score+=GOLD[i].score;
                    GOLD[i].change(-100,-100);
                }
            }
            if(SKILL.t == 3 && wizard.activate_skill==1)
            {
                if(checkCollision(tia_laze,Da1.get()))
                {
                    gold_number++;
                    if(gold_number == 100) gold_number=0;
                    GOLD[gold_number].change(Da1.x,Da1.y);
                    Da1.x = -500;
                }
                if(checkCollision(tia_laze,Da2.get()))
                {
                    gold_number++;
                    if(gold_number == 100) gold_number=0;
                    GOLD[gold_number].change(Da2.x,Da2.y);
                    Da2.x = -500;
                }
                if(checkCollision(tia_laze, Dirt.get()))
                {
                    gold_number++;
                    if(gold_number == 100) gold_number=0;
                    GOLD[gold_number].change(Dirt.x,Dirt.y);
                    Dirt.x = 800;
                    BossAt1 = 0;
                }
                if(checkCollision(tia_laze, A.get()))
                {
                    gold_number++;
                    if(gold_number == 100) gold_number=0;
                    GOLD[gold_number].change(A.x,A.y);
                    A.reset();
                    BOSS2.attack=0;
                }
                for (int i = 0; i <= 9; i++)
                {
                    if(checkCollision(tia_laze, FLAME[i].get())&&FLAME[i].exist)
                    {
                        gold_number++;
                        if(gold_number == 100) gold_number=0;
                        GOLD[gold_number].change(FLAME[i].x,FLAME[i].y);
                        FLAME[i].reset(i);
                        FLAME[i].exist=0;
                    }
                }

            }
            for(int i=0; i<=7; i++)
            {
                if(FLAME[i].exist)   if(checkCollision(hitbox,FLAME[i].get()))
                    {

                        Mix_PlayChannel(-1,LoseSound,0);
                        blood -= 1;
                        if (blood < 0) Died=1,blood=246;
                    }
            }
            if(checkCollision(A.get(),hitbox))
            {
                Mix_PlayChannel(-1,LoseSound,0);
                blood -= 15;
                if (blood < 0) Died=1,blood=246;
            }
            if(checkCollision(Dirt.get(),hitbox))
            {
                blood-=10;
                if (blood < 0) Died=1,blood=246;
                Mix_PlayChannel(-1,LoseSound,0);
            }
            for(int i=1; i<=3; i++)
            {
                if(wizard.get_attack(i))
                {
                    FIRE[i].move();
                    FIRE[i].render(i);
                }
            }
            BOSS.bot();
            BOSS2.bot();
            BOSS3.bot();
            if(B.exist)
            {
                B.render();
                B.move();

                if(checkCollision(B.get(),hitbox))
                {
                    Mix_PlayChannel(-1,LoseSound,0);
                    blood-=10;
                    if (blood < 0) Died=1,blood=246;
                }
            }
            else if(!has_boss)
            {
                B.time++;
                if(B.time>100)
                {
                    B.time=0;
                    B.exist=1;
                }
            }
            for(int i=1; i<=wizard.get_ammo(); i++)    Ammo.render(10+(i-1)*70,55);
            if(wizard.get_cooldownR()>=100)     ULTI.render(10+3*70,55);
            reload++;
            if(reload>500)       wizard.add_ammo(),reload=0,CurrentBackground^=1;
            RenderText(ScoreStr,(int)Score,550,20,!CurrentBackground?Black:White);
            scrollingOffset-=ScrollSpeed;
            if( scrollingOffset <- Background_Texture[CurrentBackground].getWidth()+1)    scrollingOffset = 0;
        }
        if(PauseGame||Died)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Background_Texture[CurrentBackground].render( scrollingOffset, 0 );
            Background_Texture[CurrentBackground].render( scrollingOffset + Background_Texture[CurrentBackground].getWidth(), 0 );
            Home.RePos(630,400);
            Da1.render(CurrentBackground);
            Da2.render(CurrentBackground);
            if(PauseGame)  wizard.render();
            if(BOSS2.attack)  A.render();
            Board.render(400,100);
            HighScore=max(HighScore,Score);
            if(Died)Replay.render();
            else if(PauseGame) Resume.render();
            Home.render();
            RenderText(ScoreStr,Score,550,300,Black);
            RenderText(HighScoreStr,HighScore,515,230,Black);
        }
        if(Died)
        {
            SKILL.x=100;
        }
        SDL_RenderPresent( gRenderer );
        int cur=SDL_GetTicks();
        ofstream out("luugame.txt", ofstream::out | ofstream::trunc);
        HighScore=max(HighScore,Score);
        out << Score << " " << HighScore << " " << CurrentBackground <<" "<< Da1.x << " " << Da2.x << " " << wizard.get_ammo() <<" "<<blood << " ";
        out << wizard.activate_skill << " " << SKILL.t << " " << wizard.timeskill <<" "<<wizard.wait_timeskill;
        SDL_Delay(max((float)0.0,1000/60.0f-(cur-lastUPD)));
        lastUPD=cur;
        //////
    }
    close();
    return 0;
}
