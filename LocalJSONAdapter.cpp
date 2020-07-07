#include "stdafx.h"
#include "LocalJSONAdapter.h"
#include <pEp/Adapter.hh>

void startSync() { }
void stopSync() { }

std::thread::id LocalJSONAdapter::get_sync_thread_id() const
{
	return pEp::Adapter::sync_thread_id();
}

LocalJSONAdapter& LocalJSONAdapter::createInstance()
{
	return dynamic_cast<LocalJSONAdapter&>(JsonAdapter::createInstance(new LocalJSONAdapter()));
}
