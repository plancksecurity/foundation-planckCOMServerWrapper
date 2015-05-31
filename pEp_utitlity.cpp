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

        template< class T2, class T > T2 from_C(T *tl);

        template<> BSTR from_C< BSTR, char >(char *s)
        {
            if (s)
                return utf16_bstr(s).Detach();
            else
                return _bstr_t(L"").Detach();
        }

        inline BSTR bstr(char *s)
        {
            return from_C< BSTR, char >(s);
        }

        template<> blob *from_C< blob *, bloblist_t >(bloblist_t *tl)
        {
            assert(tl && tl->value);

            CComSafeArray<BYTE> sa;
            sa.Create(tl->size);

            memcpy(sa.m_psa->pvData, tl->value, tl->size);

            blob *_blob = new blob();

            _blob->value = sa.Detach();
            _blob->mime_type = bstr(tl->mime_type);
            _blob->filename = bstr(tl->filename);

            return _blob;
        }

        template< class T > int length(T *);

        template< class T2, class T > SAFEARRAY * array_from_C(T *tl)
        {
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

        template<> pEp_identity_s from_C< pEp_identity_s, pEp_identity >(pEp_identity *tl)
        {
            pEp_identity_s _ident;
            copy_identity(&_ident, tl);
            return _ident;
        }

        pEp_identity_s identity_s(pEp_identity *ident)
        {
            return from_C< pEp_identity_s, pEp_identity >(ident);
        }

        template<> pEp_identity_s *from_C< pEp_identity_s *, identity_list >(identity_list *il)
        {
            pEp_identity_s *ident = new pEp_identity_s();
            copy_identity(ident, il->ident);
            return ident;
        }

        template<> opt_field *from_C< opt_field *, stringpair_list_t >(stringpair_list_t * sp)
        {
            opt_field *fld = new opt_field();
            fld->name = bstr(sp->value->key);
            fld->value = bstr(sp->value->value);
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

        void text_message_from_C(text_message *msg2, ::message *msg)
        {
            assert(msg2);
            assert(msg);

            msg2->dir = (pEp_msg_direction) msg->dir;
            msg2->id = bstr(msg->id);
            msg2->shortmsg = bstr(msg->shortmsg);
            msg2->longmsg = bstr(msg->longmsg);
            msg2->longmsg_formatted = bstr(msg->longmsg_formatted);
            msg2->attachments = array_from_C<blob, bloblist_t>(msg->attachments);
            msg2->sent = mktime(msg->sent);
            msg2->recv = mktime(msg->recv);
            msg2->from = identity_s(msg->from);
            msg2->to = array_from_C<pEp_identity_s, identity_list>(msg->to);
            msg2->recv_by = identity_s(msg->recv_by);
            msg2->cc = array_from_C<pEp_identity_s, identity_list>(msg->cc);
            msg2->bcc = array_from_C<pEp_identity_s, identity_list>(msg->bcc);
            msg2->reply_to = array_from_C<pEp_identity_s, identity_list>(msg->reply_to);
            msg2->references = string_array(msg->references).Detach();
            msg2->keywords = string_array(msg->keywords).Detach();
            msg2->comments = bstr(msg->comments);
            msg2->opt_fields = array_from_C<opt_field, stringpair_list_t>(msg->opt_fields);
        }

        char * str(BSTR s)
        {
            string str = utf8_string(s);
            char *_s = _strdup(str.c_str());
            if (_s == NULL)
                throw bad_alloc();

            return _s;
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
                blob b;
                memset(&b, 0, sizeof(blob));
                SafeArrayGetElement(sa, &i, &b);

                LONG _lbound, _ubound;
                SafeArrayGetLBound(b.value, 1, &_lbound);
                SafeArrayGetUBound(b.value, 1, &_ubound);
                size_t size = _ubound - _lbound + 1;

                char *buffer = (char *) malloc(size);
                if (buffer == NULL)
                    throw bad_alloc();

                char *data;

                SafeArrayAccessData(b.value, (void **) &data);
                memcpy(buffer, data, size);
                SafeArrayUnaccessData(sa);

                _bl = bloblist_add(_bl, buffer, size, str(b.mime_type), str(b.filename));
                if (_bl == NULL) {
                    IRecordInfo *ri = getRecordInfo<blob>();
                    ri->RecordClear(&b);

                    free_bloblist(bl);
                    free(buffer);
                    throw bad_alloc();
                }

                IRecordInfo *ri = getRecordInfo<blob>();
                ri->RecordClear(&b);
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
                pEp_identity_s s;
                memset(&s, 0, sizeof(s));
                SafeArrayGetElement(sa, &i, &s);

                pEp_identity *ident;
                try {
                    ident = new_identity(&s);
                }
                catch (bad_alloc&) {
                    IRecordInfo *ri = getRecordInfo<pEp_identity_s>();
                    ri->RecordClear(&s);

                    throw bad_alloc();
                }

                IRecordInfo *ri = getRecordInfo<pEp_identity_s>();
                ri->RecordClear(&s);

                _il = identity_list_add(_il, ident);
                if (_il == NULL) {
                    free_identity_list(il);
                    throw bad_alloc();
                }
            }

            return il;
        }

        stringpair_t *new_stringpair(opt_field *fld)
        {
            stringpair_t *pair = ::new_stringpair(str(fld->name), str(fld->value));
            if (pair == NULL)
                throw bad_alloc();

            return pair;
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
                opt_field s;
                memset(&s, 0, sizeof(opt_field));
                SafeArrayGetElement(sa, &i, &s);

                stringpair_t *pair;
                try {
                    pair = new_stringpair(&s);
                }
                catch (bad_alloc&) {
                    IRecordInfo *ri = getRecordInfo<opt_field>();
                    ri->RecordClear(&s);

                    throw bad_alloc();
                }

                IRecordInfo *ri = getRecordInfo<opt_field>();
                ri->RecordClear(&s);

                _il = stringpair_list_add(_il, pair);
                if (_il == NULL) {
                    free_stringpair_list(il);
                    throw bad_alloc();
                }
            }

            return il;
        }
        
        ::message * text_message_to_C(text_message *msg)
        {
            assert(msg);

            ::message * msg2 = new_message((PEP_msg_direction) msg->dir, NULL, NULL, NULL);
            if (msg2 == NULL)
                throw bad_alloc();

            msg2->id = str(msg->id);
            msg2->shortmsg = str(msg->shortmsg);
            msg2->longmsg = str(msg->longmsg);
            msg2->longmsg_formatted = str(msg->longmsg_formatted);
            msg2->attachments = bloblist(msg->attachments);
            msg2->sent = new_timestamp(msg->sent);
            msg2->recv = new_timestamp(msg->recv);
            msg2->from = new_identity(&msg->from);
            msg2->to = identities(msg->to);
            msg2->recv_by = new_identity(&msg->recv_by);
            msg2->cc = identities(msg->cc);
            msg2->bcc = identities(msg->bcc);
            msg2->reply_to = identities(msg->reply_to);
            msg2->references = new_stringlist(msg->references);
            msg2->keywords = new_stringlist(msg->keywords);
            msg2->comments = str(msg->comments);
            msg2->opt_fields = stringpair_list(msg->opt_fields);

            return msg2;
        }
    }
}
