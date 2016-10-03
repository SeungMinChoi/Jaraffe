#pragma once

namespace JF
{
	namespace JFSearchUtiles
	{
		//----------------------------------------------------------------------------
		// BinarySearch
		//----------------------------------------------------------------------------
		template<typename TData, typename TTarget>
		TData* BinarySearch(_Inout_ TData _SourceList[], _In_ int _nSize, _In_ TTarget _Target)
		{
			int nLeft	= 0;
			int nRight	= _nSize - 1;
			int nMid	= 0;

			while (nLeft <= nRight)
			{
				nMid = (nLeft + nRight) / 2;

				if (_SourceList[nMid] == _Target )
					return &_SourceList[nMid];
				else if (_SourceList[nMid] < _Target)
					nLeft = nMid + 1;
				else
					nRight = nMid - 1;
			}

			return nullptr;

			// bsearch();
		}

		//----------------------------------------------------------------------------
		// LCS
		//----------------------------------------------------------------------------
		struct LCSTable
		{
			int** ppData;
		};

		int LCS(_In_ char* _pX, _In_ char* _pY, _In_ int _nI, _In_ int _nJ, _Inout_ LCSTable* _pTable )
		{
			// Declear)
			int m = 0;
			int n = 0;

			// Reset)
			for (m = 0; m <= _nI; ++m)
				_pTable->ppData[m][0] = 0;
			for (n = 0; n <= _nJ; ++n)
				_pTable->ppData[0][n] = 0;

			for (m = 1; m <= _nI; ++m)
			{
				for (n = 1; n <= _nJ; ++n)
				{
					if (_pX[m - 1] == _pY[n - 1])
					{
						_pTable->ppData[m][n] = _pTable->ppData[m - 1][n - 1] + 1;
					}
					else
					{
						if (_pTable->ppData[m][n - 1] >= _pTable->ppData[m - 1][n])
							_pTable->ppData[m][n] = _pTable->ppData[m][n - 1];
						else
							_pTable->ppData[m][n] = _pTable->ppData[m - 1][n];
					}
				}
			}

			return _pTable->ppData[_nI][_nJ];
		}

		void LCS_TraceBack(_In_ char* _pX, _In_ char* _pY, _In_ int _nM, _In_ int _nN, _In_ LCSTable* _pTable, _Inout_ char* _pLCS)
		{
			if (_nM == 0 || _nN == 0)
				return;

			if (_pTable->ppData[_nM][_nN] > _pTable->ppData[_nM][_nN - 1]
				&& _pTable->ppData[_nM][_nN] > _pTable->ppData[_nM - 1][_nN]
				&& _pTable->ppData[_nM][_nN] > _pTable->ppData[_nM - 1][_nN - 1])
			{
				char tempLCS[100];
				strcpy(tempLCS, _pLCS);
				sprintf(_pLCS, "%c%s", _pX[_nM-1], tempLCS);

				LCS_TraceBack(_pX, _pY, _nM - 1, _nN - 1, _pTable, _pLCS);
			}
			else if (_pTable->ppData[_nM][_nN] > _pTable->ppData[_nM - 1][_nN]
				&& _pTable->ppData[_nM][_nN] == _pTable->ppData[_nM][_nN - 1])
			{
				LCS_TraceBack(_pX, _pY, _nM, _nN - 1, _pTable, _pLCS);
			}
			else
			{
				LCS_TraceBack(_pX, _pY, _nM - 1, _nN, _pTable, _pLCS);
			}
		}

		void LCS_PrintTable(_In_ LCSTable* _pTable, _In_ char* _pX, _In_ char* _pY, _In_ int _nLenX, _In_ int _nLenY)
		{
			int i = 0;
			int j = 0;

			printf("%4s", "");

			for (i = 0; i < _nLenY + 1; ++i)
				printf("%c ", _pY[i]);
			printf("\n");

			for (i = 0; i < _nLenX + 1; ++i)
			{
				if (i == 0)
					printf("%2s", "");
				else
					printf("%-2c", _pX[i - 1]);

				for (j = 0; j < _nLenY + 1; ++j)
					printf("%d ", _pTable->ppData[i][j]);
				printf("\n");
			}
		}
	}
}