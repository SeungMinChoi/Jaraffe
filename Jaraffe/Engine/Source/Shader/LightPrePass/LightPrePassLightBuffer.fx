Texture2D gNormalTexture;
Texture2D gPositionTexture;

cbuffer cbLightParams
{
	float3 LightPos;
	float3 LightColor;
	float3 LightDirection;
	float2 SpotLightAngles;
	float4 LightRange;
};

cbuffer cbCameraParams
{
	float3 CameraPos;
};

void GetGBufferAttributes(in float2 screenPos, out float3 normal, out float3 position, out float specularPower)
{
	// �ؽ�ó ǥ�� ������ ���� ���ε��� ���� ȭ�� ��ġ�� �����ؼ� ���Ѵ�.
	int3 sampleIndices = int3(screenPos.xy, 0);

	float4 normalTex	= gNormalTexture.Load(sampleIndices);
	normal				= normalTex.xyz;
	specularPower		= normalTex.w;
	position			= gPositionTexture.Load(sampleIndices).xyz;
}

/* [lightType] 0 : Directionallight, 1 : PointLight, 2 : SpotLight */
float4 CalcLighting(in float3 normal, in float3 position, in float specularPower, uniform int lightType)
{
	// �л걤 ���� ����Ѵ�.
	float3 L = 0;
	float attenuation = 1.0f;

	if (lightType == 1 || lightType == 2)
	{
		// ���� ��ġ�� ���� ��ġ�� �̿��ؼ� �� ���͸� ���Ѵ�.
		L = LightPos - position;

		// �������� �Ÿ��� �����ؼ� ���� ����� ���Ѵ�.
		float dist = length(L);
		attenuation = max(0, 1.0f - (dist / LightRange.x));

		L /= dist;
	}
	else if (lightType == 0)
	{
		// ���Ɽ�� ���谡 ����.
		L = -LightDirection;
	}

	if (lightType == 2)
	{
		// �������� ��쿡�� �� ������� ������ ���� ����� ������ ��ģ��.
		float3 L2 = LightDirection;
		float rho = dot(-L, L2);
		attenuation *= saturate((rho - SpotLightAngles.y) / (SpotLightAngles.x - SpotLightAngles.y));
	}

	float nDotL = saturate(dot(normal, L));
	float3 diffuse = nDotL * LightColor * attenuation;

	// �ݿ��� ���� ����Ѵ�.
	float3 V = CameraPos - position;
	float3 H = normalize(L + V);
	float specular = pow(saturate(dot(normal, H)), specularPower) * attenuation * nDotL;

	// �л걤 ����� �ݿ��� ���⸦ ����Ѵ�.
	float3 ambient = float3(0.2f, 0.2f, 0.2f);
	return float4(diffuse + ambient, specular);
}

float4 VS(in float3 position : POSITION) : SV_Position
{
	// ȭ�� ��ü �簢���� ��ġ�� �״�� �Ѱ��ش�.
	return float4(position, 1.0f);
}

float4 PS(in float4 screenPos : SV_Position, uniform int lightType) : SV_Target0
{
	float3 normal;
	float3 position;
	float specularPower;

	// ���� ���� �ؽ�ó���� ���� ������ �����Ѵ�.
	GetGBufferAttributes(screenPos.xy, normal, position, specularPower);

	return CalcLighting(normal, position, specularPower, lightType);
}

technique11 DirectionalLight
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(0)));
	}
}

technique11 PointLight
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(1)));
	}
}

technique11 Spotlight
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, PS(2)));
	}
}