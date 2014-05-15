#include "stdafx.h"
#include "SceneManager.h"

using namespace tinyxml2;

bool compareLayerOrder(const stwoDLayer *lhs, const stwoDLayer *rhs)
{
	return lhs->m_ZOrder < rhs->m_ZOrder;
}

void sSceneListener::InputEvent(std::string* InputMessage)
{

}

stwoDLayer::stwoDLayer()
{
	m_Visible = true;
	m_PosX = m_PosY = 0.0f;
	m_ZOrder = 0;
}

stwoDLayer* sSceneManager::addLayer(std::string Name)
{
	stwoDLayer *Layer = findLayer(Name);

	if (!Layer)
	{
		Layer = new stwoDLayer();
		Layer->m_Name = Name;
		m_Layers.push_back(Layer);
	}

	return Layer;
}

stwoDLayer* sSceneManager::findLayer(std::string Name)
{
	for (auto *list_it : m_Layers)
	{
		if (list_it->m_Name == Name)
			return list_it;
	}
	return NULL;
}

void sSceneManager::removeLayer(std::string Name)
{
	for (auto *list_it : m_Layers)
	{
		if (list_it->m_Name == Name)
			m_Layers.remove(list_it);
	}
}

void sSceneManager::addLayerObjects(stwoDLayer *Layer, XMLElement *Element)
{
	sSceneObject* Object = new sSceneObject();
	unsigned int r = 0, g = 0, b = 0;

	if (!Object)
		return;

	for (XMLAttribute* ElementAttrib =
		const_cast<XMLAttribute*>
		(Element->FirstAttribute()); ElementAttrib;
	ElementAttrib = const_cast<XMLAttribute*>(ElementAttrib->Next()))
	{
		std::string AttribName = ElementAttrib->Name();
		std::string AttribValue = ElementAttrib->Value();
		if (AttribName == "resourceID")
		{
			ResourceManager* ResourceManager = ResourceManager::GetResourceManager();
		}

		if (AttribName == "posx")
		{
			Object->m_PosX = atof(AttribValue.c_str());
		}

		if (AttribName == "posy")
		{
			Object->m_PosY = atof(AttribValue.c_str());
		}

		if (AttribName == "colorkey")
		{
			if (AttribValue == "true")
				Object->m_bColorKeyEnabled = true;
			else
				Object->m_bColorKeyEnabled = false;
		}

		if (AttribName == "r")
		{
			r = atoi(AttribValue.c_str());
		}

		if (AttribName == "g")
		{
			g = atoi(AttribValue.c_str());
		}

		if (AttribName == "b")
		{
			b = atoi(AttribValue.c_str());
		}
	}

	/*if (Object->m_bColorKeyEnabled)
		Object->setColorKey(r, g, b);*/

	Layer->m_SceneObjects.push_back(Object);
}

bool sSceneManager::checkCollision(SDL_Rect* A, SDL_Rect* B)
{
	bool isColliding;

	if (SDL_HasIntersection(A, B))
		isColliding = true;
	else isColliding = false;

	return isColliding;
}

void sSceneManager::checkTimerExpired()
{
	//Render all assoicated render objects

	for (auto* list_it : m_Timers)
	{
		list_it->update();
		if (list_it->m_Expired)
		{
			for (auto* listener_it : m_Listeners)
			{
				if (listener_it->m_ListenFor == SE_TIMER_EXPIRED)
				{
					listener_it->Event(this, NULL);
					list_it->start();
				}
			}
		}
	}

}


void sSceneManager::update()
{
	checkTimerExpired();
}

bool sSceneManager::loadFromXMLFile(std::string fileName)
{
	tinyxml2::XMLDocument doc;

	std::list<stwoDLayer*> List;

	if (doc.LoadFile(fileName.c_str()) == XML_NO_ERROR)
	{
		//Find resources node
		XMLNode* ResourceTree = doc.RootElement();

		if (ResourceTree)
		{
			//Enumerate resource objects
			for (XMLNode* child = ResourceTree->FirstChild(); child; child = child->NextSibling())
			{
				XMLElement *Element = child->ToElement();

				if (Element)
				{
					stwoDLayer *Layer = new stwoDLayer();
					Layer->m_ZOrder = m_Layers.size();

					for (XMLAttribute* ElementAttrib =
						const_cast<XMLAttribute*>(Element->FirstAttribute());
						ElementAttrib; ElementAttrib = const_cast<XMLAttribute*>(ElementAttrib->Next()))
					{
						//Examine layers
						std::string AttribName = ElementAttrib->Name();
						std::string AttribValue = ElementAttrib->Value();

						//Detect resource type. Graphic? Audio? Text?
						if (AttribName == "name")
						{
							Layer->m_Name = AttribValue;
							continue;
						}

						if (AttribName == "posx")
						{
							Layer->m_PosX = atof(AttribValue.c_str());
						}

						if (AttribName == "posy")
						{
							Layer->m_PosY = atof(AttribValue.c_str());
						}

						if (AttribName == "visible")
						{
							if (AttribValue == "true")
								Layer->m_Visible = true;
							else
								Layer->m_Visible = false;
						}
					}

					m_Layers.push_back(Layer);

					//Cycle through layer objects
					for (XMLNode* objs = child->FirstChild(); objs; objs = objs->NextSibling())
					{
						if (std::string(objs->Value()) == "objects")
						{
							for (XMLNode* obj = objs->FirstChild(); obj; obj = obj->NextSibling())
							{
								XMLElement *ObjElement = obj->ToElement();

								addLayerObjects(Layer, ObjElement);
							}
						}
					}
				}
			}

			sortLayers();
			return true;
		}
	}



	return false;
}

void sSceneManager::addTimer(unsigned int ID, DWORD Interval)
{
	sTimer *Timer = new sTimer();
	Timer->m_ID = ID;
	Timer->m_Interval = Interval;
	m_Timers.push_back(Timer);
	Timer->start();
}

//------------------------------------------------------------

void sSceneManager::addListener(sSceneListener* Object)
{
	m_Listeners.push_back(Object);
}

//------------------------------------------------------------

void sSceneManager::sortLayers()
{
	m_Layers.sort(compareLayerOrder);
}