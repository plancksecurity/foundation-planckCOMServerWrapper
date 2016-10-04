#include "stdafx.h"
#include "pEp_utility.h"

using namespace ATL;

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
            comm_type = (pEpComType) _ident->comm_type;
            lang = _ident->lang;
        }

        pEp_identity_cpp::pEp_identity_cpp(const pEpIdentity *_ident)
            : me(false)
        {
            if (_ident->address)
                address = utf8_string(_ident->address);
            if (_ident->fpr)
                fpr = utf8_string(_ident->fpr);
            if (_ident->userId)
                user_id = utf8_string(_ident->userId);
            if (_ident->username)
                username = utf8_string(_ident->username);
            comm_type = _ident->commType;
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

        pEpIdentity * pEp_identity_cpp::to_pEp_identity_s()
        {
            pEpIdentity *_ident = (pEpIdentity *) calloc(1, sizeof(pEpIdentity));
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->address = utf16_bstr(this->address);
            _ident->commType = this->comm_type;
            _ident->fpr = utf16_bstr(this->fpr);
            _ident->lang = utf16_bstr(this->lang);
            _ident->username = utf16_bstr(this->username);
            _ident->userId = utf16_bstr(this->user_id);

            return _ident;
        }

        void copy_identity(pEpIdentity * ident_s, const pEp_identity * ident)
        {
            assert(ident_s);

            ::memset(ident_s, 0, sizeof(pEpIdentity));
            if (ident) {
                if (ident->address)
                    ident_s->address = utf16_bstr(ident->address);
                if (ident->fpr)
                    ident_s->fpr = utf16_bstr(ident->fpr);
                if (ident->user_id)
                    ident_s->userId = utf16_bstr(ident->user_id);
                if (ident->username)
                    ident_s->username = utf16_bstr(ident->username);
                ident_s->commType = (pEpComType) ident->comm_type;
                if (ident->lang)
                    ident_s->lang = utf16_bstr(ident->lang);
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
            if (ident->userId)
                _user_id = utf8_string(ident->userId);
            if (ident->username)
                _username = utf8_string(ident->username);

            _ident = ::new_identity(_address.c_str(), _fpr.c_str(), _user_id.c_str(), _username.c_str());
            assert(_ident);
            if (_ident == NULL)
                throw bad_alloc();

            _ident->comm_type = (PEP_comm_type) ident->commType;

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

        template< class T2, class T > T2 from_C(T *tl);

        BSTR bstr(char *s)
        {
            if (s == NULL)
                return _bstr_t(L"").Detach();

            return utf16_bstr(s);
        }

        template<> Blob *from_C< Blob *, bloblist_t >(bloblist_t *tl)
        {
            CComSafeArray<BYTE> sa;
            sa.Create(tl->size);

            if (tl->size) {
                char *data;
                SafeArrayAccessData(sa, (void **) &data);
                memcpy(data, tl->value, tl->size);
                SafeArrayUnaccessData(sa);
            }

            Blob *_blob = new Blob();

            _blob->value = sa.Detach();
            _blob->mimeType = bstr(tl->mime_type);
            _blob->filename = bstr(tl->filename);

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
            SysFreeString(ident.address);
            SysFreeString(ident.fpr);
            SysFreeString(ident.lang);
            SysFreeString(ident.username);
            SysFreeString(ident.userId);

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
                fld->name = bstr(sp->value->key);
                fld->value = bstr(sp->value->value);
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
            SysFreeString(msg->id);
            SysFreeString(msg->shortmsg);
            SysFreeString(msg->longmsg);
            SysFreeString(msg->longmsgFormatted);
            SafeArrayDestroy(msg->attachments);
            clear_identity_s(msg->from);
            SafeArrayDestroy(msg->to);
            clear_identity_s(msg->recvBy);
            SafeArrayDestroy(msg->cc);
            SafeArrayDestroy(msg->bcc);
            SafeArrayDestroy(msg->replyTo);
            SafeArrayDestroy(msg->references);
            SafeArrayDestroy(msg->keywords);
            SysFreeString(msg->comments);
            SafeArrayDestroy(msg->optFields);

            memset(msg, 0, sizeof(TextMessage));
        }

        void text_message_from_C(TextMessage *msg2, const ::message *msg)
        {
            assert(msg2);
            assert(msg);

            clear_text_message(msg2);

            msg2->dir = (pEpMsgDirection) msg->dir;
            msg2->id = bstr(msg->id);
            msg2->shortmsg = bstr(msg->shortmsg);
            msg2->longmsg = bstr(msg->longmsg);
            msg2->longmsgFormatted = bstr(msg->longmsg_formatted);
            msg2->attachments = array_from_C<Blob, bloblist_t>(msg->attachments);
            if (msg->sent)
                msg2->sent = mktime(msg->sent);
            if (msg->recv)
                msg2->recv = mktime(msg->recv);
            msg2->from = identity_s(msg->from);
            msg2->to = array_from_C<pEpIdentity, identity_list>(msg->to);
            msg2->recvBy = identity_s(msg->recv_by);
            msg2->cc = array_from_C<pEpIdentity, identity_list>(msg->cc);
            msg2->bcc = array_from_C<pEpIdentity, identity_list>(msg->bcc);
            msg2->replyTo = array_from_C<pEpIdentity, identity_list>(msg->reply_to);
            msg2->references = string_array(msg->references);
            msg2->keywords = string_array(msg->keywords);
            msg2->comments = bstr(msg->comments);
            msg2->optFields = array_from_C<StringPair, stringpair_list_t>(msg->opt_fields);
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
            SysFreeString(b.filename);
            SysFreeString(b.mimeType);
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
                    buffer = (char *) malloc(size);
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
                _bl = bloblist_add(_bl, buffer, size, str(b.mimeType), str(b.filename));
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
            stringpair_t *pair = ::new_stringpair(str(fld->name), str(fld->value));
            if (pair == NULL)
                throw bad_alloc();

            return pair;
        }

        void clear_opt_field(StringPair& f)
        {
            SysFreeString(f.name);
            SysFreeString(f.value);
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

            ::message * msg2 = new_message((PEP_msg_direction) msg->dir);
            if (msg2 == NULL)
                throw bad_alloc();

            msg2->id = str(msg->id);
            msg2->shortmsg = str(msg->shortmsg);
            msg2->longmsg = str(msg->longmsg);
            msg2->longmsg_formatted = str(msg->longmsgFormatted);
            msg2->attachments = bloblist(msg->attachments);
            msg2->sent = new_timestamp(msg->sent);
            msg2->recv = new_timestamp(msg->recv);
            msg2->from = new_identity(&msg->from);
            msg2->to = identities(msg->to);
            msg2->recv_by = new_identity(&msg->recvBy);
            msg2->cc = identities(msg->cc);
            msg2->bcc = identities(msg->bcc);
            msg2->reply_to = identities(msg->replyTo);
            msg2->references = new_stringlist(msg->references);
            msg2->keywords = new_stringlist(msg->keywords);
            msg2->comments = str(msg->comments);
            msg2->opt_fields = stringpair_list(msg->optFields);

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
			SafeArrayDestroy(*opt_field_array);
			//memset(*opt_field_array, 0, sizeof(SAFEARRAY*));
			*opt_field_array = NULL;
		}
    }
}
