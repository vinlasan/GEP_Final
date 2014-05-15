#include "stdafx.h"
#include "Messenger.h"
#include "Telegram.h"

Messenger &Messenger::GetMessenger()
{
	static Messenger instance;
	return instance;
}

void Messenger::AddListener(EngineObject *engineObject)
{
	listeners.push_back(engineObject);
}

void Messenger::AddMessage(Telegram *telegram)
{
	commands.push_back(telegram);
}

void Messenger::RemoveMessage(Telegram *telegram)
{
	commands.remove(telegram);
}

void Messenger::Send()
{
	for (listenersIt = listeners.begin(); listenersIt != listeners.end(); listenersIt++)
	{
		for (commandsIt = commands.begin(); commandsIt != commands.end(); commandsIt++)
		{
			(*listenersIt)->HandleMessage((*commandsIt));
		}
	}
}