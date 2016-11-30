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

	// 법선을 세계 공간으로 변환한다.
	vout.NormalW	= normalize(mul(vin.NormalL, (float3x3)gWorld));

	// 접선 공간 기저들을 세계 공간으로 변환한다.
	vout.TangentW	= normalize(mul(vin.TangentL.xyz, (float3x3)gWorld));
	vout.BitangentW = normalize(cross(vout.NormalW, vout.TangentW) * vin.TangentL.w);

	// 세계 공간 위치를 계산한다.
	vout.PosW		= mul(float4(vin.PosL, 1.0f), gWorld).xyz;

	// 절단 공간 위치를 계산한다.
	vout.PosC		= mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	// 텍스쳐 좌표.
	vout.Tex		= vin.Tex;

	return vout;
}

PSOutput PS(in VSOutput pin, uniform bool useNormalMap)
{
	// 접선 공간 법선 맵에서 법선 백터를 추출, 복원한다.
	float3 normalW;
	if (useNormalMap)
	{
		// 보간을 거친 접선 공간 기저들을 재정규화한다.
		float3x3 tangentFrameW = float3x3(normalize(pin.TangentW)
			, normalize(pin.BitangentW)
			, normalize(pin.NormalW));

		float3 normalT = gNormalMap.Sample(samAnisotropic, pin.Tex).rgb;
		normalT = normalize(normalT * 2.0f - 1.0f);

		// 법선을 세계 공간으로 변환한다.
		normalW = mul(normalT, tangentFrameW);
	}
	else
	{
		normalW = pin.NormalW;
	}

	// 조명 계산에 필요한 값들을 기하 버퍼에 저장한다.
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