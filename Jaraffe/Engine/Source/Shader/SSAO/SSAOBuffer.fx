Texture2D gRandomVecMap;
Texture2D gNormalDepthVMap;

cbuffer cbPerFrame
{
	float4x4 gViewToTexSpace;		// 투영 행렬 곱하기 텍스처 행렬
	float4   gOffsetVectors[14];
	float4   gFrustumCorners[4];

	// 차폐 판정에 쓰이는 상수들.
	float    gOcclusionRadius		= 0.5f;
	float    gOcclusionFadeStart	= 0.2f;
	float    gOcclusionFadeEnd		= 2.0f;
	float    gSurfaceEpsilon		= 0.05f;
};

SamplerState samNormalDepth
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;

	// 법선,깊이 맵 바깥의 표본을 추출하는 경우 잘못된
	// 차폐도가 나오지 않도록 아주 먼 깊이 값을 설정한다.
	AddressU = BORDER;
	AddressV = BORDER;
	BorderColor = float4(0.0f, 0.0f, 0.0f, 1e5f);
};

SamplerState samRandomVec
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 PosL            : POSITION;
	float3 ToFarPlaneIndex : NORMAL;
	float2 Tex             : TEXCOORD;
};

struct VertexOut
{
	float4 PosH       : SV_POSITION;
	float3 ToFarPlane : TEXCOORD0;
	float2 Tex        : TEXCOORD1;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	// 이미 NDC 공간이다.
	vout.PosH = float4(vin.PosL, 1.0f);

	// 법선의 x성분에는 절두체 먼 평면 꼭짓점의 색인이 저장되어 있다.
	vout.ToFarPlane = gFrustumCorners[vin.ToFarPlaneIndex.x].xyz;

	// 텍스처 좌표는 그대로 픽셀 세이더에 넘겨준다.
	vout.Tex = vin.Tex;

	return vout;
}

// 표본점 q가 점 p를 얼마나 가리는지를 distZ(길이 차이) 의 함수로서 계산한다.
float OcclusionFunction(float distZ)
{
	//
	// 만일 depth(q) rk depth(p) 의 "뒤에" 있다면 q는 p를 가릴 수 없다.
	// 또한 depth(q) 와 depth(p) 가 충분히 가까운 경우에도 q가 p를 가리지 않는 것으로 판정한다.
	// 왜냐하면, q가p를 가리기 위해서는 q가 적어도 Epsilon만큼은 p보다 앞에 있어야 하기 때문이다.
	//
	// 차폐도 계산에는 다음과 같은 함수를 사용한다.
	// 
	//
	//       1.0     -------------\
	//               |           |  \
	//               |           |    \
	//               |           |      \ 
	//               |           |        \
	//               |           |          \
	//               |           |            \
	//  ------|------|-----------|-------------|---------|--> zv
	//        0     Eps          z0            z1        
	//

	float occlusion = 0.0f;
	if (distZ > gSurfaceEpsilon)
	{
		float fadeLength = gOcclusionFadeEnd - gOcclusionFadeStart;

		// distZ 가 gOcclusionFadeStart에서 gOcclusionFadeEnd 로 증가함에따라 차폐도를 1에서 0으로 선형 감소한다.
		occlusion = saturate((gOcclusionFadeEnd - distZ) / fadeLength);
	}

	return occlusion;
}

float4 PS(VertexOut pin, uniform int gSampleCount) : SV_Target
{
	// p -- 지금 주변광 차폐를 계싼하고자 하는 픽셀에 해당하는 점
	// n -- p에서의 법선 백터.
	// q -- p 주변의 한 무작위 점 ( 표본점 )
	// r -- p를 가릴 가능성이 있는 잠재적 차폐점

	// 이 픽셀의 시야 공간 법선과 z 성분을 가져온다. 지금 렌더링되는
	// 화면 전체 사각형의 텍스처 좌표들은 이미 uv 공간에 있다.
	float4 normalDepth = gNormalDepthVMap.SampleLevel(samNormalDepth, pin.Tex, 0.0f);

	float3 n = normalDepth.xyz;
	float pz = normalDepth.w;

	//
	// 완전한 시야 공간 위치 (x,y,z) 를 재구축한다.
	// 우선p = t*pin.ToFarPlane를 만족하는 t를 구한다.
	// p.z = t*pin.ToFarPlane.z
	// t = p.z / pin.ToFarPlane.z
	//
	float3 p = (pz / pin.ToFarPlane.z)*pin.ToFarPlane;

	// 무작위 백터를 추출해서 [0,1] --> [-1, +1]로 사상한다.
	float3 randVec = 2.0f*gRandomVecMap.SampleLevel(samRandomVec, 4.0f*pin.Tex, 0.0f).rgb - 1.0f;

	float occlusionSum = 0.0f;

	// p 주변의 이웃 표본점들을 n방향의 반구에서 추출한다.
	[unroll]
	for (int i = 0; i < gSampleCount; ++i)
	{
		// 미리 만들어 둔 상수 오프셋 백터들은 고르게 분포되어 있다( 즉, 오프셋 백터들은 같은 방향으로 뭉쳐 있지 않다 )
		// 이들을 하나의 무작위 백터를 기준으로 반사시키면 고르게 분포된 무작위 백터들이 만들어진다.
		float3 offset = reflect(gOffsetVectors[i].xyz, randVec);

		// 오프셋 백터가 (p, n) 으로 정의된 평면의 뒤쪽을 향하고 있으면 방향을 반대로 뒤집는다.
		float flip = sign(dot(offset, n));

		// p 주변에서 차폐 반지름 이내의 무작위 점 q를 선택한다.
		float3 q = p + flip * gOcclusionRadius * offset;

		// q를 투영해서 투영 텍스처 좌표를 구한다.
		float4 projQ = mul(float4(q, 1.0f), gViewToTexSpace);
		projQ /= projQ.w;

		// 시점에서 q로의 반직선에서 시점에 가장 가까운 픽셀의 깊이를 구한다.
		// ( 이것이 q의 깊이는 아니다. q는 그냥 p 근처의 임의의 점이며, 장면의 물체가 아닌 빈 공간에 있는 점일 수도 있다 )
		// 가장 가까운 깊이는 깊이 맵에서 추출한다.

		float rz = gNormalDepthVMap.SampleLevel(samNormalDepth, projQ.xy, 0.0f).a;

		// 완전한 시야 공간 위치 r = (rx,ry,rz).  를 재구축 한다.
		// r는 q를 지나는 반직선에 있으므로, r = t*q를 만족하는 t가 존재한다.
		// r.z = t*q.z ==> t = r.z / q.z

		float3 r = (rz / q.z) * q;

		//
		// r이 p를 가리는지 판정.
		//	* 내적 dot(n, normalize(r - p))는 잠재적 차폐점 r이 평면 Plane(p,n) 앞쪽으로 얼마나 앞에 있는지를 나타낸다.
		//	  더 앞에 있을수록 차폐도의 가중치를 더 크게 잡는다. 이렇게 하면 r이 시선과 직각인 평면 (p,n)에 있을 때 시점 기준의 깊이 값 차이
		//	  때문에 r이 p를 가린다고 잘못 판정하는 상황도 방지된다.
		//	* 차폐도는 현재 점p와 차폐점 r 사이의 거리에 의존한다.
		//	  r이 p에서 너무 멀리 있으면 p를 가리지 않는 것으로 간주된다.

		float distZ = p.z - r.z;
		float dp = max(dot(n, normalize(r - p)), 0.0f);
		float occlusion = dp * OcclusionFunction(distZ);

		occlusionSum += occlusion;
	}

	occlusionSum /= gSampleCount;

	float access = 1.0f - occlusionSum;

	// SSAO가 좀 더 극명한 효과를 내도록, 거듭제곱을 이용해서
	// SSAO 맵의 대비를 강화한다.
	return saturate(pow(access, 4.0f));
}

technique11 Ssao
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(14)));
	}
}
