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

void RenderText(string &s,int score,int x,int y)
{
    string tmp=s;
    tmp+=to_string(score);
    SDL_Color textColor;
    if (CurrentBackground == 0) textColor = {0,0,0};
    else textColor = {255,255,255};
    if(!ScoreText.loadFromRenderedText(tmp,textColor))
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
    for(int j=0; j<=1; j++)   bullet[j].free();
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
    ifstream in;
    in.open("luugame.txt");
    int so_lg_dan, x_Da1, x_Da2;
    in >> Score >> HighScore >> CurrentBackground >> x_Da1 >> x_Da2 >> so_lg_dan;
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
    Died=0;
    Play.reconstruct(1,450,293,300,75);
    LoadGame.reconstruct(4,450,393,300,75);
    Tutorial.reconstruct(8,450,493,300,75);
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
//                in.close();
//                out.close();
                running = 0;
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
            bullet_on_screen=0;
            GRAVITY=18;
            Choitiep=0;
            reload=0;
        }
        if(Rep)
        {
            Score=0;
            CurrentBackground = 0;
            VaoGame=1;
            ScrollSpeed=5;
            scrollingOffset=5;
            bullet_on_screen=0;
            Da1.reset(Width+20),Da2.reset(Width+400);
            wizard.reset();
            wizard.update_ammo(3);
            GRAVITY=18;
            Rep=0;
            reload=0;
        }
        if(ShowMenu)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            MenuBackground.render(0,0);
            Title.render(190,50);
            Play.render();
            Tutorial.render();
            Exit.render();
            LoadGame.render();
//            SDL_Rect fillRect = { 0, 0, 1200, 740 };
//            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
//            SDL_RenderFillRect( gRenderer, &fillRect );
//            SDL_RenderPresent( gRenderer );
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
            if(!bullet_on_screen)
            {
                int n=rnd(1,1000);
                if(n>998)     A.reset(),bullet_on_screen=1;
            }
            if(bullet_on_screen)
            {
                A.move();
                A.render();
                if(checkCollision(hitbox,A.get()))
                {
                    //Mix_PlayChannel(-1,LoseSound,0);
                    //  Died=1;
                }
                if(A.x<0)   bullet_on_screen=0;
            }
            if(checkCollision(hitbox,Da1.get())||checkCollision(hitbox,Da2.get()))
            {
                // Mix_PlayChannel(-1,LoseSound,0);
                // Died=1;
            }
            if(checkCollision(hitbox,COIN.get()))
            {

                Score+=COIN.score;
                // Mix_PlayChannel(-1,GainSound,0);
                COIN.reset();
            }
            for (int i = 1; i <= 3; i++)
            {
                if(wizard.get_attack(i))
                {
                    FIRE[i].move();
                    FIRE[i].render(i);
                    if (bullet_on_screen&&checkCollision(FIRE[i].get(),A.get()))
                    {
                        Mix_PlayChannel(-1,AttackSound,0);
                        A.reset(),bullet_on_screen=0;
                        wizard.cooldown(i);
                        Score+=100;
                    }
                }
            }
            for(int i=1; i<=wizard.get_ammo(); i++)    Ammo[i].render(10+(i-1)*70,10);
            RenderText(ScoreStr,(int)Score,550,20);
            reload++;
            if(reload>500)       wizard.add_ammo(),reload=0,CurrentBackground^=1;
            scrollingOffset-=ScrollSpeed;
            if( scrollingOffset <- Background_Texture[CurrentBackground].getWidth() )    scrollingOffset = 0;
            if(ScrollSpeed>12)   ScrollSpeed=16;
        }
        if(PauseGame||Died)
        {
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Background_Texture[CurrentBackground].render( scrollingOffset, 0 );
            Background_Texture[CurrentBackground].render( scrollingOffset + Background_Texture[CurrentBackground].getWidth()-3, 0 );
            Home.RePos(630,400);
            Da1.render(CurrentBackground);
            Da2.render(CurrentBackground);
            if(PauseGame)  wizard.render();
            if(bullet_on_screen)  A.render();
            Board.render(400,100);
            HighScore=max(HighScore,Score);
            if(Died)Replay.render();
            else if(PauseGame) Resume.render();
            Home.render();
            RenderText(ScoreStr,Score,545,300);
            RenderText(HighScoreStr,HighScore,520,230);
        }
        SDL_RenderPresent( gRenderer );
        ofstream out("luugame.txt", ofstream::out | ofstream::trunc);
        HighScore=max(HighScore,Score);
        out << Score << " " << HighScore << " " << CurrentBackground <<" "<< Da1.x << " " << Da2.x << " " << wizard.get_ammo();
        SDL_Delay(1000/60.0f);


        //////
    }
    close();
    in.close();
    out.close();
    return 0;
}
