#ifndef MESSENGER_H
#define MESSENGER_H

#include <list>
#include "EngineObject.h"

class Telegram;

class Messenger
{
private:
	Messenger() {}

	Messenger(Messenger const&);
	void operator=(Messenger const&);

public:
	static Messenger &GetMessenger();

	void AddListener(EngineObject *engineObject);

	void AddMessage(Telegram *telegram);
	void RemoveMessage(Telegram *telegram);

	void Send();

private:
	std::list<EngineObject*> listeners;
	std::list<EngineObject*>::const_iterator listenersIt;

	std::list<Telegram*> commands;
	std::list<Telegram*>::const_iterator commandsIt;
};
#endif // !MESSENGER_H
