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

#ifdef main
# undef main
#endif

int _tmain(int argc, _TCHAR* argv[])
{
	ResourceManager* resourceManager = ResourceManager::GetResourceManager();
	RenderManager* renderManager = RenderManager::GetRenderManager();
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

	InputListener* inListener;
	//inputMan.AddListener(inListener);

	SDL_RenderClear(renderManager->m_Renderer);
	
	renderManager->renderAllObjects();

	system("PAUSE");


	return 0;
}

