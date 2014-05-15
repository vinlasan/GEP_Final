#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

class Telegram;

class MessageListener
{
	virtual void HandleMessage(Telegram*) = 0;
};
#endif // !MessageListener
