#pragma once

namespace Jaraffe
{

class RenderStates
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11RasterizerState* m_WireframeRS;
	static ID3D11RasterizerState* m_SolidRS;
};

}