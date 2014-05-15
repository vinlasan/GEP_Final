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
	sceneManager->loadFromXMLFile("SceneTree.xml");
	sceneManager->addTimer(0, 2000);


	InputManager inputMan;
	inputMan.Init(renderManager->GetWindowHandle());

	MyInputListener* myInputListener = new MyInputListener();
	inputMan.AddListener(myInputListener);
	
	//Messenger::GetMessenger().AddListener(new TestObj());

	SDL_RenderClear(renderManager->m_Renderer);
	
	renderManager->renderAllObjects();

	//TODO add rendering loop here
	for (size_t i = 0; i < resourceManager->getResourceCount(); i++)
	{

		RenderObject* RenderObject = new RenderObject();
		//RenderObject->setResourceObject((RenderResource*)ResourceManager->findResourcebyID(i + 1));
		//renderManager->RenderObjects.push_back(RenderObject);
	}

	while (true)
	{
		inputMan.Update();
		Messenger::GetMessenger().Send();
	}

	system("PAUSE");


	return 0;
}

