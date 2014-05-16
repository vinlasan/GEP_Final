#ifndef SDL2DSCENEMANAGER_H_INCLUDED
#define SDL2DSCENEMANAGER_H_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <Windows.h>
#include <math.h>
#include "tinyxml2.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "EngineObject.h"
#include "RenderResource.h"
#include "RenderObject.h"

using namespace tinyxml2;

typedef enum { SE_TIMER_EXPIRED = 0 }SCENE_EVENT_TYPE;

class sSceneManager;

class sSceneListener
{
public:
	SCENE_EVENT_TYPE m_ListenFor;

	virtual void Event(sSceneManager* Manager, void* customData) const = 0;
	void InputEvent(std::string* InputMessage);
};

class sTimer
{
private:
protected:
public:

	unsigned int m_ID;
	DWORD m_StartTime;
	DWORD m_Interval;
	bool m_Expired;
	sTimer();
	void start();
	void update();
	
};

class sSceneObject : public RenderObject
{
private:
protected:
public:
	float m_PosX, m_PosY;
	SDL_Rect m_RenderRect;
	SDL_Color m_ColorKey;
	bool m_bColorKeyEnabled;
	RenderResource *m_RenderResource;
	bool m_bVisible;
	void update();
	
};

class stwoDLayer : public EngineObject 
{
public:
	stwoDLayer();
	bool m_Visible;
	unsigned int m_ZOrder;
	float m_PosX, m_PosY;
	std::string m_Name;
	std::list<sSceneObject*> m_SceneObjects;
	void update();
	
};

class sSceneManager
{
protected:
	void addLayerObjects(stwoDLayer *Layer, XMLElement *Element);
	void checkTimerExpired();
public:
	std::list<stwoDLayer*> m_Layers;
	std::list<sTimer*> m_Timers;
	std::list<sSceneListener*> m_Listeners;

	stwoDLayer* addLayer(std::string Name);
	stwoDLayer* findLayer(std::string Name);
	void removeLayer(std::string Name);
	void sortLayers();

	bool loadFromXMLFile(std::string Filename);

	void addTimer(unsigned int ID, DWORD Interval);
	void addListener(sSceneListener* Object);

	bool checkCollision(SDL_Rect* A, SDL_Rect* B);

	void update();
};

#endif // 2DSDLSCENEMANAGER_H_INCLUDED
