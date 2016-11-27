#pragma once

namespace JF
{
namespace GeometryGenerator
{
	///<summary>
	/// ������ �������� �־��� ������ �ڽ��� �����մϴ�.
	///</summary>
	void CreateBox(float _width, float _height, float _depth, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// ������ �������� �־��� �������� �������� ���� �����մϴ�.
	/// slices �� stacks �� �������� ���� ���� �ﰢ������ �ݵ��� ���� �����մϴ�.
	///</summary>
	void CreateSphere(float _radius, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// ������ �������� �־��� �������� �������� ���� �����մϴ�.
	/// _numSubdivisions �� �����̷�� �ﰢ���� �󸶳� ����ȭ ���� ���Ҽ��ֽ��ϴ�.
	///</summary>
	void CreateGeosphere(float _radius, UINT _numSubdivisions, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// Creates a cylinder parallel to the y-axis, and centered about the origin.  
	/// The bottom and top radius can vary to form various cone shapes rather than true
	/// cylinders.  The slices and stacks parameters control the degree of tessellation.
	///</summary>
	void CreateCylinder(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// Creates an mxn grid in the xz-plane with m rows and n columns, centered
	/// at the origin with the specified width and depth.
	///</summary>
	void CreateGrid(float _width, float _depth, UINT _m, UINT _n, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// Creates a quad covering the screen in NDC coordinates.  This is useful for
	/// postprocessing effects.
	///</summary>
	void CreateFullscreenQuad(std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// �ﰢ���� ����ȭ �մϴ�.
	///</summary>
	void Subdivide(std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// �Ǹ����� ���κ�.
	///</summary>
	void BuildCylinderTopCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);
	
	///<summary>
	/// �Ǹ����� �Ʒ��κ�.
	///</summary>
	void BuildCylinderBottomCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);
}
}