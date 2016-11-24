#pragma once

namespace Jaraffe
{
class Material;
namespace MeshLoader
{
	///<summary>
	/// OBJ ������ �Ľ��ϴ� �Լ�. ( Subset �� �ϴ� ����. -> ���� �����丵 or ������ �ƴ� ���� ���θ��鶧 Hiraraki ������ �ؾ��Ѵ�. )
	///</summary>
	bool OBJLoad(IN const std::wstring& _filePath, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices, OUT Jaraffe::Material& _material);
	
	///<summary>
	/// OBJ ������ Material ������ ��� �Լ�.
	///</summary>
	void ProcessMtl(IN LPCWSTR _wfilename, OUT Jaraffe::Material& _material);

	///<summary>
	/// �븻��,ź��Ʈ�� ��� ( ź��Ʈ�� �ϴ� ���� )
	///</summary>
	void ComputeNomalAndTangent(IN const int& _triangleCnt, IN const int& _vertexCnt, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices);
}
}