#pragma once

namespace JF
{
	namespace JFStudy
	{
		//----------------------------------------------------------------------------
		// Power
		//----------------------------------------------------------------------------
		int Pow(_In_ int _nBase, _In_ int _nExponent)
		{
			// Check)
			if (_nExponent == 1)
				return _nBase;
			else if (_nBase == 0)
				return 1;

			// if Even
			if (_nExponent % 2 == 0)
			{
				unsigned int nNewBase = Pow(_nBase, _nExponent / 2);
				return nNewBase * nNewBase;
			}
			else
			{
				unsigned int nNewBase = Pow(_nBase, (_nExponent-1) / 2);
				return (nNewBase * nNewBase) * _nBase;
			}
		}

		//----------------------------------------------------------------------------
		// MergeSort
		//----------------------------------------------------------------------------
		typedef unsigned int UINT;

		struct Matrix2x2
		{
			UINT Data[2][2];
		};

		Matrix2x2 Matrix2x2_Multiply(_In_ Matrix2x2 _A, _In_ Matrix2x2 _B)
		{
			Matrix2x2 C;

			C.Data[0][0] = _A.Data[0][0] * _B.Data[0][0] + _A.Data[0][1] * _B.Data[1][0];
			C.Data[0][1] = _A.Data[0][0] * _B.Data[1][0] + _A.Data[0][1] * _B.Data[1][1];

			C.Data[1][0] = _A.Data[1][0] * _B.Data[0][0] + _A.Data[1][1] * _B.Data[1][0];
			C.Data[1][1] = _A.Data[1][0] * _B.Data[1][0] + _A.Data[1][1] * _B.Data[1][1];

			return C;
		}

		Matrix2x2 Matrix2x2_Pow(_In_ Matrix2x2 _A, _In_ int _nExponent)
		{
			if (_nExponent > 1)
			{
				_A = Matrix2x2_Pow(_A, _nExponent / 2);
				_A = Matrix2x2_Multiply(_A, _A);

				if (_nExponent & 1)
				{
					Matrix2x2 B;
					B.Data[0][0] = 1; 
					B.Data[0][1] = 1;
					B.Data[1][0] = 1;
					B.Data[1][1] = 0;

					_A = Matrix2x2_Multiply(_A, B);
				}
			}

			return _A;
		}

		UINT Fibonacci(_In_ int N)
		{
			Matrix2x2 A;

			A.Data[0][0] = 1;
			A.Data[0][1] = 1;
			A.Data[1][0] = 1;
			A.Data[1][1] = 0;

			A = Matrix2x2_Pow(A, N);

			return A.Data[0][1];
		}
	}
}