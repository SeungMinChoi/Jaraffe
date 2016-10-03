#pragma once

//----------------------------------------------------------------------------
// Classes
//----------------------------------------------------------------------------
#include "JFStudyClasses/JFLinkedList.h"
#include "JFStudyClasses/JFRedBlackTree.h"
#include "JFStudyClasses/JFPriorityQueue.h"
#include "JFStudyClasses/JFDivisionHashTable.h"
#include "JFStudyClasses/JFDigitsFolding.h"
#include "JFStudyClasses/JFHuffman.h"

//----------------------------------------------------------------------------
// Utiles
//----------------------------------------------------------------------------
#include "JFStudyClasses/JFSortUtiles.h"
#include "JFStudyClasses/JFSearchUtiles.h"
#include "JFStudyClasses/JFBoyerMoore.h"
#include "JFStudyClasses/JFUtileFuntions.h"

//----------------------------------------------------------------------------
//
// Libraries
//
//----------------------------------------------------------------------------
#if defined(_MSC_VER)

	#if !defined(_MSC_PLATFORM_TOOLSET)
		#if _MSC_VER>=_MSC_VER_2015
			#define	_MSC_PLATFORM_TOOLSET	140
		#elif _MSC_VER>=_MSC_VER_2013
			#define	_MSC_PLATFORM_TOOLSET	120
		#elif _MSC_VER>=_MSC_VER_2012
			#define	_MSC_PLATFORM_TOOLSET	110
		#elif _MSC_VER>=_MSC_VER_2010
			#define	_MSC_PLATFORM_TOOLSET	100
		#elif _MSC_VER>=_MSC_VER_2008
			#define	_MSC_PLATFORM_TOOLSET	90
		#else
			#define	_MSC_PLATFORM_TOOLSET	80
		#endif
	#endif

	#if !defined(_LIB) || defined(_CONSOLE)

	//----------------------------------------------------------------------------
	// * VS2015 Lib 
	//----------------------------------------------------------------------------
	#if _MSC_PLATFORM_TOOLSET>=140

	#if defined(_M_X64)
		//1) DLL version�� ��
		#ifdef _DLL 
			#ifdef _DEBUG
				#pragma comment (lib,"JFStudyClasses_x64_v140_Debug_DLL.lib")
			#else
				#pragma comment (lib,"JFStudyClasses_x64_v140_Release_DLL.lib")
			#endif

		//2) DLL�� �ƴ� ��
		#else
			#ifdef _DEBUG
				#pragma comment (lib,"JFStudyClasses_x64_v140_Debug.lib")
			#else
				#pragma comment (lib,"JFStudyClasses_x64_v140_Release.lib")
			#endif
		#endif
	#elif defined(_M_IX86)
		//1) DLL version�� ��
		#ifdef _DLL 
			#ifdef _DEBUG
				#pragma comment (lib,"JFStudyClasses_x86_v140_Debug_DLL.lib")
			#else
				#pragma comment (lib,"JFStudyClasses_x86_v140_Release_DLL.lib")
			#endif

		//2) DLL�� �ƴ� ��
		#else
			#ifdef _DEBUG
				#pragma comment (lib,"JFStudyClasses_x86_v140_Debug.lib")
			#else
				#pragma comment (lib,"JFStudyClasses_x86_v140_Release.lib")
			#endif
		#endif
	#else
		#error	"[JF] Not supported Platform"
	#endif

	#else
		#error "[JF] Not supported platform"
	#endif

	#endif
#endif