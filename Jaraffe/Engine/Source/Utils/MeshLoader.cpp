#include "stdafx.h"
#include "MeshLoader.h"

bool JF::MeshLoader::OBJLoad(IN const std::wstring& _filePath, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices, OUT JF::Material& _material)
{
	// 버텍스 버퍼를 만들기위한 임시 버퍼들...
	std::vector<XMFLOAT3>	m_V;
	std::vector<XMFLOAT2>	m_VT;
	std::vector<XMFLOAT3>	m_VN;

	std::vector<int> PosIndex;
	std::vector<int> NormalIndex;
	std::vector<int> TexIndex;

	// 카운팅 변수들..
	int IndexTotalCnt = 0;		// face 총 갯수.
	int VertsTotalCnt = 0;		// 버텍스 총갯수.
	int TrianglesCnt = 0;		// 삼각형 갯수.

	std::wifstream fileIn(_filePath);	// 해당 경로에 있는 파일을 연다.

	std::wstring checkString;			// 문자열단위로 읽기위한 변수.
	if (fileIn)
	{
		while (fileIn)
		{
			fileIn >> checkString;
			if (checkString == L"#")
			{
				std::getline(fileIn, checkString);	// 이줄의 나머지 부분을 무시.
			}
			else if (checkString == L"g")
			{
				std::getline(fileIn, checkString);	// 이줄의 나머지 부분을 무시.
			}
			else if (checkString == L"mtllib")
			{
				fileIn >> checkString;

				// 경로를 추가.
				ProcessMtl((L"Resources/Models/" + checkString).c_str(), _material);
			}
			else if (checkString == L"vt")
			{
				XMFLOAT2 textUV;

				fileIn >> textUV.x >> textUV.y;	// U , V
				std::getline(fileIn, checkString);	// 이줄의 나머지 부분을 무시.

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
			else if (checkString == L"f")	// face 인덱스가 4개 이상일경우에대한 추가 처리하지않음.( 4개이상인 모델은 못읽는다는뜻. )
			{
				// f 이후 줄의 내용을 전부 읽는다.
				std::getline(fileIn, checkString);

				int nIdx[3][3];
				swscanf_s(checkString.c_str(),
					L"%d/%d/%d %d/%d/%d %d/%d/%d",
					&nIdx[0][0], &nIdx[0][1], &nIdx[0][2],
					&nIdx[1][0], &nIdx[1][1], &nIdx[1][2],
					&nIdx[2][0], &nIdx[2][1], &nIdx[2][2]);

				// 셋트별로 루프 ( Pos/tex/nor = 1 Set ) 
				int nTempPos, nTempTex, nTempNor;	// 임시 저장 변수들.
				for (int i = 0; i < 3; ++i)
				{
					nTempPos = nIdx[i][0] - 1;
					nTempTex = nIdx[i][1] - 1;
					nTempNor = nIdx[i][2] - 1;

					// 버텍스 총 개수만큼 루프돌면서 검사 
					bool vertAlreadyExists = false;
					for (int j = 0; j < VertsTotalCnt; ++j)
					{
						// 포지션,텍스쳐 셋트가 이미 존재하는지 체크
						if ((PosIndex[j] == nTempPos) && (TexIndex[j] == nTempTex))
						{
							// 존재한다면 인덱스버퍼만 해당 세트 번호로 추가.
							_indices.push_back(j);
							vertAlreadyExists = true;
							break;
						}
					}

					// 정점 셋트가 존재하지 않는다면.
					if (!vertAlreadyExists)
					{
						PosIndex.push_back(nTempPos);
						TexIndex.push_back(nTempTex);
						NormalIndex.push_back(nTempNor);

						_indices.push_back(VertsTotalCnt++);	// 현재 버텍스 총 개수를 인덱스 버퍼에 추가하고 1증가
					}
				}

				++TrianglesCnt;
				IndexTotalCnt += 3;				// 인덱스 총 수량 3 증가.
			}
		}
	}
	// 파일 여는대 실패했다면 오류메세지 띄운후 종료.
	else
	{
		std::wstring message = L" 해당파일을 여는대 실패 : ";
		message += _filePath;

		MessageBox(0, message.c_str(), L"Error", MB_OK);
		return false;
	}

	fileIn.close();

	// 정점 만들기.
	for (int i = 0; i < VertsTotalCnt; ++i)
	{
		Vertex::PosNormalTexTan vertexTemp;
		vertexTemp.Pos = m_V[PosIndex[i]];
		vertexTemp.Tex = m_VT[TexIndex[i]];
		vertexTemp.Normal = m_VN[NormalIndex[i]];

		_vertices.push_back(vertexTemp);
	}

	// 연산을통해 노멀과 탄젠트값을 구해주는 함수.
	ComputeNomalAndTangent(TrianglesCnt, VertsTotalCnt, _vertices, _indices);

	return true;
}

void JF::MeshLoader::ProcessMtl(IN LPCWSTR _wfilename, OUT JF::Material& _material)
{
	std::wifstream fileIn(_wfilename);	// 해당 경로에 있는 파일을 연다.

	std::wstring checkString;			// 문자열단위로 읽기위한 변수.
	if (fileIn)
	{
		while (fileIn)
		{
			fileIn >> checkString;
			if (checkString == L"#")
			{
				std::getline(fileIn, checkString);	// 이줄의 나머지 부분을 무시.
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

				_material.m_MainTexture = new JF::Texture();
				_material.m_MainTexture->SetTexture(gTEXTUREMGR->CreateTexture(L"Resources/Textures/" + checkString));
			}
		}
	}
	// 파일을 여는대 실패했다면..
	else
	{
		std::wstring message = L" 해당파일을 여는대 실패 : ";
		message += _wfilename;

		MessageBox(0, message.c_str(), L"Error", MB_OK);
		return;
	}

	fileIn.close();
}

void JF::MeshLoader::ComputeNomalAndTangent(IN const int& _triangleCnt, IN const int& _vertexCnt, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices)
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

		_vertices[i].Tan.x = XMVectorGetX(tangentSum);
		_vertices[i].Tan.y = XMVectorGetY(tangentSum);
		_vertices[i].Tan.z = XMVectorGetZ(tangentSum);

		normalSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		tangentSum = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
		facesUsing = 0;
	}
}