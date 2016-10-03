#pragma once

namespace JF
{
	namespace JFStudy
	{
		int BoyerMoore( char* _pText,  int _nTextSize,  int _nStart,  char* _pPattern,  int _nPatternSize);

		void BuildBCT( char* _pPattern,  int _nPatternSize,  int* _pBCT);
		void BuildGST( char* _pPattern,  int _nPatternSize,  int* _pSuffix,  int* _pGST);
		
		int Max( int _nA,  int _nB);
	}
}