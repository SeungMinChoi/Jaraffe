Texture2D gDiffuseMap;

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

cbuffer cbPerFrame
{
	float4x4 gLightMVP;
};

struct VertexIn
{
	float3 PosL		: POSITION;
	float3 NormalL	: NORMAL;
	float2 Tex		: TEXCOORD;
};

struct VertexOut
{
	float4 PosH		: SV_POSITION;
	float2 Tex		: TEXCOORD;
};

RasterizerState Depth
{
// [MSDN에서 발췌]
// 현재 출력 병합기 단계에 묶인 깊이 버퍼의 형식이 UNORM이거나
// 출력 병합기 단계에 아무런 깊이 버퍼도 묶여 있지 않다면,
// 편향치는 다음과 같이 계산된다.
//
// Bias = (float)DepthBias * r + SlopeScaledDepthBias * MaxDepthSlope;
//
// 여기서 r은 길이 버퍼 형식을 float32로 변환했을 때 표현 가능한, 0보다 큰 최솟값이다.
// [MSDN 발췌 끝]
//
// 24비트 깊이 버퍼의 경우 r = 1 / 2 ^ 24 이다.
//
// 예: DepthBias = 100000 ==> 실제 DepthBias = 100000 / 2 ^ 24 = 0.006

	// 이 값들은 장면의 특성에 크게 의존하므로,
	// 가장 장면에 잘맞는 값들은 실험을 거쳐서 구해야한다.
	DepthBias = 10000;
	DepthBiasClamp = 0.0f;
	SlopeScaledDepthBias = 1.0f;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;

	vout.PosH	= mul(float4(vin.PosL, 1.0f), gLightMVP);
	vout.Tex	= vin.Tex;

	return vout;
}

// 알파값 기반 픽셀 셰이더
void PS(VertexOut pin)
{
	float4 diffuse = gDiffuseMap.Sample(samLinear, pin.Tex);

	// 투명한 물체는 제외하도록.
	clip(diffuse.a - 0.15f);
}

technique11 BuildShadowMapTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(NULL);

		SetRasterizerState(Depth);
	}
}

technique11 BuildShadowMapAlphaClipTech
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}