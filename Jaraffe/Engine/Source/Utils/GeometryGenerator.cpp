#include "stdafx.h"
#include "GeometryGenerator.h"

void JF::GeometryGenerator::CreateBox(float _width, float _height, float _depth, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	//
	// Create the vertices.
	//

	Vertex::PosNormalTexTan v[24];

	float w2 = 0.5f*_width;
	float h2 = 0.5f*_height;
	float d2 = 0.5f*_depth;

	// Fill in the front face vertex data.
	v[0] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[1] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[2] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[3] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	// Fill in the back face vertex data.
	v[4] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[5] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[6] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[7] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));

	// Fill in the top face vertex data.
	v[8] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[9] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[10] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	v[11] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	// Fill in the bottom face vertex data.
	v[12] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[13] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[14] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));
	v[15] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(-1.0f, 0.0f, 0.0f, 1.0f));

	// Fill in the left face vertex data.
	v[16] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, +d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f));
	v[17] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, +d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f));
	v[18] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, +h2, -d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f));
	v[19] = Vertex::PosNormalTexTan(XMFLOAT3(-w2, -h2, -d2), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, -1.0f, 1.0f));

	// Fill in the right face vertex data.
	v[20] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, -d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	v[21] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, -d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	v[22] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, +h2, +d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	v[23] = Vertex::PosNormalTexTan(XMFLOAT3(+w2, -h2, +d2), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT2(1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

	_vertices.assign(&v[0], &v[24]);

	//
	// Create the indices.
	//

	UINT i[36];

	// Fill in the front face index data
	i[0] = 0; i[1] = 1; i[2] = 2;
	i[3] = 0; i[4] = 2; i[5] = 3;

	// Fill in the back face index data
	i[6] = 4; i[7] = 5; i[8] = 6;
	i[9] = 4; i[10] = 6; i[11] = 7;

	// Fill in the top face index data
	i[12] = 8; i[13] = 9; i[14] = 10;
	i[15] = 8; i[16] = 10; i[17] = 11;

	// Fill in the bottom face index data
	i[18] = 12; i[19] = 13; i[20] = 14;
	i[21] = 12; i[22] = 14; i[23] = 15;

	// Fill in the left face index data
	i[24] = 16; i[25] = 17; i[26] = 18;
	i[27] = 16; i[28] = 18; i[29] = 19;

	// Fill in the right face index data
	i[30] = 20; i[31] = 21; i[32] = 22;
	i[33] = 20; i[34] = 22; i[35] = 23;

	_indices.assign(&i[0], &i[36]);
}

void JF::GeometryGenerator::CreateSphere(float _radius, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	_vertices.clear();
	_indices.clear();

	//
	// Compute the vertices stating at the top pole and moving down the stacks.
	//

	// Poles: note that there will be texture coordinate distortion as there is
	// not a unique m_Point on the texture map to assign to the pole when mapping
	// a rectangular texture onto a sphere.
	Vertex::PosNormalTexTan topVertex(XMFLOAT3(0.0f, +_radius, 0.0f), XMFLOAT3(0.0f, +1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Vertex::PosNormalTexTan bottomVertex(XMFLOAT3(0.0f, -_radius, 0.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	_vertices.push_back(topVertex);

	float phiStep = XM_PI / _stackCount;
	float thetaStep = 2.0f*XM_PI / _sliceCount;

	// Compute vertices for each stack ring (do not count the poles as rings).
	for (UINT i = 1; i <= _stackCount - 1; ++i)
	{
		float phi = i*phiStep;

		// Vertices of ring.
		for (UINT j = 0; j <= _sliceCount; ++j)
		{
			float theta = j*thetaStep;

			Vertex::PosNormalTexTan v;

			// spherical to cartesian
			v.Pos.x = _radius*sinf(phi)*cosf(theta);
			v.Pos.y = _radius*cosf(phi);
			v.Pos.z = _radius*sinf(phi)*sinf(theta);

			// Partial derivative of P with respect to theta
			v.Tan.x = -_radius*sinf(phi)*sinf(theta);
			v.Tan.y = 0.0f;
			v.Tan.z = +_radius*sinf(phi)*cosf(theta);
			v.Tan.w = 1.0f;

			XMVECTOR p = XMLoadFloat3(&v.Pos);
			XMStoreFloat3(&v.Normal, XMVector3Normalize(p));

			XMVECTOR T = XMLoadFloat4(&v.Tan);
			XMStoreFloat4(&v.Tan, XMVector3Normalize(T));

			v.Tex.x = theta / XM_2PI;
			v.Tex.y = phi / XM_PI;

			_vertices.push_back(v);
		}
	}

	_vertices.push_back(bottomVertex);

	//
	// Compute indices for top stack.  The top stack was written first to the vertex buffer
	// and connects the top pole to the first ring.
	//

	for (UINT i = 1; i <= _sliceCount; ++i)
	{
		_indices.push_back(0);
		_indices.push_back(i + 1);
		_indices.push_back(i);
	}

	//
	// Compute indices for inner stacks (not connected to poles).
	//

	// Offset the indices to the index of the first vertex in the first ring.
	// This is just skipping the top pole vertex.
	UINT baseIndex = 1;
	UINT ringVertexCount = _sliceCount + 1;
	for (UINT i = 0; i < _stackCount - 2; ++i)
	{
		for (UINT j = 0; j < _sliceCount; ++j)
		{
			_indices.push_back(baseIndex + i*ringVertexCount + j);
			_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);

			_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j);
			_indices.push_back(baseIndex + i*ringVertexCount + j + 1);
			_indices.push_back(baseIndex + (i + 1)*ringVertexCount + j + 1);
		}
	}

	//
	// Compute indices for bottom stack.  The bottom stack was written last to the vertex buffer
	// and connects the bottom pole to the bottom ring.
	//

	// South pole vertex was added last.
	UINT southPoleIndex = (UINT)_vertices.size() - 1;

	// Offset the indices to the index of the first vertex in the last ring.
	baseIndex = southPoleIndex - ringVertexCount;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_indices.push_back(southPoleIndex);
		_indices.push_back(baseIndex + i);
		_indices.push_back(baseIndex + i + 1);
	}
}

void JF::GeometryGenerator::CreateGeosphere(float _radius, UINT _numSubdivisions, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	// Put a cap on the number of subdivisions.
	_numSubdivisions = JF::Util::MathHelper::Min(_numSubdivisions, 5u);

	// Approximate a sphere by tessellating an icosahedron.

	const float X = 0.525731f;
	const float Z = 0.850651f;

	XMFLOAT3 pos[12] =
	{
		XMFLOAT3(-X, 0.0f, Z),  XMFLOAT3(X, 0.0f, Z),
		XMFLOAT3(-X, 0.0f, -Z), XMFLOAT3(X, 0.0f, -Z),
		XMFLOAT3(0.0f, Z, X),   XMFLOAT3(0.0f, Z, -X),
		XMFLOAT3(0.0f, -Z, X),  XMFLOAT3(0.0f, -Z, -X),
		XMFLOAT3(Z, X, 0.0f),   XMFLOAT3(-Z, X, 0.0f),
		XMFLOAT3(Z, -X, 0.0f),  XMFLOAT3(-Z, -X, 0.0f)
	};

	DWORD k[60] =
	{
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8, 10,3,8, 8,3,5,  3,2,5,  3,7,2,
		3,10,7, 10,6,7, 6,11,7, 6,0,11, 6,1,0,
		10,1,6, 11,0,9, 2,11,9, 5,2,9,  11,2,7
	};

	_vertices.resize(12);
	_indices.resize(60);

	for (UINT i = 0; i < 12; ++i)
		_vertices[i].Pos = pos[i];

	for (UINT i = 0; i < 60; ++i)
		_indices[i] = k[i];

	for (UINT i = 0; i < _numSubdivisions; ++i)
		Subdivide(_vertices, _indices);

	// Project vertices onto sphere and scale.
	for (UINT i = 0; i < _vertices.size(); ++i)
	{
		// Project onto unit sphere.
		XMVECTOR n = XMVector3Normalize(XMLoadFloat3(&_vertices[i].Pos));

		// Project onto sphere.
		XMVECTOR p = _radius*n;

		XMStoreFloat3(&_vertices[i].Pos, p);
		XMStoreFloat3(&_vertices[i].Normal, n);

		// Derive texture coordinates from spherical coordinates.
		float theta = JF::Util::MathHelper::AngleFromXY(
			_vertices[i].Pos.x,
			_vertices[i].Pos.z);

		float phi = acosf(_vertices[i].Pos.y / _radius);

		_vertices[i].Tex.x = theta / XM_2PI;
		_vertices[i].Tex.y = phi / XM_PI;

		// Partial derivative of P with respect to theta
		_vertices[i].Tan.x = -_radius*sinf(phi)*sinf(theta);
		_vertices[i].Tan.y = 0.0f;
		_vertices[i].Tan.z = +_radius*sinf(phi)*cosf(theta);
		_vertices[i].Tan.w = 1.0f;

		XMVECTOR T = XMLoadFloat4(&_vertices[i].Tan);
		XMStoreFloat4(&_vertices[i].Tan, XMVector3Normalize(T));
	}
}

void JF::GeometryGenerator::CreateCylinder(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	_vertices.clear();
	_indices.clear();

	//
	// Build Stacks.
	// 

	float stackHeight = _height / _stackCount;

	// Amount to increment radius as we move up each stack level from bottom to top.
	float radiusStep = (_topRadius - _bottomRadius) / _stackCount;

	UINT ringCount = _stackCount + 1;

	// Compute vertices for each stack ring starting at the bottom and moving up.
	for (UINT i = 0; i < ringCount; ++i)
	{
		float y = -0.5f*_height + i*stackHeight;
		float r = _bottomRadius + i*radiusStep;

		// vertices of ring
		float dTheta = 2.0f*XM_PI / _sliceCount;
		for (UINT j = 0; j <= _sliceCount; ++j)
		{
			Vertex::PosNormalTexTan vertex;

			float c = cosf(j*dTheta);
			float s = sinf(j*dTheta);

			vertex.Pos = XMFLOAT3(r*c, y, r*s);

			vertex.Tex.x = (float)j / _sliceCount;
			vertex.Tex.y = 1.0f - (float)i / _stackCount;

			// Cylinder can be parameterized as follows, where we introduce v
			// parameter that goes in the same direction as the v tex-coord
			// so that the bitangent goes in the same direction as the v tex-coord.
			//   Let r0 be the bottom radius and let r1 be the top radius.
			//   y(v) = h - hv for v in [0,1].
			//   r(v) = r1 + (r0-r1)v
			//
			//   x(t, v) = r(v)*cos(t)
			//   y(t, v) = h - hv
			//   z(t, v) = r(v)*sin(t)
			// 
			//  dx/dt = -r(v)*sin(t)
			//  dy/dt = 0
			//  dz/dt = +r(v)*cos(t)
			//
			//  dx/dv = (r0-r1)*cos(t)
			//  dy/dv = -h
			//  dz/dv = (r0-r1)*sin(t)

			// This is unit length.
			vertex.Tan = XMFLOAT4(-s, 0.0f, c, 1.0f);

			float dr = _bottomRadius - _topRadius;
			XMFLOAT3 bitangent(dr*c, -_height, dr*s);

			XMVECTOR T = XMLoadFloat4(&vertex.Tan);
			XMVECTOR B = XMLoadFloat3(&bitangent);
			XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));
			XMStoreFloat3(&vertex.Normal, N);

			_vertices.push_back(vertex);
		}
	}

	// Add one because we duplicate the first and last vertex per ring
	// since the texture coordinates are different.
	UINT ringVertexCount = _sliceCount + 1;

	// Compute indices for each stack.
	for (UINT i = 0; i < _stackCount; ++i)
	{
		for (UINT j = 0; j < _sliceCount; ++j)
		{
			_indices.push_back(i*ringVertexCount + j);
			_indices.push_back((i + 1)*ringVertexCount + j);
			_indices.push_back((i + 1)*ringVertexCount + j + 1);

			_indices.push_back(i*ringVertexCount + j);
			_indices.push_back((i + 1)*ringVertexCount + j + 1);
			_indices.push_back(i*ringVertexCount + j + 1);
		}
	}

	BuildCylinderTopCap(_bottomRadius, _topRadius, _height, _sliceCount, _stackCount, _vertices, _indices);
	BuildCylinderBottomCap(_bottomRadius, _topRadius, _height, _sliceCount, _stackCount, _vertices, _indices);
}

void JF::GeometryGenerator::CreateGrid(float _width, float _depth, UINT _m, UINT _n, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	UINT vertexCount = _m*_n;
	UINT faceCount = (_m - 1)*(_n - 1) * 2;

	//
	// Create the vertices.
	//

	float halfWidth = 0.5f*_width;
	float halfDepth = 0.5f*_depth;

	float dx = _width / (_n - 1);
	float dz = _depth / (_m - 1);

	float du = 1.0f / (_n - 1);
	float dv = 1.0f / (_m - 1);

	_vertices.resize(vertexCount);
	for (UINT i = 0; i < _m; ++i)
	{
		float z = halfDepth - i*dz;
		for (UINT j = 0; j < _n; ++j)
		{
			float x = -halfWidth + j*dx;

			_vertices[i*_n + j].Pos		= XMFLOAT3(x, 0.0f, z);
			_vertices[i*_n + j].Normal	= XMFLOAT3(0.0f, 1.0f, 0.0f);
			_vertices[i*_n + j].Tan		= XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

			// Stretch texture over grid.
			_vertices[i*_n + j].Tex.x = j*du;
			_vertices[i*_n + j].Tex.y = i*dv;
		}
	}

	//
	// Create the indices.
	//

	_indices.resize(faceCount * 3); // 3 indices per face

											// Iterate over each quad and compute indices.
	UINT k = 0;
	for (UINT i = 0; i < _m - 1; ++i)
	{
		for (UINT j = 0; j < _n - 1; ++j)
		{
			_indices[k] = i*_n + j;
			_indices[k + 1] = i*_n + j + 1;
			_indices[k + 2] = (i + 1)*_n + j;

			_indices[k + 3] = (i + 1)*_n + j;
			_indices[k + 4] = i*_n + j + 1;
			_indices[k + 5] = (i + 1)*_n + j + 1;

			k += 6; // next quad
		}
	}
}

void JF::GeometryGenerator::CreateFullscreenQuad(std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	_vertices.resize(4);
	_indices.resize(6);

	// Position coordinates specified in NDC space.
	_vertices[0] = Vertex::PosNormalTexTan(
		XMFLOAT3(-1.0f, -1.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT2(0.0f, 1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	_vertices[1] = Vertex::PosNormalTexTan(
		XMFLOAT3(-1.0f, +1.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT2(0.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	_vertices[2] = Vertex::PosNormalTexTan(
		XMFLOAT3(+1.0f, +1.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT2(1.0f, 0.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	_vertices[3] = Vertex::PosNormalTexTan(
		XMFLOAT3(+1.0f, -1.0f, 0.0f),
		XMFLOAT3(0.0f, 0.0f, -1.0f),
		XMFLOAT2(1.0f, 1.0f),
		XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

	_indices[0] = 0;
	_indices[1] = 1;
	_indices[2] = 2;

	_indices[3] = 0;
	_indices[4] = 2;
	_indices[5] = 3;
}

void JF::GeometryGenerator::Subdivide(std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	// Save a copy of the input geometry.
	std::vector<Vertex::PosNormalTexTan> inputCopyVertices;
	std::vector<UINT> inputCopyIndices;

	inputCopyVertices.assign(_vertices.begin(), _vertices.end());
	inputCopyIndices.assign(_indices.begin(), _indices.end());

	_vertices.resize(0);
	_indices.resize(0);

	//       v1
	//       *
	//      / \
		//     /   \
	//  m0*-----*m1
//   / \   / \
	//  /   \ /   \
	// *-----*-----*
// v0    m2     v2

	UINT numTris = inputCopyIndices.size() / 3;
	for (UINT i = 0; i < numTris; ++i)
	{
		Vertex::PosNormalTexTan v0 = inputCopyVertices[inputCopyIndices[i * 3 + 0]];
		Vertex::PosNormalTexTan v1 = inputCopyVertices[inputCopyIndices[i * 3 + 1]];
		Vertex::PosNormalTexTan v2 = inputCopyVertices[inputCopyIndices[i * 3 + 2]];

		//
		// Generate the midpoints.
		//

		Vertex::PosNormalTexTan m0, m1, m2;

		// For subdivision, we just care about the position component.  We derive the other
		// vertex components in CreateGeosphere.

		m0.Pos = XMFLOAT3(
			0.5f*(v0.Pos.x + v1.Pos.x),
			0.5f*(v0.Pos.y + v1.Pos.y),
			0.5f*(v0.Pos.z + v1.Pos.z));

		m1.Pos = XMFLOAT3(
			0.5f*(v1.Pos.x + v2.Pos.x),
			0.5f*(v1.Pos.y + v2.Pos.y),
			0.5f*(v1.Pos.z + v2.Pos.z));

		m2.Pos = XMFLOAT3(
			0.5f*(v0.Pos.x + v2.Pos.x),
			0.5f*(v0.Pos.y + v2.Pos.y),
			0.5f*(v0.Pos.z + v2.Pos.z));

		//
		// Add new geometry.
		//

		_vertices.push_back(v0); // 0
		_vertices.push_back(v1); // 1
		_vertices.push_back(v2); // 2
		_vertices.push_back(m0); // 3
		_vertices.push_back(m1); // 4
		_vertices.push_back(m2); // 5

		_indices.push_back(i * 6 + 0);
		_indices.push_back(i * 6 + 3);
		_indices.push_back(i * 6 + 5);

		_indices.push_back(i * 6 + 3);
		_indices.push_back(i * 6 + 4);
		_indices.push_back(i * 6 + 5);

		_indices.push_back(i * 6 + 5);
		_indices.push_back(i * 6 + 4);
		_indices.push_back(i * 6 + 2);

		_indices.push_back(i * 6 + 3);
		_indices.push_back(i * 6 + 1);
		_indices.push_back(i * 6 + 4);
	}
}

void JF::GeometryGenerator::BuildCylinderTopCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	UINT baseIndex = (UINT)_vertices.size();

	float y = 0.5f*_height;
	float dTheta = 2.0f*XM_PI / _sliceCount;

	// Duplicate cap ring vertices because the texture coordinates and normals differ.
	for (UINT i = 0; i <= _sliceCount; ++i)
	{
		float x = _topRadius*cosf(i*dTheta);
		float z = _topRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float v = z / _height + 0.5f;
		float u = x / _height + 0.5f;

		_vertices.push_back(Vertex::PosNormalTexTan(x, y, z, 0.0f, 1.0f, 0.0f, u, v, 1.0f, 0.0f, 0.0f, 1.0f));
	}

	// Cap center vertex.
	_vertices.push_back(Vertex::PosNormalTexTan(0.0f, y, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f));

	// Index of center vertex.
	UINT centerIndex = (UINT)_vertices.size() - 1;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_indices.push_back(centerIndex);
		_indices.push_back(baseIndex + i + 1);
		_indices.push_back(baseIndex + i);
	}
}

void JF::GeometryGenerator::BuildCylinderBottomCap(float _bottomRadius, float _topRadius, float _height, UINT _sliceCount, UINT _stackCount, std::vector<Vertex::PosNormalTexTan>& _vertices, std::vector<UINT>& _indices)
{
	// 
	// Build bottom cap.
	//

	UINT baseIndex = (UINT)_vertices.size();
	float y = -0.5f*_height;

	// vertices of ring
	float dTheta = 2.0f*XM_PI / _sliceCount;
	for (UINT i = 0; i <= _sliceCount; ++i)
	{
		float x = _bottomRadius*cosf(i*dTheta);
		float z = _bottomRadius*sinf(i*dTheta);

		// Scale down by the height to try and make top cap texture coord area
		// proportional to base.
		float u = x / _height + 0.5f;
		float v = z / _height + 0.5f;

		_vertices.push_back(Vertex::PosNormalTexTan(x, y, z, 0.0f, -1.0f, 0.0f, u, v, 1.0f, 0.0f, 0.0f, 1.0f));
	}

	// Cap center vertex.
	_vertices.push_back(Vertex::PosNormalTexTan(0.0f, y, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f));

	// Cache the index of center vertex.
	UINT centerIndex = (UINT)_vertices.size() - 1;

	for (UINT i = 0; i < _sliceCount; ++i)
	{
		_indices.push_back(centerIndex);
		_indices.push_back(baseIndex + i);
		_indices.push_back(baseIndex + i + 1);
	}
}