#include "stdafx.h"
#include "pEp_identity_helper.h"

namespace pEp {
    namespace utility {
        pEp_identity_cpp::pEp_identity_cpp(const ::pEp_identity *_ident)
            : me(false)
        {
            if (_ident->address)
                address = _ident->address;
            if (_ident->fpr)
                fpr = _ident->fpr;
            if (_ident->user_id)
                user_id = _ident->user_id;
            if (_ident->username)
                username = _ident->username;
            comm_type = (pEp_comm_type) _ident->comm_type;
            lang = _ident->lang;
        }

        pEp_identity_cpp::pEp_identity_cpp(const pEp_identity_s *_ident)
            : me(false)
        {
            if (_ident->address)
                address = utf8_string(_ident->address);
            if (_ident->fpr)
                fpr = utf8_string(_ident->fpr);
            if (_ident->user_id)
                user_id = utf8_string(_ident->user_id);
            if (_ident->username)
                username = utf8_string(_ident->username);
            comm_type = _ident->comm_type;
            if (_ident->lang)
                lang = utf8_string(_ident->lang);
        }

        pEp_identity * pEp_identity_cpp::to_pEp_identity()
        {
            ::pEp_identity *_ident = ::new_identity(this->address.c_str(), this->fpr.c_str(), this->user_id.c_str(), this->username.c_str());
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->comm_type = (::PEP_comm_type) this->comm_type;
            _ident->me = this->me;

            assert(this->lang.size() == 0 || this->lang.size() == 2);

            if (this->lang.size()) {
                _ident->lang[0] = this->lang[0];
                _ident->lang[1] = this->lang[1];
            }

            return _ident;
        }

        pEp_identity_s * pEp_identity_cpp::to_pEp_identity_s()
        {
            pEp_identity_s *_ident = (pEp_identity_s *) calloc(1, sizeof(pEp_identity_s));
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->address = utf16_bstr(this->address).Detach();
            _ident->comm_type = this->comm_type;
            _ident->fpr = utf16_bstr(this->fpr).Detach();
            _ident->lang = utf16_bstr(this->lang).Detach();
            _ident->username = utf16_bstr(this->username).Detach();
            _ident->user_id = utf16_bstr(this->user_id).Detach();

            return _ident;
        }

        void copy_identity(pEp_identity_s * ident_s, const pEp_identity * ident)
        {
            assert(ident_s);

            ::memset(ident_s, 0, sizeof(pEp_identity_s));
            if (ident) {
                if (ident->address)
                    ident_s->address = utf16_bstr(ident->address).Detach();
                if (ident->fpr)
                    ident_s->fpr = utf16_bstr(ident->fpr).Detach();
                if (ident->user_id)
                    ident_s->user_id = utf16_bstr(ident->user_id).Detach();
                if (ident->username)
                    ident_s->username = utf16_bstr(ident->username).Detach();
                ident_s->comm_type = (pEp_comm_type) ident->comm_type;
                if (ident->lang)
                    ident_s->lang = utf16_bstr(ident->lang).Detach();
            }
        }

        ::pEp_identity *new_identity(const pEp_identity_s * ident)
        {
            ::pEp_identity *_ident;

            string _address;
            string _fpr;
            string _user_id;
            string _username;

            if (ident->address)
                _address = utf8_string(ident->address);
            if (ident->fpr) {
                _fpr = utf8_string(ident->fpr);
                for (auto p = _fpr.begin(); p != _fpr.end(); ++p) {
                    if (*p >= 'A' && *p <= 'Z')
                        continue;
                    if (*p >= '0' && *p <= '9')
                        continue;
                    throw invalid_argument("invalid hex digits in fingerprint");
                }
            }
            if (ident->user_id)
                _user_id = utf8_string(ident->user_id);
            if (ident->username)
                _username = utf8_string(ident->username);

            _ident = ::new_identity(_address.c_str(), _fpr.c_str(), _user_id.c_str(), _username.c_str());
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->comm_type = (PEP_comm_type) ident->comm_type;

            if (ident->lang) {
                string _lang = utf8_string(ident->lang);
                if (_lang.length() != 0) {
                    if (_lang.length() != 2) {
                        ::free_identity(_ident);
                        throw invalid_argument("invalid language code");
                    }
                    if (_lang[0] < 'a' || _lang[0] > 'z') {
                        ::free_identity(_ident);
                        throw invalid_argument("invalid language code");
                    }
                    if (_lang[1] < 'a' || _lang[1] > 'z') {
                        ::free_identity(_ident);
                        throw invalid_argument("invalid language code");
                    }
                    _ident->lang[0] = _lang[0];
                    _ident->lang[1] = _lang[1];
                }
            }

            return _ident;
        }
    }
}
