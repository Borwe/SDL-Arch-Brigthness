#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "text.h"
#include <string>
#include <cstdlib>

using namespace std;

TTF_Font *font;
SDL_Window *window;
SDL_Renderer *render;

bool init_font(){
    bool success=true;

    if(TTF_Init()<0){
        cout<<"Failed to TTF_init:\n"<<TTF_GetError()<<endl;
        success=false;
    }else{
        font=TTF_OpenFont("merry.ttf",30);
        if(font==NULL){
            cout<<"failed to load font:\n"<<TTF_GetError()<<endl;
            success=false;
        }
    }

    return success;
}

bool init(){
    bool success=true;

    if(init_font()==true){
        if(SDL_Init(SDL_INIT_VIDEO)<0){
            cout<<"Failed to SDL_init()\n"<<SDL_GetError()<<endl;
            success=false;
        }else{
            window=SDL_CreateWindow("BRIGHTNESS CONTROL",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,640,480,SDL_WINDOW_SHOWN);
            if(window==NULL){
                cout<<"Failed to get window:\n"<<SDL_GetError()<<endl;
                success=false;
            }else{
                render=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if(render==NULL){
                    cout<<"Failed to create render:\n"<<SDL_GetError()<<endl;
                    success=false;
                }
            }
        }
    }else{
        cout<<"Failed at init_font:\n"<<endl;
        success=false;
    }

    return success;
}

void close(){
    TTF_CloseFont(font);
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);

    font=NULL;
    render=NULL;
    window=NULL;

    TTF_Quit();
    SDL_Quit();
}

void brightness_cmd(string amnt){
    if(amnt=="[Enter only Numbers]"){
        cout<<"Can't change text"<<endl;
    }else{
        string todo="xbacklight -set "+amnt;
        system(todo.c_str());
    }
}

void do_shit(){
    SDL_Event e;
    bool quit=false;

    //Top text
    Text top("ENTER BRIGHTNESS LEVEL BELLOW",font,render);

    //Input text
    Text input("[Enter only Numbers]",font,render);
    string in="";

    //scape text
    Text space("PRESS [SPACE] TO APPLY BRIGHTNESS",font,render);

    while(quit==false){
        while(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT){
                quit=true;
                close();
            }

            if(e.type==SDL_KEYUP){
                if(in=="[Enter only Numbers]"){
                    in="";
                }
                switch(e.key.keysym.sym){
                    case SDLK_0: in=in+"0";break;
                    case SDLK_1: in=in+"1";break;
                    case SDLK_2: in=in+"2";break;
                    case SDLK_3: in=in+"3";break;
                    case SDLK_4: in=in+"4";break;
                    case SDLK_5: in=in+"5";break;
                    case SDLK_6: in=in+"6";break;
                    case SDLK_7: in=in+"7";break;
                    case SDLK_8: in=in+"8";break;
                    case SDLK_9: in=in+"9";break;
                    case SDLK_BACKSPACE: if(in.size()>0)in.pop_back();
                        break;
                    case SDLK_SPACE: brightness_cmd(in);
                }
                if(in.size()==0){
                    in="[Enter only Numbers]";
                }
                input.changeText(in);
            }
        }

        SDL_SetRenderDrawColor(render,255,255,255,255);
        SDL_RenderClear(render);

        top.render();
        input.render(0,top.getRect()->h+20);
        space.render(0,input.getRect()->y+input.getRect()->h+20);

        SDL_RenderPresent(render);
    }
}


int main(int argc,char **argv){
    if(init()){
        do_shit();
    }
    return 0;
}
