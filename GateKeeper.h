class CpEpCOMServerAdapterModule;

class GateKeeper {
public:
    GateKeeper(CpEpCOMServerAdapterModule * const self) : _self(self), now(time(NULL)), next(now + time_diff())
    {
        LONG lResult = RegOpenCurrentUser(KEY_READ, &cu);
        assert(lResult == ERROR_SUCCESS);
    }

    ~GateKeeper()
    {
        RegCloseKey(cu);
    }

    void keep();

protected:
    static const LPCTSTR plugin_reg_path;
    static const LPCTSTR plugin_reg_value_name;
    static const time_t cycle;
    static const DWORD waiting;

    static time_t time_diff();
    void keep_plugin();
    void keep_updated();

private:
    time_t now;
    time_t next;
    HKEY cu;

    CpEpCOMServerAdapterModule * const _self;
};
