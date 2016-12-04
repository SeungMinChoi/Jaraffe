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

	// ���� ���� ��ġ�� ����Ѵ�.
	vout.PositionC = mul(float4(input.Position, 1.0f), gWorldViewProj);

	// 
	vout.TexCoord = input.TexCoord;

	return vout;
}

float4 PS(in PSInput input) : SV_Target0
{
	// �л걤 ���� ǥ���� �����Ѵ�.
	float4 diffuseAlbedo = DiffuseMap.Sample(samAnisotropic, input.TexCoord);

	// ���� �ȼ��� ȭ�� ���� ��ġ�� �����ؼ� �� ���� �ؽ�ó�� ǥ�� ������ ���� ���ε��� �����Ѵ�.
	int3 sampleIndices = int3(input.ScreenPos.xy, 0);

	// �� ���ۿ��� ���� ���� �����Ѵ�.
	float4 lighting = LightTexture.Load(sampleIndices);

	// �л걤 �ݻ����� �ݿ��� �ݻ����� ���� ���� �����Ѵ�.
	float3 Ambient = float3(0.2f, 0.2f, 0.2f);
	float3 diffuse = (lighting.xyz + Ambient) * diffuseAlbedo.rgb;
	float specular = lighting.w		* SpecularAlbedo;

	// �л걤 ����� �ݿ��� ������ ���� ���� ���� ��� �����̴�.
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