
#include <assert.h>

#include "dispatchers.h"


Dispatcher::Dispatcher(const sigc::slot<void>& slot)
{
	dispatcher.connect(slot);
}

void Dispatcher::notify()
{
	dispatcher.emit();
}
