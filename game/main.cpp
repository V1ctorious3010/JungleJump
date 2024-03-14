#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>
#include"global.h"
#include"LTexture.h"
#include<SDL_ttf.h>
int reload=0;
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)   cout<<"Can't init"<<endl;
    gWindow = SDL_CreateWindow( "Game_nhay_nhay", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN );
    if(gWindow==NULL)    return 0;
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(gRenderer==NULL)   return 0;
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }
    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return 0;
    }
    gFont = TTF_OpenFont( "dot_to_dot.ttf", 50);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        return 0;
    }
    return 1;
}
void close()
{
    //Free loaded images
    Character_Texture.free();
    Background_Texture.free();
    bullet.free();
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
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,36,121,126,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    Button Play= {1,500,400,300,75};
    Button Exit= {0,500,600,300,75};
    Button Pause= {3,Width-60,10,50,50};
    Button LoadGame= {4,500,500,300,75};
    Button Menu={5,500,400,300,75};
    while(running)
    {
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                return 0;
            }
            if(!VaoGame)
            {
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                MenuBackground.render(0,0);
                Play.render();
                Play.HandleEvent(EV);
                Exit.render();
                Exit.HandleEvent(EV);
                LoadGame.render();
                LoadGame.HandleEvent(EV);
            }
            else
            {
                wizard.handleEvent(EV);
                Pause.HandleEvent(EV);
            }
        }
        if(VaoGame&&!PauseGame)
        {
            Pause.RePos(Width-60,10);
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            scrollingOffset-=ScrollSpeed;
            if( scrollingOffset <- Background_Texture.getWidth() )    scrollingOffset = 0;
            wizard.move();
            ////////////////////////
            Background_Texture.render( scrollingOffset, 0 );
            Background_Texture.render( scrollingOffset + Background_Texture.getWidth()-3, 0 );
            wizard.render();
            Pause.render();
            Da1.render();
            Da2.render();
            SDL_Rect hitbox= {230,wizard.getY(),1,110};
            if(!bullet_on_screen)
            {
                int n=rnd(1,1000);
                if(n>995)     A.reset(),bullet_on_screen=1;
            }
            if(bullet_on_screen)
            {
                A.move();
                A.render();
                if(checkCollision(hitbox,A.get()))
                {
                    //  return 0;
                }
                if(A.x<0)   bullet_on_screen=0;
            }
            Da1.move();
            Da2.move();
            if(checkCollision(hitbox,Da1.get())||checkCollision(hitbox,Da2.get()))
            {
                // return 0;
            }
            if(wizard.get_attack())
            {
                FIRE.move();
                FIRE.render();
                if(bullet_on_screen&&checkCollision(FIRE.get(),A.get()))
                {
                    A.reset(),bullet_on_screen=0;
                    wizard.cooldown();
                    Score+=100;
                }
            }
            for(int i=1; i<=wizard.get_ammo(); i++)    Ammo[i].render(10+(i-1)*70,10);
            ////////
            //hien thi diem
            string tmp="Score: ";
            Score++;
            tmp+=to_string(Score);
            SDL_Color textColor = {0,0,0};
            if(!ScoreText.loadFromRenderedText(tmp,textColor))
            {
                printf( "Failed to render text texture!\n");
            }
            ScoreText.render(550,20);
            //////////
            SDL_Delay(1000/60.0f);
            ////tang toc do game
            int cur=SDL_GetTicks();
            if(cur%300==0)      ScrollSpeed++;
            reload++;
            if(reload>500) wizard.add_ammo(),reload=0;
            if(ScrollSpeed>16)   ScrollSpeed=16;
        }
        if(PauseGame)
        {
            Pause.RePos(500,600);
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(gRenderer);
            Background_Texture.render( scrollingOffset, 0 );
            Background_Texture.render( scrollingOffset + Background_Texture.getWidth()-3, 0 );
            wizard.render();
            Da1.render();
            Da2.render();
            if(bullet_on_screen)  A.render();

            Pause.render();

        }
        SDL_RenderPresent( gRenderer );
        //////
    }
    close();
    return 0;
}
