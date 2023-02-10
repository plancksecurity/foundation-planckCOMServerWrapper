#pragma once
#include "stdafx.h"
#include "json-adapter.hh"

class LocalJSONAdapter :
    public JsonAdapter
{
public:
	static LocalJSONAdapter& createInstance();
	std::thread::id get_sync_thread_id() const;

protected:
	virtual inject_sync_event_t getInjectSyncEvent() const override
	{
		return pEp::Adapter::_cb_inject_sync_event_enqueue_sync_event;
	}
};
