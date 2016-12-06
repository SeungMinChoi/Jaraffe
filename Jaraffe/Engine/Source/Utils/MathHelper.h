//***************************************************************************************
// MathHelper.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Helper math class.
//***************************************************************************************

#pragma once

namespace JF
{
namespace Util
{

class MathHelper
{
public:
	// Constants
	static const float Pi;
	static const float PiOver2;
	static const float PiOver4;
	static const float Infinity;

public:
	// Returns random float in [0, 1).
	static float RandF()
	{
		return (float)(rand()) / (float)RAND_MAX;
	}

	// Returns random float in [a, b).
	static float RandF(float a, float b)
	{
		return a + RandF()*(b-a);
	}

	template<typename T>
	static T Min(const T& a, const T& b)
	{
		return a < b ? a : b;
	}

	template<typename T>
	static T Max(const T& a, const T& b)
	{
		return a > b ? a : b;
	}
	 
	template<typename T>
	static T Lerp(const T& a, const T& b, float t)
	{
		return a + (b-a)*t;
	}

	template<typename T>
	static T Clamp(const T& x, const T& low, const T& high)
	{
		return x < low ? low : (x > high ? high : x); 
	}

	// Returns the polar angle of the m_Point (x,y) in [0, 2*PI).
	static float AngleFromXY(float x, float y);

	static XMMATRIX InverseTranspose(CXMMATRIX M)
	{
		// Inverse-transpose is just applied to normals.  So zero out 
		// translation row so that it doesn't get into our inverse-transpose
		// calculation--we don't want the inverse-transpose of the translation.
		XMMATRIX A = M;
		A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);

		XMVECTOR det = XMMatrixDeterminant(A);
		return XMMatrixTranspose(XMMatrixInverse(&det, A));
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 ForwardVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(matrix._31, matrix._32, matrix._33);
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 BackVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(-matrix._31, -matrix._32, -matrix._33);
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 RightVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(matrix._11, matrix._12, matrix._13);
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 LeftVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(-matrix._11, -matrix._12, -matrix._13);
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 UpVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(matrix._21, matrix._22, matrix._23);
	}

	// Returns the forward vector from a transform matrix
	static XMFLOAT3 DownVec(const XMFLOAT4X4& matrix)
	{
		return XMFLOAT3(-matrix._21, -matrix._22, -matrix._23);
	}

	// Returns the translation vector from a transform matrix
	static XMVECTOR TranslationVec(const XMMATRIX& matrix)
	{
		return XMLoadFloat3(&XMFLOAT3(matrix._41, matrix._42, matrix._43));
	}

	// Sets the translation vector in a transform matrix
	static void SetTranslationVec(XMMATRIX& matrix, const XMVECTOR& translation)
	{
		matrix._41 = XMVectorGetX(translation);
		matrix._42 = XMVectorGetY(translation);
		matrix._43 = XMVectorGetZ(translation);
	}

	static XMVECTOR RandUnitVec3();
	static XMVECTOR RandHemisphereUnitVec3(XMVECTOR n);
};

}
}