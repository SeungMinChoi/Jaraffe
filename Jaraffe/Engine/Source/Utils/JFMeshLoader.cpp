#include "stdafx.h"
#include "JFMeshLoader.h"

JF::JFMeshLoader::JFMeshLoader()
{
	
}


JF::JFMeshLoader::~JFMeshLoader()
{
}

bool JF::JFMeshLoader::OBJLoad(IN const std::string& _filePath, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices, OUT std::vector<Mesh::Subset>& _subset)
{
	// Declear)
	bool ret;

	// 1) File Importe
	Assimp::Importer Importer;
	const aiScene* pScene = Importer.ReadFile(
		_filePath.c_str(), aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_MaxQuality);

	// 2)
	if (pScene) {
		ret = InitFromScene(pScene, _filePath.c_str(), _vertices, _indices, _subset);
	}
	else {
		printf("Error parsing '%s': '%s'\n", _filePath, Importer.GetErrorString());
	}

	// Retrun)
	return true;
}

bool JF::JFMeshLoader::InitFromScene(
	  IN const aiScene* pScene
	, IN const char* Filename
	, OUT std::vector<Vertex::PosNormalTexTan>& vertices
	, OUT std::vector<UINT>& indices
	, OUT std::vector<Mesh::Subset>& _subset)
{
	// 1) Clear)
	indices.clear();
	vertices.clear();

	// Check)
	if (pScene->HasMeshes()) 
	{
		for (size_t i = 0; i < pScene->mNumMeshes; i++) 
		{
			// 
			aiMesh* mesh = pScene->mMeshes[i];

			Mesh::Subset subSet;
			{
				subSet.VertexCount = mesh->mNumVertices;
				subSet.VertexStart = vertices.size();
				subSet.FaceStart = indices.size() / 3;
				subSet.FaceCount = mesh->mNumFaces;
			}

			//
			ProcessMesh(pScene->mMeshes[i], vertices, indices);

			//
			ProcessMaterial(pScene, pScene->mMeshes[i], subSet);

			// Add
			_subset.push_back(subSet);
		}
	}
	return true;
}

void JF::JFMeshLoader::ProcessMesh(IN aiMesh* pMesh, OUT std::vector<Vertex::PosNormalTexTan>& vertices, OUT std::vector<UINT>& indices)
{
	// Declear)
	UINT vertexStart = vertices.size();

	// 1) Resize
	indices.reserve(indices.size() + pMesh->mNumFaces * 3);
	vertices.reserve(vertices.size() + pMesh->mNumVertices);

	// 2)
	for (size_t i = 0; i < pMesh->mNumVertices; i++)
	{
		XMFLOAT3 pos, norm;
		XMFLOAT4 tan;
		XMFLOAT2 texC;
		Vertex::PosNormalTexTan v;
		pMesh->HasPositions() ?					pos =	{ pMesh->mVertices[i].x, pMesh->mVertices[i].y, pMesh->mVertices[i].z }			: pos = { 0, 0, 0 };
		pMesh->HasNormals() ?					norm =	{ pMesh->mNormals[i].x, pMesh->mNormals[i].y, pMesh->mNormals[i].z }			: norm = { 0, 0, 0 };
		pMesh->HasTextureCoords(0) ?			texC =	{ pMesh->mTextureCoords[0][i].x, pMesh->mTextureCoords[0][i].y }				: texC = { 0.5f, 0.5f };
		pMesh->HasTangentsAndBitangents() ?		tan =	{ pMesh->mTangents[i].x, pMesh->mTangents[i].y, pMesh->mTangents[i].z, 1.0f }	: tan = { 0, 0, 0, 0 };

		v.Pos = pos; 
		v.Normal = norm; 
		v.Tex = texC; 
		v.Tan = tan;
		vertices.push_back(v);
	}

	// 3)
	size_t count = indices.size();
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++) {
		const aiFace& Face = pMesh->mFaces[i];
		assert(Face.mNumIndices == 3);
		indices.push_back(Face.mIndices[0] + vertexStart);
		indices.push_back(Face.mIndices[1] + vertexStart);
		indices.push_back(Face.mIndices[2] + vertexStart);
	}
}

void JF::JFMeshLoader::ProcessMaterial(IN const aiScene* pScene, IN aiMesh* pMesh, OUT Mesh::Subset& _subset)
{
	XMFLOAT4 xmdiffuse(0, 0, 0, 0), xmspecular(0, 0, 0, 0), xmambient(0, 0, 0, 0), xmreflect(0, 0, 0, 0);
	aiMaterial* mtl = pScene->mMaterials[pMesh->mMaterialIndex];

	aiColor4D diffuse, ambient, specular, reflect;
	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		AICOLOR4toXMFLOAT4(diffuse, xmdiffuse);

	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		AICOLOR4toXMFLOAT4(ambient, xmambient);

	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		AICOLOR4toXMFLOAT4(specular, xmspecular);

	float shiness;
	if (AI_SUCCESS == aiGetMaterialFloat(mtl, AI_MATKEY_SHININESS, &shiness))
		xmspecular.w = shiness;

	if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_REFLECTIVE, &reflect))
		AICOLOR4toXMFLOAT4(reflect, xmreflect);

	_subset.m_Material.m_Material.Ambient	= xmambient;
	_subset.m_Material.m_Material.Diffuse	= xmdiffuse;
	_subset.m_Material.m_Material.Reflect	= xmreflect;
	_subset.m_Material.m_Material.Specular	= xmspecular;
	_subset.m_Material.m_bAlphaClip = false;

	aiString diffusePath, normalPath;

	mtl->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &diffusePath);
	{
		if (diffusePath.length > 0)
		{
			wchar_t	wstr[512];
			size_t wLen = 0;
			mbstowcs_s(&wLen, wstr, diffusePath.length + 1, diffusePath.C_Str(), _TRUNCATE);
			std::wstring input = L"Resources/Textures/";
			input += wstr;

			auto texture = new JF::Texture();
			texture->SetTexture(gTEXTUREMGR->CreateTexture(input));

			_subset.m_Material.m_MainTexture = texture;
		}
	}
	mtl->GetTexture(aiTextureType::aiTextureType_NORMALS, 0, &normalPath);
	{
		if (normalPath.length > 0)
		{
			wchar_t	wstr[512];
			size_t wLen = 0;
			mbstowcs_s(&wLen, wstr, normalPath.length + 1, normalPath.C_Str(), _TRUNCATE);
			std::wstring input = L"Resources/Textures/";
			input += wstr;

			auto texture = new JF::Texture();
			texture->SetTexture(gTEXTUREMGR->CreateTexture(input));

			_subset.m_Material.m_BumpTexture = texture;
		}
	}
}

void JF::JFMeshLoader::AICOLOR4toXMFLOAT4(IN aiColor4D& in, OUT XMFLOAT4& out)
{
	out = { in.r, in.g, in.b, in.a };
}