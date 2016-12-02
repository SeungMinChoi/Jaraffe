Texture2D gNormalTexture;
Texture2D gPositionTexture;

cbuffer cbLightParams
{
	float3 LightPos;
	float3 LightColor;
	float3 LightDirection;
	float2 SpotLightAngles;
	float LightRange;
};

cbuffer cbCameraParams
{
	float3 CameraPos;
};

void GetGBufferAttributes(in float2 screenPos, out float3 normal, out float3 position, out float specularPower)
{
	// 텍스처 표본 추출을 위한 색인들을 현재 화면 위치에 기초해서 구한다.
	int3 sampleIndices = int3(screenPos.xy, 0);

	float4 normalTex	= gNormalTexture.Load(sampleIndices);
	normal				= normalTex.xyz;
	specularPower		= normalTex.w;
	position			= gPositionTexture.Load(sampleIndices).xyz;
}

/* [lightType] 0 : Directionallight, 1 : PointLight, 2 : SpotLight */
float4 CalcLighting(in float3 normal, in float3 position, in float specularPower, uniform int lightType)
{
	// 분산광 항을 계산한다.
	float3 L = 0;
	float attenuation = 1.0f;

	if (lightType == 1 || lightType == 2)
	{
		// 광원 위치와 현재 위치를 이용해서 빛 백터를 구한다.
		L = LightPos - position;

		// 광원과의 거리에 기초해서 감쇠 계수를 구한다.
		float dist = length(L);
		attenuation = max(0, 1.0f - (dist / LightRange));

		L /= dist;
	}
	else if (lightType == 0)
	{
		// 지향광은 감쇠가 없다.
		L = -LightDirection;
	}

	if (lightType == 2)
	{
		// 점적광의 경우에는 빛 방향과의 각도도 감쇠 계수에 영향을 미친다.
		float3 L2 = LightDirection;
		float rho = dot(-L, L2);
		attenuation *= saturate((rho - SpotLightAngles.y) / (SpotLightAngles.x - SpotLightAngles.y));
	}

	float nDotL = saturate(dot(normal, L));
	float3 diffuse = nDotL * LightColor * attenuation;

	// 반영광 항을 계산한다.
	float3 V = CameraPos - position;
	float3 H = normalize(L + V);
	float specular = pow(saturate(dot(normal, H)), specularPower) * attenuation * nDotL;

	// 분산광 색상과 반영광 세기를 출력한다.
	return float4(diffuse, specular);
}

float4 VS(in float3 position : POSITION) : SV_Position
{
	// 화면 전체 사각형의 위치를 그대로 넘겨준다.
	return float4(position, 1.0f);
}

float4 PS(in float4 screenPos : SV_Position, uniform int lightType) : SV_Target0
{
	float3 normal;
	float3 position;
	float specularPower;

	// 기하 버퍼 텍스처에서 기하 정보를 추출한다.
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