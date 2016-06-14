#pragma once

// TODO : 이후 구조 잡고 리펙토링 할때 이부분 없어지거나 이동할수있음. ( 그냥 어느정도 만들고 다시 처음부터 짜는게 빠를지도?.. )
namespace Jaraffe
{
	class CScene;
	class CD3DDevice;

	class Effect;
	class SimpleEffect;
	class BasicEffect;
	class Effects;

	class InputLayoutDesc;
	class InputLayouts;

	struct DirectionalLight;
	struct PointLight;
	struct SpotLight;
	struct Material;

	namespace Component
	{
		class Transform;
		class Camera;
		class Renderer;
		class Mesh;
		class Light;
		class Material;
	}

	namespace Util
	{
		class CGameTimer;
		class MyDirectUtil;
		class MathHelper;
	}

	namespace Geometry
	{
	}
}

