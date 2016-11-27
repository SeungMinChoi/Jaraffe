#pragma once

namespace JF
{
namespace GeometryGenerator
{
	///<summary>
	/// 중점을 기준으로 주어진 값으로 박스를 생성합니다.
	///</summary>
	void CreateBox(float _width, float _height, float _depth, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// 중점을 기준으로 주어진 반지름을 바탕으로 원을 생성합니다.
	/// slices 와 stacks 을 바탕으로 좀더 많은 삼각형으로 반듯한 원을 생성합니다.
	///</summary>
	void CreateSphere(float _radius, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// 중점을 기준으로 주어진 반지름을 바탕으로 원을 생성합니다.
	/// _numSubdivisions 로 원을이루는 삼각형을 얼마나 세분화 할지 정할수있습니다.
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
	/// 삼각형을 세분화 합니다.
	///</summary>
	void Subdivide(std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);

	///<summary>
	/// 실린더의 윗부분.
	///</summary>
	void BuildCylinderTopCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);
	
	///<summary>
	/// 실린더의 아랫부분.
	///</summary>
	void BuildCylinderBottomCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices);
}
}