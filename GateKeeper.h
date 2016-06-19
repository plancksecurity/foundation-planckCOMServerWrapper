class CpEpCOMServerAdapterModule;

namespace pEp {

#ifdef UNICODE
    typedef std::wstring tstring;
#else
    typedef std::string tstring;
#endif

    class GateKeeper {
    public:
        typedef std::pair<tstring, tstring> product;
        typedef std::vector< product > product_list;

        GateKeeper(CpEpCOMServerAdapterModule * const self);
        ~GateKeeper();

        CpEpCOMServerAdapterModule * const module() const
        {
            return _self;
        }

        void keep();

    protected:
        static const LPCTSTR plugin_reg_path;
        static const LPCTSTR plugin_reg_value_name;
        static const LPCTSTR updater_reg_path;

        static const time_t cycle;
        static const DWORD waiting;

        static time_t time_diff();

        void keep_plugin();

        string handshake(HINTERNET hUrl);
        void update_product(product p, DWORD context);
        product_list& registered_products();
        void keep_updated();

    private:
        time_t now;
        time_t next;
        bool cu_open;
        HKEY cu;
        HKEY hkUpdater;
        HINTERNET internet;

        CpEpCOMServerAdapterModule * const _self;
    };
}
