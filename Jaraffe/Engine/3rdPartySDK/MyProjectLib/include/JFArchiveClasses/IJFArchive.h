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
// 1. IJFArchive��!
//    1) I/O�� �����Ͽ� ó���ϱ� ���� Archive Interface
//
// 2. ICGArchive�� �ٽ�! Function�� ��� ����
//    1) int ProcessRead(void* _pData, size_t _Bytes)
//       - �����͸� �о���̴� ����� �������ϴ� �Լ�.
//       - file�� ��� �Ϲ������� ReadFile�� ����Ͽ� �����Ѵ�.
//
//    2) int ProcessWrite(const void* _pData, int _Bytes)
//       - �����͸� ���� ����� �������ϴ� �Լ��̴�.
//       - file�� ��� �Ϲ������� WriteFile�� ����Ͽ� �����Ѵ�.
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
