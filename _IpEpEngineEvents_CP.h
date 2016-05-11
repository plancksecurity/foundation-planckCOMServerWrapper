#pragma once

template<class T>
class CProxy_IpEpEngineEvents :
	public ATL::IConnectionPointImpl<T, &__uuidof(_IpEpEngineEvents)>
{
public:
	HRESULT Fire_messageToSend(text_message * msg)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int cConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < cConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			_IpEpEngineEvents * pConnection = static_cast<_IpEpEngineEvents *>(punkConnection.p);

			if (pConnection)
			{
				hr = pConnection->messageToSend(msg);
			}
		}
		return hr;
	}
	HRESULT Fire_showHandshake(pEp_identity_s * self, pEp_identity_s * partner, sync_handshake_result * result)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int cConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < cConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			_IpEpEngineEvents * pConnection = static_cast<_IpEpEngineEvents *>(punkConnection.p);

			if (pConnection)
			{
				hr = pConnection->showHandshake(self, partner, result);
			}
		}
		return hr;
	}
};

