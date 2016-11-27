#pragma once

namespace JF
{
	//***************************************************************************//
	//							범용 Exception									 //
	//***************************************************************************//
	class JFCException
	{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
	public:
		JFCException()				
		{
		}
		JFCException(const std::wstring& _exceptionMessage)
			: mMessage(_exceptionMessage)
		{
		}

	//=============================================================================
	// Public Methods)
	//=============================================================================
	public:
		const std::wstring& GetMessage() const throw()
		{
			return mMessage;
		}

		void ShowErrorMessage() const throw ()
		{
			// 임시로 Windows Box 사용
			MessageBox(NULL, mMessage.c_str(), L"Error", MB_OK | MB_ICONERROR);
		}

	//=============================================================================
	// Protected Members)
	//=============================================================================
	protected:
		std::wstring	mMessage;
	};

	//***************************************************************************//
	//							윈도우용 Exception								 //
	//***************************************************************************//
	class JFCWindowsException : public JFCException
	{
	//=============================================================================
	// Constructor/Destructor)
	//=============================================================================
	public:
		JFCWindowsException(DWORD _code)
			: mErrorCode(_code)
		{
			WCHAR errorString[MAX_PATH];
			::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
				0,
				mErrorCode,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				errorString,
				MAX_PATH,
				NULL);

			mMessage = L"Windows Error: ";
			mMessage += errorString;
		}

		// Retrieve the error code
		DWORD GetErrorCode() const throw ()
		{
			return mErrorCode;
		}

	protected:
		DWORD	mErrorCode;
	};

	//***************************************************************************//
	//							Direcx용 Exception								 //
	//***************************************************************************//
	class JFCDirectXException : public JFCException
	{

	public:

		// Obtains a string for the specified HRESULT error code
		JFCDirectXException(HRESULT _hresult)
			: mErrorCode(_hresult)
		{
			mMessage = L"DirectX Error: ";
			mMessage += mErrorCode;
		}

		JFCDirectXException(HRESULT _hresult, LPCWSTR _errorMsg)
			: mErrorCode(_hresult)
		{
			mMessage = L"DirectX Error: ";
			mMessage += _errorMsg;
		}

		// Retrieve the error code
		HRESULT GetErrorCode() const throw ()
		{
			return mErrorCode;
		}

	protected:

		HRESULT		mErrorCode;		// The DX error code
	};
}