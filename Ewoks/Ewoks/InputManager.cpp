#include "stdafx.h"
#include "InputManager.h"
#include <sstream>
#include "InputListener.h"

InputManager::InputManager()
{
	m_OISInputManager = nullptr;
	m_Keyboard = nullptr;
}

void InputManager::Init(HWND windowHandle)
{
	OIS::ParamList p1;
	std::ostringstream windowHndStr;
	size_t handle = (size_t) windowHandle;
	windowHndStr << handle;
	p1.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	m_OISInputManager = OIS::InputManager::createInputSystem(p1);

	if (m_OISInputManager->getNumberOfDevices(OIS::OISKeyboard) > 0)
	{
		m_Keyboard = static_cast<OIS::Keyboard*>(
			m_OISInputManager->createInputObject(OIS::OISKeyboard, true));

		m_Keyboard->setEventCallback(this);
	}
}

void InputManager::Free()
{
	if (m_OISInputManager)
	{
		m_OISInputManager->destroyInputSystem(m_OISInputManager);
	}
}

bool InputManager::keyPressed(const OIS::KeyEvent &e)
{
	std::list<InputListener*>::iterator list_it;

	for (list_it = m_InputListeners.begin(); list_it != m_InputListeners.end(); list_it++)
		(*list_it)->keyPressed(e);

	return true;
}

bool InputManager::keyReleased(const OIS::KeyEvent &e)
{
	std::list<InputListener*>::iterator list_it;
	for (list_it = m_InputListeners.begin(); list_it != m_InputListeners.end(); list_it++)
		(*list_it)->keyReleased(e);

	return true;
}

void InputManager::Update()
{
	if (m_Keyboard)
		m_Keyboard->capture();
}

void InputManager::AddListener(InputListener *listener)
{
	m_InputListeners.push_back(listener);
}