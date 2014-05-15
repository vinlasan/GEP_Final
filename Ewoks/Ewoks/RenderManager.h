#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_syswm.h>
#include <windows.h>
#include <tinyxml2.h>
#include "ResourceManager.h"

using namespace std;

class RenderManager{
public:
	int SCREEN_WIDTH ;
	int SCREEN_HEIGHT;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	string filenNme;

	RenderManager();
	~RenderManager();

	bool Initialize();

	static RenderManager* GetRenderManager();

	//Error Logger
	void logSDLError(ostream &os, const string &msg);

	//window
	/*SDL_Window* SDL_CreateWindow(const char* title, int x, int y, const int SCREEN_WIDTH, 
		int h, Uint32 flags);*/

	//Load Texture
	SDL_Texture* loadTexture(const string &file);

	//Render Texture
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y);

	void renderAllObjects();

	void clean();

	HWND GetWindowHandle();

	Resource* loadFromXML(tinyxml2::XMLElement *Element);

protected:
	static RenderManager m_RenderManager;
	HWND m_WindowHandle;
	SDL_SysWMinfo m_inf;

	//std::list<RenderObject*> m_RenderObjects;


};