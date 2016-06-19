class CpEpCOMServerAdapterModule;

class GateKeeper {
public:
    GateKeeper(CpEpCOMServerAdapterModule * const self) : _self(self), now(time(NULL)), next(now + time_diff())
    {
        LONG lResult = RegOpenCurrentUser(KEY_READ, &cu);
        assert(lResult == ERROR_SUCCESS);
        if (lResult == ERROR_SUCCESS)
            cu_open = true;
        else
            cu_open = false;
    }

    ~GateKeeper()
    {
        if (cu_open)
            RegCloseKey(cu);
    }

    CpEpCOMServerAdapterModule * const module() const
    {
        return _self;
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
    bool cu_open;
    HKEY cu;

    CpEpCOMServerAdapterModule * const _self;
};
