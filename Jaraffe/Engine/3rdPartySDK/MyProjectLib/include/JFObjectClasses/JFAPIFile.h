//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 8.0 / Release 2015.01.05                        *
//*                                                                           *
//*                              Execute Classes                              *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangduck@cgcii.co.kr         *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                 ¨Ï 2016 Cho Sanghyun All right reserved.                  *
//*                          http://www.CGCII.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once

typedef	HANDLE		CGHANDLE;
typedef	HANDLE		FILE_HANDLE;
typedef	HANDLE		THREAD_HANDLE;
const FILE_HANDLE	INVALID_FILE_HANDLE		 = INVALID_HANDLE_VALUE;
const HANDLE		INVALID_CGHANDLE_VALUE	 = INVALID_HANDLE_VALUE;

enum class eFILE_OPERATION : unsigned int
{
	NONE			 = 0,
	READ			 = 1,
	WRITE			 = 2,
	APPEND			 = 3,
	READ_ASYNC		 = 4,
	WRITE_ASYNC		 = 5,
	APPEND_ASYNC	 = 6,
	MAX
};

enum class eFILE_ORIGIN : int
{
	BEGIN			 = 0,
	CURRENT			 = 1,
	END				 = 2
};

enum class eFILE_LOCATION : unsigned int
{
	NONE			 = 0,
	NOW				 = 1,
	RESOURCE		 = 2,
	SYSTEM			 = 4
};
inline eFILE_LOCATION	operator &	(const eFILE_LOCATION& a, const eFILE_LOCATION& b)	{ return eFILE_LOCATION(((unsigned int)a) & (unsigned int)b); }
inline eFILE_LOCATION	operator &	(const eFILE_LOCATION& a, unsigned int b)			{ return eFILE_LOCATION(((unsigned int)a) & (unsigned int)b); }
inline eFILE_LOCATION	operator |	(const eFILE_LOCATION& a, const eFILE_LOCATION& b)	{ return eFILE_LOCATION(((unsigned int)a) | (unsigned int)b); }
inline eFILE_LOCATION	operator |	(const eFILE_LOCATION& a, unsigned int b)			{ return eFILE_LOCATION(((unsigned int)a) | (unsigned int)b); }


namespace JFAPI
{
	namespace FILE
	{
		FILE_HANDLE		Open			(const wchar_t* _FileName, eFILE_OPERATION _Operation, eFILE_LOCATION _FileLocation=eFILE_LOCATION::NOW);
		FILE_HANDLE		Open			(const char* _FileName, eFILE_OPERATION _Operation, eFILE_LOCATION _FileLocation=eFILE_LOCATION::NOW);
		void			Close			(FILE_HANDLE _hFile);
		size_t			Read			(FILE_HANDLE _hFile, size_t _size, void* _Data);
		size_t			Write			(FILE_HANDLE _hFile, size_t _size, const void* _Data);
		size_t			Seek			(FILE_HANDLE _hFile, size_t _Offset, eFILE_ORIGIN _Origin=eFILE_ORIGIN::BEGIN);
		size_t			GetLength		(FILE_HANDLE _hFile);
	}
}