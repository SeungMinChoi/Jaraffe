Texture2D gNormalMap;

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldView;
	float4x4 gWorldViewProj;
};

struct VSInput
{
	float3 PosL		: POSITION;
	float3 NormalL	: NORMAL;
	float2 Tex		: TEXCOORD;
	float4 TangentL : TANGENT;
};

struct VSOutput
{
	float4 PosC			: SV_POSITION;
	float2 Tex			: TEXCOORD;
	float3 NormalW		: NORMAL;
	float3 TangentW		: TANGENT;
	float3 BitangentW	: BITANGENT;
	float3 PosW			: POSITION;
};

struct PSOutput
{
	float4 Normal	: SV_Target0;
	float4 Position	: SV_Target1;
};

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

SamplerState samLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

VSOutput VS(in VSInput vin)
{
	VSOutput vout;

	// ������ ���� �������� ��ȯ�Ѵ�.
	vout.NormalW	= normalize(mul(vin.NormalL, (float3x3)gWorld));

	// ���� ���� �������� ���� �������� ��ȯ�Ѵ�.
	vout.TangentW	= normalize(mul(vin.TangentL.xyz, (float3x3)gWorld));
	vout.BitangentW = normalize(cross(vout.NormalW, vout.TangentW) * vin.TangentL.w);

	// ���� ���� ��ġ�� ����Ѵ�.
	vout.PosW		= mul(float4(vin.PosL, 1.0f), gWorld).xyz;

	// ���� ���� ��ġ�� ����Ѵ�.
	vout.PosC		= mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	// �ؽ��� ��ǥ.
	vout.Tex		= vin.Tex;

	return vout;
}

PSOutput PS(in VSOutput pin, uniform bool useNormalMap)
{
	// ���� ���� ���� �ʿ��� ���� ���͸� ����, �����Ѵ�.
	float3 normalW;
	if (useNormalMap)
	{
		// ������ ��ģ ���� ���� �������� ������ȭ�Ѵ�.
		float3x3 tangentFrameW = float3x3(normalize(pin.TangentW)
			, normalize(pin.BitangentW)
			, normalize(pin.NormalW));

		float3 normalT = gNormalMap.Sample(samAnisotropic, pin.Tex).rgb;
		normalT = normalize(normalT * 2.0f - 1.0f);

		// ������ ���� �������� ��ȯ�Ѵ�.
		normalW = mul(normalT, tangentFrameW);
	}
	else
	{
		normalW = pin.NormalW;
	}

	// ���� ��꿡 �ʿ��� ������ ���� ���ۿ� �����Ѵ�.
	PSOutput output;
	output.Normal	= float4(normalW, 1.0f);
	output.Position = float4(pin.PosW, 1.0f);

	return output;
}

technique11 Basic
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(true)));
	}
}

technique11 Basic_NoNormal
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(false)));
	}
}