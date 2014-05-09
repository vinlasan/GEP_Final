#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_syswm.h>
#include <windows.h>

using namespace std;

class Render{
public:
	int SCREEN_WIDTH ;
	int SCREEN_HEIGHT;
	SDL_Window *win;
	SDL_Renderer *ren;
	string filenNme;

	Render();
	~Render();

	bool Initialize();

	static Render* GetRenderManager();

	//Error Logger
	void logSDLError(ostream &os, const string &msg);

	//window
	/*SDL_Window* SDL_CreateWindow(const char* title, int x, int y, const int SCREEN_WIDTH, 
		int h, Uint32 flags);*/

	//Load Texture
	SDL_Texture* loadTexture(const string &file, SDL_Renderer *ren);

	//Render Texture
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

	void renderAllObjects();

	void clean();

	HWND GetWindowHandle();

protected:
	static Render m_RenderManager;
	HWND m_WindowHandle;
	SDL_SysWMinfo m_inf;

	//std::list<RenderObject*> m_RenderObjects;


};