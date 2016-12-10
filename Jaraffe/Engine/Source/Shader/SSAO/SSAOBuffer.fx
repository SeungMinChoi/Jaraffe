Texture2D gRandomVecMap;
Texture2D gNormalDepthVMap;

cbuffer cbPerFrame
{
	float4x4 gViewToTexSpace;		// ���� ��� ���ϱ� �ؽ�ó ���
	float4   gOffsetVectors[14];
	float4   gFrustumCorners[4];

	// ���� ������ ���̴� �����.
	float    gOcclusionRadius		= 0.5f;
	float    gOcclusionFadeStart	= 0.2f;
	float    gOcclusionFadeEnd		= 2.0f;
	float    gSurfaceEpsilon		= 0.05f;
};

SamplerState samNormalDepth
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;

	// ����,���� �� �ٱ��� ǥ���� �����ϴ� ��� �߸���
	// ���󵵰� ������ �ʵ��� ���� �� ���� ���� �����Ѵ�.
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

	// �̹� NDC �����̴�.
	vout.PosH = float4(vin.PosL, 1.0f);

	// ������ x���п��� ����ü �� ��� �������� ������ ����Ǿ� �ִ�.
	vout.ToFarPlane = gFrustumCorners[vin.ToFarPlaneIndex.x].xyz;

	// �ؽ�ó ��ǥ�� �״�� �ȼ� ���̴��� �Ѱ��ش�.
	vout.Tex = vin.Tex;

	return vout;
}

// ǥ���� q�� �� p�� �󸶳� ���������� distZ(���� ����) �� �Լ��μ� ����Ѵ�.
float OcclusionFunction(float distZ)
{
	//
	// ���� depth(q) rk depth(p) �� "�ڿ�" �ִٸ� q�� p�� ���� �� ����.
	// ���� depth(q) �� depth(p) �� ����� ����� ��쿡�� q�� p�� ������ �ʴ� ������ �����Ѵ�.
	// �ֳ��ϸ�, q��p�� ������ ���ؼ��� q�� ��� Epsilon��ŭ�� p���� �տ� �־�� �ϱ� �����̴�.
	//
	// ���� ��꿡�� ������ ���� �Լ��� ����Ѵ�.
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

		// distZ �� gOcclusionFadeStart���� gOcclusionFadeEnd �� �����Կ����� ���󵵸� 1���� 0���� ���� �����Ѵ�.
		occlusion = saturate((gOcclusionFadeEnd - distZ) / fadeLength);
	}

	return occlusion;
}

float4 PS(VertexOut pin, uniform int gSampleCount) : SV_Target
{
	// p -- ���� �ֺ��� ���� ����ϰ��� �ϴ� �ȼ��� �ش��ϴ� ��
	// n -- p������ ���� ����.
	// q -- p �ֺ��� �� ������ �� ( ǥ���� )
	// r -- p�� ���� ���ɼ��� �ִ� ������ ������

	// �� �ȼ��� �þ� ���� ������ z ������ �����´�. ���� �������Ǵ�
	// ȭ�� ��ü �簢���� �ؽ�ó ��ǥ���� �̹� uv ������ �ִ�.
	float4 normalDepth = gNormalDepthVMap.SampleLevel(samNormalDepth, pin.Tex, 0.0f);

	float3 n = normalDepth.xyz;
	float pz = normalDepth.w;

	//
	// ������ �þ� ���� ��ġ (x,y,z) �� �籸���Ѵ�.
	// �켱p = t*pin.ToFarPlane�� �����ϴ� t�� ���Ѵ�.
	// p.z = t*pin.ToFarPlane.z
	// t = p.z / pin.ToFarPlane.z
	//
	float3 p = (pz / pin.ToFarPlane.z)*pin.ToFarPlane;

	// ������ ���͸� �����ؼ� [0,1] --> [-1, +1]�� ����Ѵ�.
	float3 randVec = 2.0f*gRandomVecMap.SampleLevel(samRandomVec, 4.0f*pin.Tex, 0.0f).rgb - 1.0f;

	float occlusionSum = 0.0f;

	// p �ֺ��� �̿� ǥ�������� n������ �ݱ����� �����Ѵ�.
	[unroll]
	for (int i = 0; i < gSampleCount; ++i)
	{
		// �̸� ����� �� ��� ������ ���͵��� ���� �����Ǿ� �ִ�( ��, ������ ���͵��� ���� �������� ���� ���� �ʴ� )
		// �̵��� �ϳ��� ������ ���͸� �������� �ݻ��Ű�� ���� ������ ������ ���͵��� ���������.
		float3 offset = reflect(gOffsetVectors[i].xyz, randVec);

		// ������ ���Ͱ� (p, n) ���� ���ǵ� ����� ������ ���ϰ� ������ ������ �ݴ�� �����´�.
		float flip = sign(dot(offset, n));

		// p �ֺ����� ���� ������ �̳��� ������ �� q�� �����Ѵ�.
		float3 q = p + flip * gOcclusionRadius * offset;

		// q�� �����ؼ� ���� �ؽ�ó ��ǥ�� ���Ѵ�.
		float4 projQ = mul(float4(q, 1.0f), gViewToTexSpace);
		projQ /= projQ.w;

		// �������� q���� ���������� ������ ���� ����� �ȼ��� ���̸� ���Ѵ�.
		// ( �̰��� q�� ���̴� �ƴϴ�. q�� �׳� p ��ó�� ������ ���̸�, ����� ��ü�� �ƴ� �� ������ �ִ� ���� ���� �ִ� )
		// ���� ����� ���̴� ���� �ʿ��� �����Ѵ�.

		float rz = gNormalDepthVMap.SampleLevel(samNormalDepth, projQ.xy, 0.0f).a;

		// ������ �þ� ���� ��ġ r = (rx,ry,rz).  �� �籸�� �Ѵ�.
		// r�� q�� ������ �������� �����Ƿ�, r = t*q�� �����ϴ� t�� �����Ѵ�.
		// r.z = t*q.z ==> t = r.z / q.z

		float3 r = (rz / q.z) * q;

		//
		// r�� p�� �������� ����.
		//	* ���� dot(n, normalize(r - p))�� ������ ������ r�� ��� Plane(p,n) �������� �󸶳� �տ� �ִ����� ��Ÿ����.
		//	  �� �տ� �������� ������ ����ġ�� �� ũ�� ��´�. �̷��� �ϸ� r�� �ü��� ������ ��� (p,n)�� ���� �� ���� ������ ���� �� ����
		//	  ������ r�� p�� �����ٰ� �߸� �����ϴ� ��Ȳ�� �����ȴ�.
		//	* ���󵵴� ���� ��p�� ������ r ������ �Ÿ��� �����Ѵ�.
		//	  r�� p���� �ʹ� �ָ� ������ p�� ������ �ʴ� ������ ���ֵȴ�.

		float distZ = p.z - r.z;
		float dp = max(dot(n, normalize(r - p)), 0.0f);
		float occlusion = dp * OcclusionFunction(distZ);

		occlusionSum += occlusion;
	}

	occlusionSum /= gSampleCount;

	float access = 1.0f - occlusionSum;

	// SSAO�� �� �� �ظ��� ȿ���� ������, �ŵ������� �̿��ؼ�
	// SSAO ���� ��� ��ȭ�Ѵ�.
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
