#include "stdafx.h"
#include "RenderManager.h"
#include "RenderObject.h"
#include "Telegram.h"

RenderObject::RenderObject()
{
	renderResource = NULL;
	m_PosX = m_PosY = 0.0f;
	m_bVisible = true;
	ZeroMemory(&m_RenderRect, sizeof(SDL_Rect));
	ZeroMemory(&m_ColorKey, sizeof(SDL_Color));
	m_ColorKeyEnabled = false;
}

void RenderObject::setResourceObject(RenderResource* res)
{
	if (res)
	{
		renderResource = res;

		renderResource->m_Renderer = RenderManager::GetRenderManager()->m_Renderer;
		ResourceManager::GetResourceManager()->setCurrentScope(0);

		int w, h;
		SDL_QueryTexture(renderResource->m_Texture, NULL, NULL, &w, &h);

		m_RenderRect.w = w;
		m_RenderRect.h = h;

		if (m_ColorKeyEnabled)
			setColorKey(m_ColorKey.r, m_ColorKey.g, m_ColorKey.b);
	}
}

void RenderObject::setColorKey(unsigned int r, unsigned int g, unsigned int b)
{
	m_ColorKey.r = r;
	m_ColorKey.g = g;
	m_ColorKey.b = b;


	SDL_Window* window = RenderManager::GetRenderManager()->m_Window;
	SDL_Surface* surface = SDL_GetWindowSurface(window);

	Uint32 colorkey = SDL_MapRGB(surface->format, m_ColorKey.r, m_ColorKey.g, m_ColorKey.b);
	int success = SDL_SetColorKey(surface, -1, colorkey);
	std::cout << "success value: " << success << "\n";
}

void RenderObject::HandleMessage(Telegram *telegram)
{
	m_PosX += telegram->Value;
	std::cout << "I printe";
}