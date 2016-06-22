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
        union aeskey_t {
            uint8_t c_key[16];
            uint16_t w_key[8];
            uint32_t dw_key[4];
            uint64_t qw_key[2];
        };

        GateKeeper(CpEpCOMServerAdapterModule * self);
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

        string update_key();
        BCRYPT_KEY_HANDLE delivery_key();
        string wrapped_delivery_key(BCRYPT_KEY_HANDLE hDeliveryKey);

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
        BCRYPT_ALG_HANDLE hAES;
        BCRYPT_ALG_HANDLE hRSA;

        CpEpCOMServerAdapterModule * _self;
    };
}
