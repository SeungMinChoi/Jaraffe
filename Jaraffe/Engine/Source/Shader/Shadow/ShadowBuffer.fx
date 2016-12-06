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
// [MSDN���� ����]
// ���� ��� ���ձ� �ܰ迡 ���� ���� ������ ������ UNORM�̰ų�
// ��� ���ձ� �ܰ迡 �ƹ��� ���� ���۵� ���� ���� �ʴٸ�,
// ����ġ�� ������ ���� ���ȴ�.
//
// Bias = (float)DepthBias * r + SlopeScaledDepthBias * MaxDepthSlope;
//
// ���⼭ r�� ���� ���� ������ float32�� ��ȯ���� �� ǥ�� ������, 0���� ū �ּڰ��̴�.
// [MSDN ���� ��]
//
// 24��Ʈ ���� ������ ��� r = 1 / 2 ^ 24 �̴�.
//
// ��: DepthBias = 100000 ==> ���� DepthBias = 100000 / 2 ^ 24 = 0.006

	// �� ������ ����� Ư���� ũ�� �����ϹǷ�,
	// ���� ��鿡 �߸´� ������ ������ ���ļ� ���ؾ��Ѵ�.
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

// ���İ� ��� �ȼ� ���̴�
void PS(VertexOut pin)
{
	float4 diffuse = gDiffuseMap.Sample(samLinear, pin.Tex);

	// ������ ��ü�� �����ϵ���.
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