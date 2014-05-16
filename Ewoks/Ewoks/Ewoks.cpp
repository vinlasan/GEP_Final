// Ewoks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <cstdlib>
#include <stdio.h>
#include <tchar.h>
#include <tinyxml2.h>
#include "RenderManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "OIS.h"
#include "InputManager.h"
#include "MyInputListener.h"
#include "Messenger.h"
#include "RenderObject.h"
#include "RenderResource.h"

//For testing messenger

#ifdef main
# undef main
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	RenderManager* renderManager = RenderManager::GetRenderManager();
	ResourceManager* resourceManager = ResourceManager::GetResourceManager();
	sSceneManager* sceneManager = new sSceneManager();

	if (renderManager->Initialize())
	{
		std::cout << "Initialized" << std::endl;
	}
	else
	{
		printf( "Unable to Initialize: %s\n", SDL_GetError());
	}

	resourceManager->loadFromXMLFile("ResourceTree.xml");
	

	//TODO add rendering loop here
	for (size_t i = 0; i < resourceManager->getResourceCount(); i++)
	{

		RenderObject* renderObject = new RenderObject();
		renderObject->setResourceObject((RenderResource*)resourceManager->findResourcebyID(i + 1));
		resourceManager->setCurrentScope(0);
		renderManager->m_RenderObjects.push_back(renderObject);
	}

	sceneManager->loadFromXMLFile("SceneTree.xml");
	renderManager->m_SceneManager = sceneManager;

	InputManager inputMan;
	inputMan.Init(renderManager->GetWindowHandle());

	MyInputListener* myInputListener = new MyInputListener();
	inputMan.AddListener(myInputListener);

	sceneManager->addTimer(0, 2000);

	/*std::list<stwoDLayer*>::const_iterator it;
	for (it = sceneManager->m_Layers.begin(); it != sceneManager->m_Layers.end(); it++)
	{
		std::list<sSceneObject*>::const_iterator is;
		for (is = (*it)->m_SceneObjects.begin(); is != (*it)->m_SceneObjects.end(); is++)
		{
			Messenger::GetMessenger().AddListener(*is);
		}
	}*/
	

	renderManager->renderAllObjects();

	while (renderManager->update())
	{
		inputMan.Update();
		Messenger::GetMessenger().Send();
		sceneManager->update();
	}
	SDL_RenderClear(renderManager->m_Renderer);
	//system("PAUSE");
	

	return 0;
}

