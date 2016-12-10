Texture2D gNormalMap;
Texture2D gDiffuseMap;

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldView;
	float4x4 gWorldViewProj;
	float4x4 gWorldInvTransposeView;
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
	float4 PosH			: SV_POSITION;
	float3 PosW			: POSITION0;
	float3 PosV			: POSITION1;
	float3 NormalW		: NORMAL0;
	float3 NormalV		: NORMAL1;
	float3 TangentW		: TANGENT0;
	float3 TangentV		: TANGENT1;
	float3 BitangentW	: BITANGENT0;
	float3 BitangentV	: BITANGENT1;
	float2 Tex			: TEXCOORD0;
};

struct PSOutput
{
	float4 NormalW		: SV_Target0;
	float4 PositionW	: SV_Target1;
	float4 NormalDepthV	: SV_Target2;
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

	// 위치와 법선을 시야공간으로 변환한다.
	vout.PosV		= mul(float4(vin.PosL, 1.0f), gWorldView).xyz;
	vout.NormalV	= mul(vin.NormalL, (float3x3)gWorldInvTransposeView);
	vout.TangentV	= normalize(mul(vin.TangentL.xyz, (float3x3)gWorldView));
	vout.BitangentV = normalize(cross(vout.NormalV, vout.TangentV) * vin.TangentL.w);

	// 법선을 세계 공간으로 변환한다.
	vout.NormalW	= normalize(mul(vin.NormalL, (float3x3)gWorld));

	// 접선 공간 기저들을 세계 공간으로 변환한다.
	vout.TangentW	= normalize(mul(vin.TangentL.xyz, (float3x3)gWorld));
	vout.BitangentW = normalize(cross(vout.NormalW, vout.TangentW) * vin.TangentL.w);

	// 세계 공간 위치를 계산한다.
	vout.PosW		= mul(float4(vin.PosL, 1.0f), gWorld).xyz;

	// 절단 공간 위치를 계산한다.
	vout.PosH		= mul(float4(vin.PosL, 1.0f), gWorldViewProj);

	// 텍스쳐 좌표.
	vout.Tex		= vin.Tex;

	return vout;
}

PSOutput PS(in VSOutput pin, uniform bool useNormalMap, uniform bool useAlphaClip)
{
	// Check)
	if (useAlphaClip)
	{
		float4 texColor = gDiffuseMap.Sample(samLinear, pin.Tex);

		clip(texColor.a - 0.1f);
	}

	// 1) 접선 공간 법선 맵에서 법선 백터를 추출, 복원한다.
	float3 normalW;
	if (useNormalMap)
	{
		// 보간을 거친 접선 공간 기저들을 재정규화한다. ( 세계공간 )
		float3x3 tangentFrameW = float3x3(normalize(pin.TangentW)
										, normalize(pin.BitangentW)
										, normalize(pin.NormalW));

		// 보간을 거친 접선 공간 기저들을 재정규화한다. ( 시야공간 )
		float3x3 tangentFrameV = float3x3(normalize(pin.TangentV)
										, normalize(pin.BitangentV)
										, normalize(pin.NormalV));

		float3 normalT = gNormalMap.Sample(samAnisotropic, pin.Tex).rgb;
		normalT = normalize(normalT * 2.0f - 1.0f);

		// 법선을 세계 공간으로 변환한다.
		normalW = mul(normalT, tangentFrameW);

		// 법선을 시야 공간으로 변환한다.
		pin.NormalV = mul(normalT, tangentFrameV);
	}
	else
	{
		normalW = normalize(pin.NormalW);

		pin.NormalV = normalize(pin.NormalV);
	}

	// 2) GBuffer 값을 채운다.
	PSOutput output;
	output.NormalW		= float4(normalW, 1.0f);
	output.PositionW	= float4(pin.PosW, 1.0f);
	output.NormalDepthV = float4(pin.NormalV, pin.PosV.z);

	return output;
}

technique11 GBuffer
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(false, false)));
	}
}

technique11 GBufferNormal
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(true, false)));
	}
}

technique11 GBufferAlphaClip
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(false, true)));
	}
}

technique11 GBufferNormalAlphaClip
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(true, true)));
	}
}