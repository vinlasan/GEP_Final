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

using namespace tinyxml2;

typedef enum { SE_TIMER_EXPIRED = 0 }SCENE_EVENT_TYPE;

class sSceneManager;

class sSceneListener
{
public:
	SCENE_EVENT_TYPE m_ListenFor;

	virtual void Event(sSceneManager* Manager, void* customData) const = 0;
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

	sTimer()
	{
		m_ID = 0;
		m_StartTime = 0;
		m_Interval = 0;
		m_Expired = false;
	}

	void start()
	{
		m_StartTime = timeGetTime();
		m_Expired = false;
	}

	void update()
	{
		if (m_Expired)
			return;
		DWORD ElapsedTime = timeGetTime() - m_StartTime;

		if (ElapsedTime >= m_Interval)
		{
			m_Expired = true;
		}
	}
};

class sSceneObject
{
private:
protected:
public:
};

class stwoDLayer
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

	void update();
};

#endif // 2DSDLSCENEMANAGER_H_INCLUDED
