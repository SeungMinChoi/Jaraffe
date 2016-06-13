#pragma once

namespace Jaraffe
{
	class CScene;
	class CD3DDevice;

	class Effect;
	class SimpleEffect;
	class PosNormalEffect;
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

