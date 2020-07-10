#include "stdafx.h"

class CpEpCOMServerAdapterModule;

using namespace std;

namespace pEp {

#ifdef UNICODE
	typedef wstring tstring;
	typedef wregex tregex;
	typedef wsmatch tsmatch;
#else
	typedef string tstring;
	typedef regex tregex;
	typedef smatch tsmatch;
#endif

    class GateKeeper {
    public:
        typedef pair<tstring, tstring> product;
        typedef vector< product > product_list;
        union aeskey_t {
            uint8_t c_key[32];
            uint16_t w_key[16];
            uint32_t dw_key[8];
            uint64_t qw_key[4];
        };

        GateKeeper(CpEpCOMServerAdapterModule * self);
        ~GateKeeper();

        CpEpCOMServerAdapterModule * const module() const
        {
            return _self;
        }

        void keep();
		product_list registered_products();
		bool update_product(product p, DWORD context = 0);

        bool update_enabled();
        void enable_update();
        void disable_update();
        void update_now();

        void show_notification(tstring title, tstring text);

		static GateKeeper *gatekeeper() { return the_gatekeeper; }

    protected:
        static const LPCTSTR plugin_reg_path;
        static const LPCTSTR plugin_reg_value_name;
        static const LPCTSTR updater_reg_path;

        static const time_t cycle;
        static const time_t fraction;
        static const DWORD waiting;

        static time_t time_diff();

        void keep_plugin();

        void execute_file(tstring filename);
        string update_key();
        BCRYPT_KEY_HANDLE delivery_key();
        string wrapped_delivery_key(BCRYPT_KEY_HANDLE hDeliveryKey);

        static tstring get_lockFile();
		static GateKeeper *the_gatekeeper;

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
