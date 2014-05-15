#ifndef ENGINEOBJECT_H_INCLUDED
#define ENGINEOBJECT_H_INCLUDED

#include "MessageListener.h"

#define SAFE_DELETE(a) { delete (a); (a) = NULL; }

class EngineObject : public MessageListener
{
    private:
    protected:
    public:
		virtual void HandleMessage(Telegram *telegram);
};

#endif // ENGINEOBJECT_H_INCLUDED
