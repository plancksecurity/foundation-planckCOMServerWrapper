#pragma once

#include "stdafx.h"
#include "pEpComServerAdapter_i.h"
#include "utf8_helper.h"


using namespace std;

namespace pEp {
    namespace utility {

        struct pEp_identity_cpp {
            string address;
            string fpr;
            string user_id;
            string username;
            pEpComType comm_type;
            string lang;
			bool me;
            int flags;

            pEp_identity_cpp(
                string _address = string(),
                string _fpr = string(),
                string _user_id = string(),
                string _username = string(),
                pEpComType _comm_type = pEpCtUnknown,
				bool _me = false,
                string _lang = string()
            ) : address(_address), fpr(_fpr), user_id(_user_id), username(_username), comm_type(_comm_type), me(_me), lang(_lang)
            { }

            pEp_identity_cpp(const ::pEp_identity *_ident);
            pEp_identity_cpp(const pEpIdentity *_ident);

            pEp_identity * to_pEp_identity();
            pEpIdentity * to_pEp_identity_s();
        };

        void copy_identity(pEpIdentity * ident_s, const pEp_identity * ident);
        void clear_identity_s(pEpIdentity& ident);
        void clear_text_message(TextMessage *msg);
        ::pEp_identity *new_identity(const pEpIdentity * ident);

        void opt_field_array_from_C(stringpair_list_t* spair_list, LPSAFEARRAY* pair_list_out);
        void clear_opt_field_array(LPSAFEARRAY* pair_list);
        template< class T2, class T > SAFEARRAY * array_from_C(T *tl);

        static LPTYPELIB pTypelib = NULL;

        template< class UDType > static IRecordInfo *getRecordInfo()
        {
            LPTYPEINFO pTypeInfo = NULL;
            LPSAFEARRAY psaUDType = NULL;
            IRecordInfo* pRecInfo = NULL;
            HRESULT hr;

            // Fetch the IRecordInfo interface describing the UDT
            if (pTypelib == NULL) {
                hr = LoadRegTypeLib(LIBID_pEpCOMServerAdapterLib, 1, 0, GetUserDefaultLCID(), &pTypelib);
                assert(SUCCEEDED(hr));
                if (!SUCCEEDED(hr))
                    throw runtime_error("getRecordInfo(): LoadRegTypeLib cannot load LIBID_pEpCOMServerAdapterLib");
            }

            assert(pTypelib);

            GUID guid = __uuidof(UDType);
            hr = pTypelib->GetTypeInfoOfGuid(guid, &pTypeInfo);
            assert(SUCCEEDED(hr) && pTypeInfo);
            hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
            assert(SUCCEEDED(hr) && pRecInfo);
            pTypeInfo->Release();

            return pRecInfo;
        }

        template< class UDType > LPSAFEARRAY newSafeArray(ULONG cElements)
        {
            IRecordInfo *pRecInfo = getRecordInfo< UDType >();
            SAFEARRAYBOUND rgbounds = { cElements, 0 };
            LPSAFEARRAY psaUDType = SafeArrayCreateEx(VT_RECORD, 1, &rgbounds, pRecInfo);
            pRecInfo->Release();
            assert(psaUDType);

            return psaUDType;
        }

		identity_list *identities(SAFEARRAY * sa);
        ::message * text_message_to_C(TextMessage *msg);
        void text_message_from_C(TextMessage *msg2, const ::message *msg);

        // group
        pEpGroup pEpGroup_from_C(pEp_group* group);
        member_list* members(SAFEARRAY* sa);

    }
}
