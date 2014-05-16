#include "stdafx.h"
#include "MyInputListener.h"
#include "Telegram.h"
#include "Messenger.h"

// TODO Make Delegate for sending bools to correct function
// function sets bool to true, and class receiving message does something
MyInputListener::MyInputListener()
{
	mainKey = false;
	altKey = false;
}

bool MyInputListener::keyPressed(const OIS::KeyEvent &e)
{
	switch (e.key)
	{
	case OIS::KC_LEFT:
		Messenger::GetMessenger().AddMessage(moveLeft);
		break;
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		Messenger::GetMessenger().AddMessage(moveRight);
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
		Messenger::GetMessenger().RemoveMessage(moveLeft);
		break;
	case OIS::KC_RIGHT:
	case OIS::KC_D:
		Messenger::GetMessenger().RemoveMessage(moveRight);
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