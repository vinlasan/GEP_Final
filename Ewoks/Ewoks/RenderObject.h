#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

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

class RenderObject : public EngineObject
{
private:

protected:

public:
	//Render Resource?

	SDL_Rect m_RenderRect;
	float m_PosX;
	float m_PosY;
	bool m_bVisible;
	SDL_Color m_ColorKey;


	RenderObject();
	void setResourceObject();
	void setColorKey(unsigned int r, unsigned intg, unsigned intb);
	virtual void update() {};
};


#endif