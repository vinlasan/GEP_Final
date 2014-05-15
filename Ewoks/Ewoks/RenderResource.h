#ifndef RENDERRESOURCE_H
#define RENDERRESOURCE_H

#include "EngineObject.h"
#include "ResourceManager.h"
#include "SDL.h"

class RenderResource : public Resource
{
public:
	SDL_Texture* m_Texture;
	SDL_Renderer* m_Renderer;

	RenderResource();
	~RenderResource();
	void load();
	void unload();

protected:

private:


};
#endif