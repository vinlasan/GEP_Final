#include "stdafx.h"
#include "RenderManager.h"
#include "RenderResource.h"

RenderManager RenderManager::m_RenderManager;

RenderResource::RenderResource() : Resource()
{
	m_Texture = NULL;
}

RenderResource::~RenderResource()
{
	unload();
}

void RenderResource::load()
{
	unload();

	SDL_Renderer* curRend = RenderManager::GetRenderManager()->m_Renderer;

	m_Texture = IMG_LoadTexture(RenderManager::GetRenderManager()->m_Renderer, m_FileName.c_str());

	m_bLoaded = true;
}

void RenderResource::unload()
{
	if(m_Texture)
	{
		SDL_DestroyTexture(m_Texture);
		m_Texture = NULL;
	}

	m_bLoaded = false;
}

RenderManager::RenderManager()
{
	this->SCREEN_WIDTH = 640;
	this->SCREEN_HEIGHT = 480;
}

RenderManager::~RenderManager()
{
}

bool RenderManager::Initialize()
{

	//Error
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(cout, "SDL_Init"); 
		return false;
	}
	

	//Window
	m_Window = SDL_CreateWindow("window", 100, 100, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_Window == nullptr)
	{
		logSDLError(cout, "CreateWindow");
		return false;
	}
	

	//Renderer
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == nullptr)
	{
		logSDLError(cout, "CreateRenderer");
		return false;
	}

	SDL_GetWindowWMInfo(m_Window, &m_inf);

	m_WindowHandle = m_inf.info.win.window;
	

	return true;
	/*SDL_RenderClear(ren);*/

}

void RenderManager:: logSDLError(ostream &os, const string &msg)
{
	os << msg << " error: " << SDL_GetError() << endl;
}


SDL_Texture* RenderManager :: loadTexture(const string &file)
{
	SDL_Texture *texture = nullptr;

	//load image
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	//convert to tecture and return the texture
	if (loadedImage != nullptr)
	{
		texture = SDL_CreateTextureFromSurface(m_Renderer, loadedImage);
		SDL_FreeSurface(loadedImage);

		//make sure converting success
		if (texture == nullptr)
			logSDLError(cout, "CreateTextureFromSurface");
	}
	else
		logSDLError(cout, "LoadBMP");

	return texture;
}

Resource* RenderManager::loadFromXML(tinyxml2::XMLElement *Element)
{
	if (Element)
	{
		Resource* Resource = new RenderResource();

		for (tinyxml2::XMLAttribute* ElementAttrib = const_cast<tinyxml2::XMLAttribute*>(Element->FirstAttribute());
			ElementAttrib; ElementAttrib = const_cast<tinyxml2::XMLAttribute*>(ElementAttrib->Next()))
		{
			std::string AttribName = ElementAttrib->Name();
			std::string AttribValue = ElementAttrib->Value();

			if (AttribName == "UID")
			{
				Resource->m_ResourceID = atoi(AttribValue.c_str());
			}

			if (AttribName == "filename")
			{
				Resource->m_FileName = AttribValue;
			}

			if (AttribName == "scenescope")
			{
				Resource->m_Scope = atoi(AttribValue.c_str());
			}
		}

		return Resource;
	}

	return NULL;

}

void RenderManager :: renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y)
{
	//setup the destination rectangle position
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	//Query texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(ren, tex, NULL, &pos);
}

void RenderManager :: renderAllObjects()
{
	SDL_RenderPresent(m_Renderer);
	SDL_Delay(3000);
}

void RenderManager :: clean()
{
	//SDL_DestroyTexture("fileName");
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

RenderManager* RenderManager::GetRenderManager()
{
	return &m_RenderManager;
}

HWND RenderManager::GetWindowHandle()
{
	return m_WindowHandle;
}