#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "EngineObject.h"
#include "ResourceManager.h"
#include "SDL.h"

class RenderManager;

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
	virtual void HandleMessage(Telegram *telegram);
};


#endif