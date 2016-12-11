#pragma once

namespace JF
{

class JFMeshLoader
{
public:
	JFMeshLoader();
	virtual ~JFMeshLoader();

public:
	bool OBJLoad(IN const std::string& _filePath, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices, OUT std::vector<Mesh::Subset>& _subset);

private:
	bool InitFromScene
		( IN const aiScene* pScene
		, IN const char* Filename
		, OUT std::vector<Vertex::PosNormalTexTan>& vertices
		, OUT std::vector<UINT>& indices
		, OUT std::vector<Mesh::Subset>& _subset);

	void ProcessMesh
		( IN aiMesh* pMesh
		, OUT std::vector<Vertex::PosNormalTexTan>& vertices
		, OUT std::vector<UINT>& indices);

	void ProcessMaterial
		( IN const aiScene* pScene
		, IN aiMesh* pMesh
		, OUT Mesh::Subset& _subset);

private: // helper
	void AICOLOR4toXMFLOAT4(IN aiColor4D& in, OUT XMFLOAT4& out);
};

}