#include "stdafx.h"
#include "LocalJSONAdapter.h"

void startSync() { }
void stopSync() { }

LocalJSONAdapter& LocalJSONAdapter::createInstance()
{
	return dynamic_cast<LocalJSONAdapter&>(JsonAdapter::createInstance(new LocalJSONAdapter()));
}
