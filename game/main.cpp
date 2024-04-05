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
    for(int i=1; i<=4; i++)    Ammo[i].free();
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
    if(!init())
    {
        cout<<"Can't init"<<endl;
        return 0;
    }
    LoadTexture();
    CucDa Da1(Width+20);
    CucDa Da2(Width+400);
    coin COIN;
    Died=0;
    Play.reconstruct(1,450,293,300,75);
    LoadGame.reconstruct(4,450,393,300,75);
    Tutorial.reconstruct(8,453,493,300,75);
    Exit.reconstruct(0,450,593,300,75);
    Pause.reconstruct(3,1200-60,10,50,50);
    Resume.reconstruct(6,570,400,50,50);
    Replay.reconstruct(7,570,400,50,50);
    Home.reconstruct(9,1200-60,10,50,50);
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,36,121,126,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    Mix_PlayMusic(GameMusic,-1);
    while(running)
    {

        //cout<<PauseGame<<endl;
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                return 0;
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
        if(Rep)
        {
            Score=0;
            VaoGame=1;
            ScrollSpeed=5;
            scrollingOffset=5;
            BOSS2.attack=0;
            Da1.reset(Width+20),Da2.reset(Width+400);
            wizard.reset();
            GRAVITY=18;
            Rep=0;
            reload=0;
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
            Da2.move();
            Da1.move();
            wizard.move();
            COIN.move();
            Background_Texture[CurrentBackground].render( scrollingOffset, 0 );
            Background_Texture[CurrentBackground].render( scrollingOffset + Background_Texture[CurrentBackground].getWidth(), 0 );

            Da1.render(CurrentBackground);
            Da2.render(CurrentBackground);
            wizard.render();
            Pause.render();
            COIN.render();
            SDL_Rect hitbox= {258,wizard.getY(),1,110};
              bool has_boss=(BOSS.HP>0)||(BOSS2.HP>0);
            if(!has_boss)  No_Boss_Time++;
            if(No_Boss_Time>=150)
            {
                No_Boss_Time=0;
                int t=rnd(1,3);
                if(t==1)  BOSS.heal();
                if(t==2)  BOSS2.heal();
                //if(t==1)  BOSS.heal();
            }
            if(BOSS2.attack)
            {
                A.move();
                A.render();
            }
            if(checkCollision(hitbox,Da1.get())||checkCollision(hitbox,Da2.get()))
            {
                //Mix_PlayChannel(-1,LoseSound,0);
                //Died=1;
            }
            if(checkCollision(hitbox,COIN.get()))
            {

                Score+=COIN.score;
                Mix_PlayChannel(-1,GainSound,0);
                COIN.reset();
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
            for(int i=1; i<=wizard.get_ammo(); i++)    Ammo[i].render(10+(i-1)*70,10);
            reload++;
            if(reload>500)       wizard.add_ammo(),reload=0,CurrentBackground^=1;
            RenderText(ScoreStr,(int)Score,550,20,!CurrentBackground?Black:White);

            scrollingOffset-=ScrollSpeed;
            if( scrollingOffset <- Background_Texture[CurrentBackground].getWidth() )    scrollingOffset = 0;
            if(ScrollSpeed>12)   ScrollSpeed=16;
        }
        if(PauseGame||Died)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Background_Texture[CurrentBackground].render( scrollingOffset, 0 );
            Background_Texture[CurrentBackground].render( scrollingOffset + Background_Texture[CurrentBackground].getWidth()-1, 0 );
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
            RenderText(ScoreStr,Score,545,300,Black);
            RenderText(HighScoreStr,HighScore,520,230,Black);
        }
        SDL_RenderPresent( gRenderer );
        SDL_Delay(1000/60.0f);
        //////
    }
    close();
    return 0;
}
