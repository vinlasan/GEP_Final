#include "RenderManager.h"

Render::Render(){
	this->SCREEN_WIDTH = 640;
	this->SCREEN_HEIGHT = 480;
}

Render::~Render(){
}

bool Render::Initialize(){

	//Error
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(cout, "SDL_Init"); 
		return false;
	}
	

	//Window
	win = SDL_CreateWindow("window", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		logSDLError(cout, "CreateWindow");
		return false;
	}
	

	//Renderer
	ren = SDL_CreateRenderer(win, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		logSDLError(cout, "CreateRenderer");
		return false;
	}
	

	return true;
	/*SDL_RenderClear(ren);*/

}

void Render:: logSDLError(ostream &os, const string &msg){
	os << msg << " error: " << SDL_GetError() << endl;
}


SDL_Texture* Render :: loadTexture(const string &file, SDL_Renderer *ren){
	SDL_Texture *texture = nullptr;
	//load image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
	//convert to tecture and return the texture
	if (loadedImage != nullptr){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//make sure converting success
		if (texture == nullptr)
			logSDLError(cout, "CreateTextureFromSurface");
	}
	else
		logSDLError(cout, "LoadBMP");

	return texture;
}

void Render :: renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y){
	//setup the destination rectangle position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	//Query texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(ren, tex, NULL, &pos);
}

void Render :: renderAllObjects(){

	

	


	
	SDL_RenderPresent(ren);
	SDL_Delay(3000);
}

void Render :: clean(){
	//SDL_DestroyTexture("fileName");
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}