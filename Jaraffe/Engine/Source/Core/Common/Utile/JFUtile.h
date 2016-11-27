#pragma once

namespace JF
{
	namespace Utile
	{
		// Throws a DXException on failing HRESULT
		inline void DXCall(HRESULT hr)
		{
			if (FAILED(hr))
			{
				_ASSERT(false);
				throw JF::JFCDirectXException(hr);
			}
		}

		// Converts a number to a string
		template<typename T> inline std::wstring ToString(const T& val)
		{
			std::wostringstream stream;
			if (!(stream << val))
				throw JF::JFCException(L"Error converting value to string");
			return stream.str();
		}
	}
}