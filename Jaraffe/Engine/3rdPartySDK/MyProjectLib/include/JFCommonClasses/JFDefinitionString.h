#pragma once

//-----------------------------------------------------------------------------
//                                                                            
// Definitions for String
//                                                                            
//                                                                            
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>	// C++ STL string
#include <string.h>	// C++ Standard string functions
#include <cstdlib> 
#include <locale>
#include <cwchar>

#ifdef _MSC_VER
#include <codecvt>
#include "Shlwapi.h"
#endif

#if defined(_MSC_VER)
#pragma warning(disable:28313)
#include <tchar.h>
#pragma warning(default:28131)
#endif

inline wchar_t* CONVERT_STRING(_In_z_ const char* _strSource, wchar_t* _strDest, size_t _Size=1024)
{
	// Check) 
	RETURN_IF(_strSource==nullptr, nullptr);

#if defined(_WIN32)
	#if defined(_USE_CHAR_STRING)
		wcstombs_s(nullptr, _strDest, _Size, _strSource, _Size);
	#elif defined(_USE_WCHAR_STRING)
		mbstowcs_s(nullptr, _strDest, _Size, _strSource, _Size);
	#endif
#else
	#if defined(_USE_CHAR_STRING)
		std::wcstombs(_strDest, _strSource, _Size);
	#elif defined(_USE_WCHAR_STRING)
		std::mbstowcs(_strDest, _strSource, _Size);
	#endif
#endif
	// Return) 
	return	_strDest;
}