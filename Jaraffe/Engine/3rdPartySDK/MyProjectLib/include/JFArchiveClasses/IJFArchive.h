//*****************************************************************************
//*                                                                           *
//*                        Choi SeungMin Game Classes                         *
//*                       Ver 1.0 / Release 2016.10.03                        *
//*                                                                           *
//*                             Archive Classes                               *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// 1. IJFArchive란!
//    1) I/O를 통일하여 처리하기 위한 Archive Interface
//
// 2. ICGArchive의 핵심! Function의 기능 설명
//    1) int ProcessRead(void* _pData, size_t _Bytes)
//       - 데이터를 읽어들이는 기능을 재정의하는 함수.
//       - file의 경우 일반적으로 ReadFile을 사용하여 구현한다.
//
//    2) int ProcessWrite(const void* _pData, int _Bytes)
//       - 데이터를 쓰는 기능을 재정의하는 함수이다.
//       - file의 경우 일반적으로 WriteFile을 사용하여 구현한다.
//
//
//-----------------------------------------------------------------------------
#define	JFARCHIVE_STATUS_LOADING		0x01
#define	JFARCHIVE_STATUS_SAVING			0x02
#define	JFARCHIVE_STATUS_PRE_SAVING		0x03
#define	JFARCHIVE_STATUS_POST_LOADING	0x04

class IJFArchive
{

};
