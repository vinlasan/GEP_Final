#include "stdafx.h"
#include "RenderManager.h"
#include "RenderResource.h"
#include "SceneManager.h"	

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

bool RenderManager::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// check for messages
		switch (event.type)
		{
			// exit if the window is closed
		case SDL_QUIT:
			return false;

		case SDL_WINDOWEVENT:

			SDL_GetWindowSize(this->m_Window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
			break;

		} // end switch
	} // end of message processing

	// clear screen
	// SDL_RenderClear(m_Renderer);


	renderScene();

	//Call frame listeners
	renderAllObjects();


	return true;
}

void RenderManager:: logSDLError(ostream &os, const string &msg)
{
	os << msg << " error: " << SDL_GetError() << endl;
}

void RenderManager::renderScene()
{
	if (!m_SceneManager)
		return;


	for (auto* Layer : m_SceneManager->m_Layers)
	{
		/*if (Layer->m_Name == "layer2")*/

		if (!Layer->m_Visible)
			continue;

		for (auto* Object : Layer->m_SceneObjects)
		{
			if (Object->m_bVisible)
			{
				Object->update();
				SDL_Rect Pos;

				Pos.x = int(Layer->m_PosX) + int(Object->m_PosX);
				Pos.y = int(Layer->m_PosY) + int(Object->m_PosY);
				Pos.w = int(Object->m_RenderRect.w);
				Pos.h = int(Object->m_RenderRect.h);
				(Object->m_PosX) = Layer->m_PosX;
				Object->m_PosY = Layer->m_PosY;
				Object->m_RenderRect.y = Object->m_PosY;
				Object->m_RenderRect.x = Object->m_PosX;

				renderTexture(Object->renderResource->m_Texture, this->m_Renderer, Object->m_PosX,
					Object->m_PosY);
				SDL_RenderCopy(this->m_Renderer, Object->renderResource ->m_Texture,
					&Object->m_RenderRect, &Pos);
			}

		}
	}
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
	//std::list<cSDLRenderObject*>::iterator list_it;

	//Hard coded values
	const int x_increment = 5;
	static int xpos = 0;
	static int ypos = 0;
	// Render all assoicated render objects
	for (auto &list_it : m_RenderObjects)
	{
		// HIghly ineffiecnet
		/*for (auto *s : this->m_SceneManager->m_Layers)
		for (auto *so : s->m_SceneObjects)
		if (so->m_RenderResource == list_it->m_RenderResource)
		curScene = so;*/

		// Highly efficent
		//curScene = list_it->GetCurrentScene();

		if (list_it->m_bVisible)
		{
			list_it->update();

			SDL_Rect Pos = list_it->m_RenderRect;
			Pos.x = list_it->m_PosX;
			Pos.y = list_it->m_PosY;

			std::cout << Pos.x;
			SDL_RenderCopy(this->m_Renderer, list_it->renderResource->m_Texture , &(list_it->m_RenderRect), &Pos);

			/*if (list_it->m_RenderResource->m_FileName == "spaceship.bmp")
			{
			xpos += x_increment;
			if (xpos + Pos.w > 640 + Pos.w)
			xpos = -200;
			}*/
		}
	}

	SDL_RenderPresent(this->m_Renderer);
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