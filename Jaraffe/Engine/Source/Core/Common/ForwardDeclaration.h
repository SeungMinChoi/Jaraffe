#pragma once

namespace JF
{
	class JFCScene;

	class GameObject;

	namespace Component
	{
		class Mesh;
		class Light;

		class JFSpotLight;
		class JFPointLight;
		class JFDirectionalLight;
	}

	namespace RenderMap
	{
		class JFSSAO;
		class JFGBuffer;
	}
}