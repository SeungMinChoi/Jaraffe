#include "stdafx.h"
#include "MeshLoader.h"

bool Jaraffe::MeshLoader::OBJLoad(IN const std::wstring& _filePath, OUT std::vector<Vertex::PosNormalTex>& _vertices, OUT std::vector<UINT>& _indices, OUT Jaraffe::Material& _material)
{
	// ���ؽ� ���۸� ��������� �ӽ� ���۵�...
	std::vector<XMFLOAT3>	m_V;
	std::vector<XMFLOAT2>	m_VT;
	std::vector<XMFLOAT3>	m_VN;

	std::vector<int> PosIndex;
	std::vector<int> NormalIndex;
	std::vector<int> TexIndex;

	// ī���� ������..
	int IndexTotalCnt = 0;		// face �� ����.
	int VertsTotalCnt = 0;		// ���ؽ� �Ѱ���.
	int TrianglesCnt = 0;		// �ﰢ�� ����.

	std::wifstream fileIn(_filePath);	// �ش� ��ο� �ִ� ������ ����.

	std::wstring checkString;			// ���ڿ������� �б����� ����.
	if (fileIn)
	{
		while (fileIn)
		{
			fileIn >> checkString;
			if (checkString == L"#")
			{
				std::getline(fileIn, checkString);	// ������ ������ �κ��� ����.
			}
			else if (checkString == L"g")
			{
				std::getline(fileIn, checkString);	// ������ ������ �κ��� ����.
			}
			else if (checkString == L"mtllib")
			{
				fileIn >> checkString;

				// ��θ� �߰�.
				ProcessMtl((L"Resources/Models/" + checkString).c_str(), _material);
			}
			else if (checkString == L"vt")
			{
				XMFLOAT2 textUV;

				fileIn >> textUV.x >> textUV.y;	// U , V
				std::getline(fileIn, checkString);	// ������ ������ �κ��� ����.

				textUV.y = 1.0f - textUV.y;

				m_VT.push_back(textUV);
			}
			else if (checkString == L"vn")
			{
				XMFLOAT3 normal;

				fileIn >> normal.x >> normal.y >> normal.z;

				m_VN.push_back(normal);
			}
			else if (checkString == L"v")
			{
				XMFLOAT3 pos;

				fileIn >> pos.x >> pos.y >> pos.z;

				m_V.push_back(pos);
			}
			else if (checkString == L"f")	// face �ε����� 4�� �̻��ϰ�쿡���� �߰� ó����������.( 4���̻��� ���� ���д´ٴ¶�. )
			{
				// f ���� ���� ������ ���� �д´�.
				std::getline(fileIn, checkString);

				int nIdx[3][3];
				swscanf_s(checkString.c_str(),
					L"%d/%d/%d %d/%d/%d %d/%d/%d",
					&nIdx[0][0], &nIdx[0][1], &nIdx[0][2],
					&nIdx[1][0], &nIdx[1][1], &nIdx[1][2],
					&nIdx[2][0], &nIdx[2][1], &nIdx[2][2]);

				// ��Ʈ���� ���� ( Pos/tex/nor = 1 Set ) 
				int nTempPos, nTempTex, nTempNor;	// �ӽ� ���� ������.
				for (int i = 0; i < 3; ++i)
				{
					nTempPos = nIdx[i][0] - 1;
					nTempTex = nIdx[i][1] - 1;
					nTempNor = nIdx[i][2] - 1;

					// ���ؽ� �� ������ŭ �������鼭 �˻� 
					bool vertAlreadyExists = false;
					for (int j = 0; j < VertsTotalCnt; ++j)
					{
						// ������,�ؽ��� ��Ʈ�� �̹� �����ϴ��� üũ
						if ((PosIndex[j] == nTempPos) && (TexIndex[j] == nTempTex))
						{
							// �����Ѵٸ� �ε������۸� �ش� ��Ʈ ��ȣ�� �߰�.
							_indices.push_back(j);
							vertAlreadyExists = true;
							break;
						}
					}

					// ���� ��Ʈ�� �������� �ʴ´ٸ�.
					if (!vertAlreadyExists)
					{
						PosIndex.push_back(nTempPos);
						TexIndex.push_back(nTempTex);
						NormalIndex.push_back(nTempNor);

						_indices.push_back(VertsTotalCnt++);	// ���� ���ؽ� �� ������ �ε��� ���ۿ� �߰��ϰ� 1����
					}
				}

				++TrianglesCnt;
				IndexTotalCnt += 3;				// �ε��� �� ���� 3 ����.
			}
		}
	}
	// ���� ���´� �����ߴٸ� �����޼��� ����� ����.
	else
	{
		std::wstring message = L" �ش������� ���´� ���� : ";
		message += _filePath;

		MessageBox(0, message.c_str(), L"Error", MB_OK);
		return false;
	}

	fileIn.close();

	// ���� �����.
	for (int i = 0; i < VertsTotalCnt; ++i)
	{
		Vertex::PosNormalTex vertexTemp;
		vertexTemp.Pos = m_V[PosIndex[i]];
		vertexTemp.Tex = m_VT[TexIndex[i]];
		vertexTemp.Normal = m_VN[NormalIndex[i]];

		_vertices.push_back(vertexTemp);
	}

	// ���������� ��ְ� ź��Ʈ���� �����ִ� �Լ�.
	ComputeNomalAndTangent(TrianglesCnt, VertsTotalCnt, _vertices, _indices);

	return true;
}

void Jaraffe::MeshLoader::ProcessMtl(IN LPCWSTR _wfilename, OUT Jaraffe::Material& _material)
{
	std::wifstream fileIn(_wfilename);	// �ش� ��ο� �ִ� ������ ����.

	std::wstring checkString;			// ���ڿ������� �б����� ����.
	if (fileIn)
	{
		while (fileIn)
		{
			fileIn >> checkString;
			if (checkString == L"#")
			{
				std::getline(fileIn, checkString);	// ������ ������ �κ��� ����.
			}
			else if (checkString == L"Ka")
			{
				float fR, fG, fB;
				fileIn >> fR >> fG >> fB;

				_material.m_Material.Ambient.x = fR;
				_material.m_Material.Ambient.y = fG;
				_material.m_Material.Ambient.z = fB;
				_material.m_Material.Ambient.w = 1.0f;
			}
			else if (checkString == L"Kd")
			{
				float fR, fG, fB;
				fileIn >> fR >> fG >> fB;

				_material.m_Material.Diffuse.x = fR;
				_material.m_Material.Diffuse.y = fG;
				_material.m_Material.Diffuse.z = fB;
				_material.m_Material.Diffuse.w = 1.0f;
			}
			else if (checkString == L"Ks")
			{
				float fR, fG, fB;
				fileIn >> fR >> fG >> fB;

				_material.m_Material.Specular.x = fR;
				_material.m_Material.Specular.y = fG;
				_material.m_Material.Specular.z = fB;
				_material.m_Material.Specular.w = 1.0f;
			}
			else if (checkString == L"map_Kd")		// diffuse map
			{
				fileIn >> checkString;

				_material.m_MainTexture = new Jaraffe::Texture();
				_material.m_MainTexture->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/" + checkString));
			}
		}
	}
	// ������ ���´� �����ߴٸ�..
	else
	{
		std::wstring message = L" �ش������� ���´� ���� : ";
		message += _wfilename;

		MessageBox(0, message.c_str(), L"Error", MB_OK);
		return;
	}

	fileIn.close();
}

void Jaraffe::MeshLoader::ComputeNomalAndTangent(IN const int& _triangleCnt, IN const int& _vertexCnt, OUT std::vector<Vertex::PosNormalTex>& _vertices, OUT std::vector<UINT>& _indices)
{
	std::vector<XMFLOAT3> tempNormal;

	XMFLOAT3 unnormalized = XMFLOAT3(0.0f, 0.0f, 0.0f);

	std::vector<XMFLOAT3> tempTangent;
	XMFLOAT3 tangent = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float tcU1, tcV1, tcU2, tcV2;

	float vecX, vecY, vecZ;

	XMVECTOR edge1 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR edge2 = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	for (int i = 0; i < _triangleCnt; ++i)
	{
		//( 1 , 0 )
		vecX = _vertices[_indices[(i * 3) + 1]].Pos.x - _vertices[_indices[(i * 3)]].Pos.x;
		vecY = _vertices[_indices[(i * 3) + 1]].Pos.y - _vertices[_indices[(i * 3)]].Pos.y;
		vecZ = _vertices[_indices[(i * 3) + 1]].Pos.z - _vertices[_indices[(i * 3)]].Pos.z;
		edge1 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

		//( 2 , 0 )
		vecX = _vertices[_indices[(i * 3) + 2]].Pos.x - _vertices[_indices[(i * 3)]].Pos.x;
		vecY = _vertices[_indices[(i * 3) + 2]].Pos.y - _vertices[_indices[(i * 3)]].Pos.y;
		vecZ = _vertices[_indices[(i * 3) + 2]].Pos.z - _vertices[_indices[(i * 3)]].Pos.z;
		edge2 = XMVectorSet(vecX, vecY, vecZ, 0.0f);

		XMStoreFloat3(&unnormalized, XMVector3Cross(edge1, edge2));

		tempNormal.push_back(unnormalized);

		tcU1 = _vertices[_indices[(i * 3) + 1]].Tex.x - _vertices[_indices[(i * 3)]].Tex.x;
		tcV1 = _vertices[_indices[(i * 3) + 1]].Tex.y - _vertices[_indices[(i * 3)]].Tex.y;
															  
		tcU2 = _vertices[_indices[(i * 3) + 2]].Tex.x - _vertices[_indices[(i * 3)]].Tex.x;
		tcV2 = _vertices[_indices[(i * 3) + 2]].Tex.y - _vertices[_indices[(i * 3)]].Tex.y;
																  
		tangent.x = (tcV2 * XMVectorGetX(edge1) - tcV1 * XMVectorGetX(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
		tangent.y = (tcV2 * XMVectorGetY(edge1) - tcV1 * XMVectorGetY(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));
		tangent.z = (tcV2 * XMVectorGetZ(edge1) - tcV1 * XMVectorGetZ(edge2)) * (1.0f / (tcU1 * tcV2 - tcU2 * tcV1));

		tempTangent.push_back(tangent);
	}

	XMVECTOR normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	int facesUsing = 0;
	float tX, tY, tZ;

	for (size_t i = 0; i < _vertexCnt; ++i)
	{
		for (size_t j = 0; j < _triangleCnt; ++j)
		{
			if (_indices[j * 3] == i ||
				_indices[(j * 3) + 1] == i ||
				_indices[(j * 3) + 2] == i)
			{
				tX = XMVectorGetX(normalSum) + tempNormal[j].x;
				tY = XMVectorGetY(normalSum) + tempNormal[j].y;
				tZ = XMVectorGetZ(normalSum) + tempNormal[j].z;

				normalSum = XMVectorSet(tX, tY, tZ, 0.0f);

				tX = XMVectorGetX(tangentSum) + tempTangent[j].x;
				tY = XMVectorGetY(tangentSum) + tempTangent[j].y;
				tZ = XMVectorGetZ(tangentSum) + tempTangent[j].z;

				tangentSum = XMVectorSet(tX, tY, tZ, 0.0f);

				facesUsing++;
			}
		}

		normalSum = normalSum / (float)facesUsing;
		tangentSum = tangentSum / (float)facesUsing;

		normalSum = XMVector3Normalize(normalSum);
		tangentSum = XMVector3Normalize(tangentSum);

		_vertices[i].Normal.x = XMVectorGetX(normalSum);
		_vertices[i].Normal.y = XMVectorGetY(normalSum);
		_vertices[i].Normal.z = XMVectorGetZ(normalSum);

		//vertices[i].tangent.x = XMVectorGetX(tangentSum);
		//vertices[i].tangent.y = XMVectorGetY(tangentSum);
		//vertices[i].tangent.z = XMVectorGetZ(tangentSum);

		normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		facesUsing = 0;
	}
}