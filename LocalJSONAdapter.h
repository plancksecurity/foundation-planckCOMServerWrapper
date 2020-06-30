#pragma once
#include "stdafx.h"
#include "json-adapter.hh"
#include "..\libpEpAdapter\Adapter.hh""

class LocalJSONAdapter :
    public JsonAdapter
{
public:
	static LocalJSONAdapter& createInstance();

protected:
	virtual inject_sync_event_t getInjectSyncEvent() const override
	{
		return pEp::Adapter::_inject_sync_event;
	}
};
