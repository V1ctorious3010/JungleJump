#include<bits/stdc++.h>
using namespace std;
#include<SDL.h>
#include<SDL_image.h>


const int Dai=600;
const int Rong=800;
SDL_Window *gWindow;
SDL_Renderer *gRenderer;
int PosX,PosY;
const int Acceleration=30;
const int gravity=10;
const int FPS=60;

