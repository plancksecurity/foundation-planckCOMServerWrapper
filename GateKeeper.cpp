#include "stdafx.h"

#include "GateKeeper.h"

using namespace std;

const LPCTSTR GateKeeper::plugin_reg_path = _T("Software\\Microsoft\\Office\\Outlook\\Addins\\pEp");
const LPCTSTR GateKeeper::plugin_reg_value_name = _T("LoadBehavior");

const time_t GateKeeper::cycle = 7200;   // 7200 sec is 2 h
const DWORD GateKeeper::waiting = 10000; // 10000 ms is 10 sec

time_t GateKeeper::time_diff()
{
    try {
        static random_device rd;
        static mt19937 gen(rd());

        uniform_int_distribution<time_t> dist(0, cycle);

        return dist(gen);
    }
    catch (exception&) {
        assert(0);
        return 0;
    }
}

void GateKeeper::keep()
{
    while (1) {
        keep_plugin();

        now = time(NULL);
        assert(now != -1);

        if (now > next) {
            next = now + GateKeeper::cycle;
            keep_updated();
        }

        Sleep(waiting);
    }
}

void GateKeeper::keep_plugin()
{
    DWORD value;
    DWORD size;

    LONG lResult = RegGetValue(cu, plugin_reg_path, plugin_reg_value_name, RRF_RT_REG_DWORD, NULL, &value, &size);
    if (lResult != ERROR_SUCCESS)
        return;

    if (value != 3) {
        lResult = RegSetValue(cu, plugin_reg_path, RRF_RT_REG_DWORD, plugin_reg_value_name, 3);
        assert(lResult == ERROR_SUCCESS);
    }
}

void GateKeeper::keep_updated()
{

}
