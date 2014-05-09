#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "SDL.h"

class RenderObject
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