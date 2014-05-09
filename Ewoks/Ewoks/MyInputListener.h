#ifndef MY_INPUT_LISTENER
#define MY_INPUT_LISTENER

#include "InputListener.h"

class MyInputListener : public InputListener
{
private:
	bool assigned;
public:
	MyInputListener();
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
};
#endif