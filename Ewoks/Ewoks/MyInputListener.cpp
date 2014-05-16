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
		Messenger::GetMessenger().AddMessage(moveRight);
		break;
	case OIS::KC_DOWN:
		Messenger::GetMessenger().AddMessage(moveDown);
		break;
	case OIS::KC_UP:
		Messenger::GetMessenger().AddMessage(moveUp);
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
		Messenger::GetMessenger().RemoveMessage(moveRight);
		break;
	case OIS::KC_DOWN:
		Messenger::GetMessenger().RemoveMessage(moveDown);
		break;
	case OIS::KC_UP:
		Messenger::GetMessenger().RemoveMessage(moveUp);
		break;
	default:
		break;
	}

	return true;
}