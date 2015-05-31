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
            pEp_comm_type comm_type;
            string lang;
            bool me;

            pEp_identity_cpp(
                string _address = string(),
                string _fpr = string(),
                string _user_id = string(),
                string _username = string(),
                pEp_comm_type _comm_type = pEp_ct_unknown,
                string _lang = string()
                ) : address(_address), fpr(_fpr), user_id(_user_id), username(_username), comm_type(_comm_type), lang(_lang), me(false)
            { }

            pEp_identity_cpp(const ::pEp_identity *_ident);
            pEp_identity_cpp(const pEp_identity_s *_ident);

            pEp_identity * to_pEp_identity();
            pEp_identity_s * to_pEp_identity_s();
        };

        void copy_identity(pEp_identity_s * ident_s, const pEp_identity * ident);
        ::pEp_identity *new_identity(const pEp_identity_s * ident);

        static LPTYPELIB pTypelib = NULL;

        template< class UDType > static IRecordInfo *getRecordInfo()
        {
            LPTYPEINFO pTypeInfo = NULL;
            LPSAFEARRAY psaUDType = NULL;
            IRecordInfo* pRecInfo = NULL;

            // Fetch the IRecordInfo interface describing the UDT
            if (pTypelib == NULL)
                LoadRegTypeLib(LIBID_pEpCOMServerAdapterLib, 1, 0, GetUserDefaultLCID(), &pTypelib);

            assert(pTypelib);

            HRESULT hr = pTypelib->GetTypeInfoOfGuid(__uuidof(UDType), &pTypeInfo);
            assert(SUCCEEDED(hr) && pTypeInfo);
            hr = GetRecordInfoFromTypeInfo(pTypeInfo, &pRecInfo);
            assert(SUCCEEDED(hr) && pRecInfo);
            pTypeInfo->Release();
            pTypelib->Release();

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

        ::message * text_message_to_C(text_message *msg);
        void text_message_from_C(text_message *msg2, ::message *msg);
    }
}
