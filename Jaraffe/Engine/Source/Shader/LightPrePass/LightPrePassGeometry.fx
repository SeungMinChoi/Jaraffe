Texture2D DiffuseMap;
Texture2D LightTexture;

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldView;
	float4x4 gWorldViewProj;
};

cbuffer MaterialProperties
{
	float3 SpecularAlbedo;
};

struct VSInput
{
	float3 Position		: POSITION;
	float3 NormalL		: NORMAL;
	float2 TexCoord		: TEXCOORD;
	float4 TangentL		: TANGENT;
};

struct VSOutput
{
	float4 PositionC	: SV_Position;
	float2 TexCoord		: TEXCOORD;
};

struct PSInput
{
	float4 ScreenPos	: SV_Position;
	float2 TexCoord		: TEXCOORD;
};

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

VSOutput VS(in VSInput input)
{
	VSOutput vout;

	// 절단 공간 위치를 계산한다.
	vout.PositionC = mul(float4(input.Position, 1.0f), gWorldViewProj);

	// 
	vout.TexCoord = input.TexCoord;

	return vout;
}

float4 PS(in PSInput input) : SV_Target0
{
	// 분산광 맵의 표본을 추출한다.
	float4 diffuseAlbedo = DiffuseMap.Sample(samAnisotropic, input.TexCoord);

	// 현재 픽셀의 화면 공간 위치에 기초해서 빛 버퍼 텍스처의 표본 추출을 위한 색인들을 결정한다.
	int3 sampleIndices = int3(input.ScreenPos.xy, 0);

	// 빛 버퍼에서 조명 값을 추출한다.
	float4 lighting = LightTexture.Load(sampleIndices);

	// 분산광 반사율과 반영광 반사율을 조명 값에 적용한다.
	float3 Ambient = float3(0.2f, 0.2f, 0.2f);
	float3 diffuse = (lighting.xyz + Ambient) * diffuseAlbedo.rgb;
	float specular = lighting.w		* SpecularAlbedo;

	// 분산광 색상과 반영광 색상을 더한 것이 최종 출력 색상이다.
	return float4(diffuse + specular, 1.0f);
}

technique11 Basic
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
}