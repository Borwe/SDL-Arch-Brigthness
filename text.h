#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <string>

using namespace std;


void show_text(SDL_Texture *text,SDL_Rect *rect,SDL_Renderer *rendr){
	rect->x=(640-rect->w)/2;
	SDL_RenderCopy(rendr,text,NULL,rect);
}

class Text{
public:
	Text(string s,TTF_Font *font,SDL_Renderer *rendr){
        gFont=font;
        gRender=rendr;
        if(gRender==NULL || font==NULL){
			cout<<"Failed to create gRender:\n"<<endl;
			return;
        }
        SDL_Surface *temp=NULL;
        SDL_Color color={0,0,0,255};
        temp=TTF_RenderText_Solid(gFont,s.c_str(),color);
        if(temp==NULL){
			cout<<"Failed to create temp:\n"<<TTF_GetError()<<endl;
        }else{
        	text=SDL_CreateTextureFromSurface(gRender,temp);
			text_Rect.w=temp->w;
			text_Rect.h=temp->h;
			SDL_FreeSurface(temp);
			temp=NULL;
			cout<<"Created text object"<<endl;
        }
	}

	void changeText(string x){
		SDL_DestroyTexture(text);
		text=NULL;

		SDL_Color color={0,0,0,255};

		if(gFont==NULL){
			cout<<"Failed gFont:"<<endl;
		}

		cout<<x<<endl;

		SDL_Surface *temp=NULL;
        temp=TTF_RenderText_Solid(gFont,x.c_str(),color);
        if(temp!=NULL){
			text=SDL_CreateTextureFromSurface(gRender,temp);
			text_Rect.w=temp->w;
			text_Rect.h=temp->h;
			SDL_FreeSurface(temp);
			temp=NULL;
			cout<<"Changed text"<<endl;
        }else{
			cout<<"Failed to change text"<<endl;
        }
	}
	void render(int x=0,int y=0){
        text_Rect.x=x;
        text_Rect.y=y;

        show_text(text,getRect(),gRender);
	}

	SDL_Rect *getRect(){
		return &text_Rect;
	}

	SDL_Texture *getText(){
		return text;
	}

	~Text(){
		SDL_DestroyTexture(text);
	}
protected:
	string show;
	TTF_Font *gFont;
    SDL_Texture *text;
    SDL_Rect text_Rect;
    SDL_Renderer *gRender;
};

#endif // TEXT_H_INCLUDED
