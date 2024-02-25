#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>
const int Dai=559;
const int Rong=689;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int PosX,PosY;
const int Acceleration=30;
const int gravity=10;
const int FPS=60;
class LTexture
{
private:
    SDL_Texture *mTexture;
    int mWidth;
    int mHeight;
public:
    LTexture()
    {
        mTexture=NULL;
        mWidth=0;
        mHeight=0;
    }
    void free()
    {
        if(mTexture!=NULL)
        {
            SDL_DestroyTexture(mTexture);
            mTexture=NULL;
            mWidth=mHeight=0;
        }
    }
    void render(int x,int y)
    {
        SDL_Rect tmp= {x,y,mWidth,mHeight};
        SDL_RenderCopy(gRenderer,mTexture,NULL,&tmp);
    }
    int getWidth()
    {
        return mWidth;
    }
    int getHeight()
    {
        return mHeight;
    }
    bool LoadImage(string file_path)
    {
        free();
        SDL_Surface* Sur=IMG_Load(file_path.c_str());
        if(Sur==NULL)   return 0;

        SDL_SetColorKey( Sur, SDL_TRUE, SDL_MapRGB( Sur->format, 239, 228, 176 ) );
        SDL_Texture *newTexture=SDL_CreateTextureFromSurface(gRenderer,Sur);
        if(newTexture==NULL) return 0;
        mWidth=Sur->w;
        mHeight=Sur->h;
        mTexture=newTexture;
        return (mTexture!=NULL);
    }
};
LTexture Character_Texture;
LTexture Background_Texture;
bool init()
{
    if(SDL_Init(SDL_INIT_EVERYTHING)!=0)   cout<<"Can't init"<<endl;
    gWindow = SDL_CreateWindow( "DoodleJump", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Dai, Rong, SDL_WINDOW_SHOWN );
    if(gWindow==NULL)    return 0;
    gRenderer=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
    if(gRenderer==NULL)   return 0;
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        return 0;
    }
    return 1;
}
void close()
{
    //Free loaded images
    Character_Texture.free();
    Background_Texture.free();
    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}
int main(int argc,char * argv[])
{
    if(!init())
    {
        cout<<"Can't init"<<endl;
        return 0;
    }
    PosX=250;
    PosY=250;
    if(!Character_Texture.LoadImage("character.png"))
    {
        cout<<"Q1";
        return 0;
    }
    if(!Background_Texture.LoadImage("background.png"))
    {
        cout<<"Q2";
        return 0;
    }
    ///////////////////
    SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
    SDL_RenderClear(gRenderer);
    SDL_Event  EV;
    bool running=1;
    int lastUpd=0;
    while(running)
    {
        bool moveL=0,moveR=0;
        while(SDL_PollEvent(&EV))
        {
            if(EV.type==SDL_QUIT)
            {
                running=0;
                break;
            }
            else if(EV.type=SDL_KEYDOWN)
            {
                if(EV.key.keysym.sym==SDLK_LEFT) moveL=1;
                if(EV.key.keysym.sym==SDLK_RIGHT) moveR=1;
            }

            Uint32 cur=SDL_GetTicks();
            float dT = (cur - lastUpd) / 1000.0f;
            int framesToUpdate = floor(dT / (1.0f / FPS));
            if (framesToUpdate > 0)
            {


                SDL_RenderClear(gRenderer);
                Background_Texture.render(0,0);
                Character_Texture.render(PosX,PosY);
                SDL_RenderPresent( gRenderer );
            }
            lastUpd=cur;


            //SDL_Delay(1000.0/60);
        }
    }

    close();
    return 0;
}
