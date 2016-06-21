class CpEpCOMServerAdapterModule;

using namespace std;

namespace pEp {

#ifdef UNICODE
    typedef wstring tstring;
#else
    typedef string tstring;
#endif

    class GateKeeper {
    public:
        typedef pair<tstring, tstring> product;
        typedef vector< product > product_list;

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

        string updateKey();
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

        CpEpCOMServerAdapterModule * _self;
    };
}
