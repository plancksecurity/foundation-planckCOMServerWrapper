#include "stdafx.h"
#include "pEp_utility.h"

using namespace ATL;

namespace pEp {
    namespace utility {
        pEp_identity_cpp::pEp_identity_cpp(const ::pEp_identity *_ident)
            : me(false)
        {
			if (!_ident)
				return;

            if (_ident->address)
                address = _ident->address;
            if (_ident->fpr)
                fpr = _ident->fpr;
            if (_ident->user_id)
                user_id = _ident->user_id;
            if (_ident->username)
                username = _ident->username;
            comm_type = (pEpComType) _ident->comm_type;
            lang = _ident->lang;
			flags = (int) _ident->flags;
        }

        pEp_identity_cpp::pEp_identity_cpp(const pEpIdentity *_ident)
            : me(false)
        {
			if (!_ident)
				return;

			if (_ident->Address)
                address = utf8_string(_ident->Address);
            if (_ident->Fpr)
                fpr = utf8_string(_ident->Fpr);
            if (_ident->UserId)
                user_id = utf8_string(_ident->UserId);
            if (_ident->UserName)
                username = utf8_string(_ident->UserName);
            comm_type = _ident->CommType;
            if (_ident->Lang)
                lang = utf8_string(_ident->Lang);
			flags = (int)_ident->Flags;
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

			_ident->flags = (identity_flags) this->flags;

            return _ident;
        }

        pEpIdentity * pEp_identity_cpp::to_pEp_identity_s()
        {
            pEpIdentity *_ident = (pEpIdentity *) calloc(1, sizeof(pEpIdentity));
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->Address = utf16_bstr(this->address);
            _ident->CommType = this->comm_type;
            _ident->Fpr = utf16_bstr(this->fpr);
            _ident->Lang = utf16_bstr(this->lang);
            _ident->UserName = utf16_bstr(this->username);
            _ident->UserId = utf16_bstr(this->user_id);
			_ident->Flags = (pEpIdentityFlags) this->flags;

            return _ident;
        }

        void copy_identity(pEpIdentity * ident_s, const pEp_identity * ident)
        {
            assert(ident_s);
			if (!ident_s)
				throw invalid_argument("ident_s");

            ::memset(ident_s, 0, sizeof(pEpIdentity));
            if (ident) {
                if (ident->address)
                    ident_s->Address = utf16_bstr(ident->address);
                if (ident->fpr)
                    ident_s->Fpr = utf16_bstr(ident->fpr);
                if (ident->user_id)
                    ident_s->UserId = utf16_bstr(ident->user_id);
                if (ident->username)
                    ident_s->UserName = utf16_bstr(ident->username);
                ident_s->CommType = (pEpComType) ident->comm_type;
                if (ident->lang)
                    ident_s->Lang = utf16_bstr(ident->lang);
				ident_s->Flags = (pEpIdentityFlags) ident->flags;
            }
        }

        ::pEp_identity *new_identity(const pEpIdentity * ident)
        {
            if (ident == NULL)
                return NULL;

            ::pEp_identity *_ident;

            string _address;
            string _fpr;
            string _user_id;
            string _username;

            if (ident->Address)
                _address = utf8_string(ident->Address);
            if (ident->Fpr) {
                _fpr = utf8_string(ident->Fpr);
                for (auto p = _fpr.begin(); p != _fpr.end(); ++p) {
                    if (*p >= 'A' && *p <= 'Z')
                        continue;
                    if (*p >= '0' && *p <= '9')
                        continue;
                    throw invalid_argument("invalid hex digits in fingerprint");
                }
            }
            if (ident->UserId)
                _user_id = utf8_string(ident->UserId);
            if (ident->UserName)
                _username = utf8_string(ident->UserName);

            _ident = ::new_identity(_address.c_str(), _fpr.c_str(), _user_id.c_str(), _username.c_str());
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->comm_type = (PEP_comm_type) ident->CommType;

            if (ident->Lang) {
                string _lang = utf8_string(ident->Lang);
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

			_ident->flags = (identity_flags_t)ident->Flags;

            return _ident;
        }

        template< class T2, class T > T2 from_C(T *tl);

        BSTR bstr(char *s)
        {
            if (s == NULL)
                return _bstr_t(L"").Detach();

            return utf16_bstr(s);
        }

        template<> Blob *from_C< Blob *, bloblist_t >(bloblist_t *tl)
        {
			assert(tl);

            CComSafeArray<BYTE> sa;
			if (tl) {
				sa.Create(tl->size);
				if (tl->size) {
					char *data;
					SafeArrayAccessData(sa, (void **)&data);
					memcpy(data, tl->value, tl->size);
					SafeArrayUnaccessData(sa);
				}
			}
			else {
				sa.Create((ULONG)0);
			}

            Blob *_blob = new Blob();

            _blob->value = sa.Detach();
            _blob->MimeType = bstr(tl->mime_type);
            _blob->Filename = bstr(tl->filename);

            return _blob;
        }

        template< class T > int length(T *);

        template< class T2, class T > SAFEARRAY * array_from_C(T *tl)
        {
            if (tl == NULL)
                return newSafeArray<T2>(0);

            int len = length<T>(tl);

            LPSAFEARRAY sa = newSafeArray<T2>(len);
            LONG lbound, ubound;
            SafeArrayGetLBound(sa, 1, &lbound);
            SafeArrayGetUBound(sa, 1, &ubound);

            T *_tl = tl;
            for (LONG i = lbound; i <= ubound; _tl = _tl->next, i++)
                SafeArrayPutElement(sa, &i, from_C<T2 *, T>(_tl));

            return sa;
        }

        void clear_identity_s(pEpIdentity& ident)
        {
            SysFreeString(ident.Address);
            SysFreeString(ident.Fpr);
            SysFreeString(ident.Lang);
            SysFreeString(ident.UserName);
            SysFreeString(ident.UserId);

            memset(&ident, 0, sizeof(pEpIdentity));
        }

        template<> pEpIdentity from_C< pEpIdentity, pEp_identity >(pEp_identity *tl)
        {
            pEpIdentity _ident;
            memset(&_ident, 0, sizeof(_ident));

            if (tl)
                copy_identity(&_ident, tl);
            return _ident;
        }

        pEpIdentity identity_s(pEp_identity *ident)
        {
            return from_C< pEpIdentity, pEp_identity >(ident);
        }

        template<> pEpIdentity *from_C< pEpIdentity *, identity_list >(identity_list *il)
        {
            pEpIdentity *ident = new pEpIdentity();
            memset(ident, 0, sizeof(pEpIdentity));

            if (il)
                copy_identity(ident, il->ident);
            return ident;
        }

        template<> StringPair *from_C< StringPair *, stringpair_list_t >(stringpair_list_t * sp)
        {
            StringPair *fld = new StringPair();
            if (sp) {
                fld->Name = bstr(sp->value->key);
                fld->Value = bstr(sp->value->value);
            }
            return fld;
        }

        template<> int length<identity_list>(identity_list *tl)
        {
            return identity_list_length(tl);
        }

        template<> int length<bloblist_t>(bloblist_t *tl)
        {
            return bloblist_length(tl);
        }

        template<> int length<stringpair_list_t>(stringpair_list_t *tl)
        {
            return stringpair_list_length(tl);
        }

        void clear_text_message(TextMessage *msg)
        {
			assert(msg);
			if (!msg)
				return;

            SysFreeString(msg->Id);
            SysFreeString(msg->ShortMsg);
            SysFreeString(msg->LongMsg);
            SysFreeString(msg->LongMsgFormatted);
            SafeArrayDestroy(msg->Attachments);
            clear_identity_s(msg->From);
            SafeArrayDestroy(msg->To);
            clear_identity_s(msg->RecvBy);
            SafeArrayDestroy(msg->Cc);
            SafeArrayDestroy(msg->Bcc);
            SafeArrayDestroy(msg->ReplyTo);
            SafeArrayDestroy(msg->References);
            SafeArrayDestroy(msg->Keywords);
            SysFreeString(msg->Comments);
            SafeArrayDestroy(msg->OptFields);

            memset(msg, 0, sizeof(TextMessage));
        }

        void text_message_from_C(TextMessage *msg2, const ::message *msg)
        {
            assert(msg2);
            assert(msg);

			if (!msg2) {
				msg2 = (TextMessage *)calloc(1, sizeof(TextMessage));
				assert(msg2);
				if (!msg2)
					throw bad_alloc();
			}
			else {
				clear_text_message(msg2);
			}

			if (!msg)
				return;

            msg2->Dir = (pEpMsgDirection) msg->dir;
            msg2->Id = bstr(msg->id);
            msg2->ShortMsg = bstr(msg->shortmsg);
            msg2->LongMsg = bstr(msg->longmsg);
            msg2->LongMsgFormatted = bstr(msg->longmsg_formatted);
            msg2->Attachments = array_from_C<Blob, bloblist_t>(msg->attachments);
            if (msg->sent)
                msg2->Sent = mktime(msg->sent);
            if (msg->recv)
                msg2->Recv = mktime(msg->recv);
            msg2->From = identity_s(msg->from);
            msg2->To = array_from_C<pEpIdentity, identity_list>(msg->to);
            msg2->RecvBy = identity_s(msg->recv_by);
            msg2->Cc = array_from_C<pEpIdentity, identity_list>(msg->cc);
            msg2->Bcc = array_from_C<pEpIdentity, identity_list>(msg->bcc);
            msg2->ReplyTo = array_from_C<pEpIdentity, identity_list>(msg->reply_to);
            msg2->References = string_array(msg->references);
            msg2->Keywords = string_array(msg->keywords);
            msg2->Comments = bstr(msg->comments);
            msg2->OptFields = array_from_C<StringPair, stringpair_list_t>(msg->opt_fields);
        }

        char * str(BSTR s)
        {
            string str = utf8_string(s);
            char *_s = _strdup(str.c_str());
            if (_s == NULL)
                throw bad_alloc();

            return _s;
        }

        void clear_blob(Blob& b)
        {
            SysFreeString(b.Filename);
            SysFreeString(b.MimeType);
            SafeArrayDestroy(b.value);
            memset(&b, 0, sizeof(Blob));
        }

        bloblist_t *bloblist(SAFEARRAY *sa)
        {
            if (sa == NULL)
                return NULL;

            LONG lbound, ubound;
            SafeArrayGetLBound(sa, 1, &lbound);
            SafeArrayGetUBound(sa, 1, &ubound);

            size_t size = ubound - lbound + 1;
            if (size <= 0)
                return NULL;

            bloblist_t *bl = new_bloblist(NULL, 0, NULL, NULL);
            if (bl == NULL)
                throw bad_alloc();

            bloblist_t *_bl = bl;
            for (LONG i = lbound; i <= ubound; i++) {
                Blob b;
                memset(&b, 0, sizeof(Blob));
                SafeArrayGetElement(sa, &i, &b);

                LONG _lbound, _ubound;
                SafeArrayGetLBound(b.value, 1, &_lbound);
                SafeArrayGetUBound(b.value, 1, &_ubound);
                size_t size = _ubound - _lbound + 1;

                char *buffer;
                if (size) {
                    buffer = (char *) calloc(1, size);
                    if (buffer == NULL)
                        throw bad_alloc();

                    char *data;

                    SafeArrayAccessData(b.value, (void **) &data);
                    memcpy(buffer, data, size);
                    SafeArrayUnaccessData(sa);
                }
                else {
                    buffer = _strdup("");
                    if (buffer == NULL)
                        throw bad_alloc();

                }
                _bl = bloblist_add(_bl, buffer, size, str(b.MimeType), str(b.Filename));
                if (_bl == NULL) {
                    free(buffer);
                    clear_blob(b);
                    free_bloblist(bl);
                    throw bad_alloc();
                }

                clear_blob(b);
            }

            return bl;
        }

        identity_list *identities(SAFEARRAY * sa)
        {
            if (sa == NULL)
                return NULL;

            LONG lbound, ubound;
            SafeArrayGetLBound(sa, 1, &lbound);
            SafeArrayGetUBound(sa, 1, &ubound);

            size_t size = ubound - lbound + 1;
            if (size <= 0)
                return NULL;

            identity_list *il = new_identity_list(NULL);

            identity_list *_il = il;
            for (LONG i = lbound; i <= ubound; i++) {
                pEpIdentity s;
                memset(&s, 0, sizeof(pEpIdentity));
                SafeArrayGetElement(sa, &i, &s);

                pEp_identity *ident;
                try {
                    ident = new_identity(&s);
                }
                catch (bad_alloc&) {
                    clear_identity_s(s);
                    throw bad_alloc();
                }

                clear_identity_s(s);

                _il = identity_list_add(_il, ident);
                if (_il == NULL) {
                    free_identity_list(il);
                    throw bad_alloc();
                }
            }

            return il;
        }

        stringpair_t *new_stringpair(StringPair *fld)
        {
			stringpair_t *pair;

			if (!fld) {
				pair = ::new_stringpair(NULL, NULL);
			}
			else {
				pair = ::new_stringpair(str(fld->Name), str(fld->Value));
			}
            if (pair == NULL)
                throw bad_alloc();

            return pair;
        }

        void clear_opt_field(StringPair& f)
        {
            SysFreeString(f.Name);
            SysFreeString(f.Value);
            memset(&f, 0, sizeof(StringPair));
        }

        stringpair_list_t *stringpair_list(SAFEARRAY * sa)
        {
            if (sa == NULL)
                return NULL;

            LONG lbound, ubound;
            SafeArrayGetLBound(sa, 1, &lbound);
            SafeArrayGetUBound(sa, 1, &ubound);

            size_t size = ubound - lbound + 1;
            if (size <= 0)
                return NULL;

            stringpair_list_t *il = new_stringpair_list(NULL);

            stringpair_list_t *_il = il;
            for (LONG i = lbound; i <= ubound; i++) {
                StringPair s;
                memset(&s, 0, sizeof(StringPair));
                SafeArrayGetElement(sa, &i, &s);

                stringpair_t *pair;
                try {
                    pair = new_stringpair(&s);
                }
                catch (bad_alloc&) {
                    clear_opt_field(s);
                    throw bad_alloc();
                }

                clear_opt_field(s);

                _il = stringpair_list_add(_il, pair);
                if (_il == NULL) {
                    free_stringpair_list(il);
                    throw bad_alloc();
                }
            }

            return il;
        }
        
        ::message * text_message_to_C(TextMessage *msg)
        {
            assert(msg);
			if (!msg)
				throw invalid_argument("msg");

            ::message * msg2 = new_message((PEP_msg_direction) msg->Dir);
            if (msg2 == NULL)
                throw bad_alloc();

            msg2->id = str(msg->Id);
            msg2->shortmsg = str(msg->ShortMsg);
            msg2->longmsg = str(msg->LongMsg);
            msg2->longmsg_formatted = str(msg->LongMsgFormatted);
            msg2->attachments = bloblist(msg->Attachments);
            msg2->sent = new_timestamp(msg->Sent);
            msg2->recv = new_timestamp(msg->Recv);
            msg2->from = new_identity(&msg->From);
            msg2->to = identities(msg->To);
            msg2->recv_by = new_identity(&msg->RecvBy);
            msg2->cc = identities(msg->Cc);
            msg2->bcc = identities(msg->Bcc);
            msg2->reply_to = identities(msg->ReplyTo);
            msg2->references = new_stringlist(msg->References);
            msg2->keywords = new_stringlist(msg->Keywords);
            msg2->comments = str(msg->Comments);
            msg2->opt_fields = stringpair_list(msg->OptFields);

            return msg2;
        }

		void opt_field_array_from_C(stringpair_list_t* spair_list, LPSAFEARRAY* pair_list_out) {
			assert(spair_list);
			assert(pair_list_out);
			
			if (!spair_list)
				return;

			*pair_list_out = array_from_C<StringPair, stringpair_list_t>(spair_list);
		}

		void clear_opt_field_array(LPSAFEARRAY* opt_field_array) {
			if (opt_field_array){
				SafeArrayDestroy(*opt_field_array);
				*opt_field_array = NULL;
			}
		}
    }
}
