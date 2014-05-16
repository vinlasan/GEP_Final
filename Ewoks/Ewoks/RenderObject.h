#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "EngineObject.h"
#include "ResourceManager.h"
#include "RenderResource.h"
#include "SDL.h"

class RenderManager;

class RenderObject : public EngineObject
{
private:

protected:

public:
	//Render Resource?
	RenderResource* renderResource;

	SDL_Rect m_RenderRect;
	float m_PosX;
	float m_PosY;
	bool m_bVisible;
	SDL_Color m_ColorKey;
	bool m_ColorKeyEnabled;

	RenderObject();
	void setResourceObject(RenderResource* res);
	void setColorKey(unsigned int r, unsigned intg, unsigned intb);
	virtual void update() { };
	
};


#endif