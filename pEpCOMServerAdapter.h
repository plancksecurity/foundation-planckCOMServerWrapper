#include "stdafx.h"

#include "pEpCOMServerAdapter_i.h"

using namespace ATL;
using namespace std;

class CpEpCOMServerAdapterModule : public ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule > {
public:
    CpEpCOMServerAdapterModule() : ATL::CAtlExeModuleT< CpEpCOMServerAdapterModule >(), gatekeeper_thread(NULL), _hModule(NULL)
    {
    }

    DECLARE_LIBID(LIBID_pEpCOMServerAdapterLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PEPCOMSERVERADAPTER, "{B3480081-82C0-4EE4-9AA1-3F513C9D78DD}")

    HMODULE hModule()
    {
        return _hModule;
    }

    void hModule(HMODULE m)
    {
        _hModule = m;
    }

    void start_gatekeeper()
    {
#ifdef NDEBUG
        this->Lock(); // never exit
#endif

        try {
            gatekeeper_thread = new thread(gatekeeper, this);
            gatekeeper_thread->detach();
        }
        catch (system_error&) {

        }
    }

protected:
    static void gatekeeper(CpEpCOMServerAdapterModule * self);

private:
    thread *gatekeeper_thread;
    HMODULE _hModule;
};
