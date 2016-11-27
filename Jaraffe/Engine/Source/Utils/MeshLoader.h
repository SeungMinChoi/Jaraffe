#pragma once

namespace JF
{
class Material;
namespace MeshLoader
{
	///<summary>
	/// OBJ 파일을 파싱하는 함수. ( Subset 은 일단 뺏다. -> 이후 리펙토링 or 포폴이 아닌 엔진 새로만들때 Hiraraki 구조로 해야한다. )
	///</summary>
	bool OBJLoad(IN const std::wstring& _filePath, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices, OUT JF::Material& _material);
	
	///<summary>
	/// OBJ 파일의 Material 정보를 얻는 함수.
	///</summary>
	void ProcessMtl(IN LPCWSTR _wfilename, OUT JF::Material& _material);

	///<summary>
	/// 노말값,탄젠트값 계산 ( 탄젠트는 일단 제외 )
	///</summary>
	void ComputeNomalAndTangent(IN const int& _triangleCnt, IN const int& _vertexCnt, OUT std::vector<Vertex::PosNormalTexTan>& _vertices, OUT std::vector<UINT>& _indices);
}
}