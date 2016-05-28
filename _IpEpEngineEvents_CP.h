#pragma once

template<class T>
class CProxy_IpEpEngineEvents :
	public ATL::IConnectionPointImpl<T, &__uuidof(_IpEpEngineEvents)>
{
public:

	/* Test code - remove before shipping 
	HRESULT Fire_TestEvent(LONG test, BSTR testtest)
	{
		HRESULT hr = S_OK;
		T * pThis = static_cast<T *>(this);
		int cConnections = m_vec.GetSize();

		for (int iConnection = 0; iConnection < cConnections; iConnection++)
		{
			pThis->Lock();
			CComPtr<IUnknown> punkConnection = m_vec.GetAt(iConnection);
			pThis->Unlock();

			IDispatch * pConnection = static_cast<IDispatch *>(punkConnection.p);

			if (pConnection)
			{
				CComVariant avarParams[2];
				avarParams[1] = test;
				avarParams[1].vt = VT_I4;
				avarParams[0] = testtest;
				avarParams[0].vt = VT_BSTR;
				CComVariant varResult;

				DISPPARAMS params = { avarParams, NULL, 2, 0 };
				hr = pConnection->Invoke(1, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &params, &varResult, NULL, NULL);
			}
		}
		return hr;
	}*/
};

