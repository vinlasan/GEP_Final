#include "stdafx.h"
#include "MyInputListener.h"

// TODO Make Delegate for sending bools to correct function
// function sets bool to true, and class receiving message does something
MyInputListener::MyInputListener()
{

}

bool MyInputListener::keyPressed(const OIS::KeyEvent &e)
{
	switch (e.key)
	{
	case OIS::KC_LEFT:
	case OIS::KC_A:
		break;
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		break;
	case OIS::KC_DOWN:
	case OIS::KC_S:
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		break;
	default:
		break;
	}

	return true;
}

bool MyInputListener::keyReleased(const OIS::KeyEvent &e)
{
	switch (e.key)
	{
	case OIS::KC_LEFT:
	case OIS::KC_A:
		break;
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		break;
	case OIS::KC_DOWN:
	case OIS::KC_S:
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		break;
	default:
		break;
	}

	return true;
}