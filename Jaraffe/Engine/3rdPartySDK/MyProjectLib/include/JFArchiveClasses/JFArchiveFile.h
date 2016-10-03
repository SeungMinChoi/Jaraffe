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
// JFArchive::CFile
//
// 1. JFArchive::CFile란!
//    1) File을 Access하기 위한 Class이다.
//    2) 기본적으로 IJFArchive를 상속받은 Class이다.
//
// 2. JFArchive::CFile Function
//    1) Open/Close	File을 열고 다는 함수이다.
//    2) Read/Write	열린 파일을 Read/Write를 수행하는 함수이다.
//
// 3. 주의 사항
//	  1) Open이 되지 않았을 때는 기본적으로 return값이 false로 돌아온다.
//	  2) 하지만 Read와 Write의 실패의 경우 Exception을 던지믈 그것을 주의해야 한다.
//
//-----------------------------------------------------------------------------
#define	MAX_LENGTH_OF_FILENAME	1024

namespace JFArchive
{


}