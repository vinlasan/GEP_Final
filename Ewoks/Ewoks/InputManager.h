#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "OIS.h"
#include "SDL_syswm.h"
#include <list>

class InputListener;

class InputManager : public OIS::KeyListener
{
public:
	OIS::InputManager *m_OISInputManager;
	OIS::Keyboard *m_Keyboard;

	std::list<InputListener*> m_InputListeners;

	InputManager();

	void Init(HWND windowHandle);
	void Free();

	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

	void Update();

	void AddListener(InputListener *listener);
};
#endif // !INPUTMANAGER_H
