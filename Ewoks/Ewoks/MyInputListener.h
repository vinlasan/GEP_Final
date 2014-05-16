#ifndef MY_INPUT_LISTENER
#define MY_INPUT_LISTENER

#include "InputListener.h"
#include "Telegram.h"

class MyInputListener : public InputListener
{
private:
	bool mainKey;
	bool altKey;

	Telegram *moveLeft = new Telegram(RIGHT, -5);
	Telegram *moveRight = new Telegram(RIGHT,5);
	Telegram *moveDown = new Telegram(UP,5);
	Telegram *moveUp = new Telegram(UP,-5);

public:
	MyInputListener();
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);
};
#endif