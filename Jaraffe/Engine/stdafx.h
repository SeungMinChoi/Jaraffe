#pragma once

// Windows Header Files:
#include <windows.h>
#include <windowsx.h>

// DirectX11
#pragma warning( push )
#pragma warning( disable : 4005 4838  ) 
#include <d3d11_1.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <xnamath.h>
#pragma warning( pop )

// DirectX11 Utile
#include "d3dx11effect.h"

// PhsyX
#include <unordered_set>

#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

//Debug 
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <float.h>
#include <cmath>

// Boost

// Defines
#include "JFCommonClasses.h"

//
#include "JFObjectClasses.h"

// Platform
#include "Source/Core/GenericPlatform/GenericPlatform.h"

// Interface


// Renderer
#include "Source/RHI/D3D11/D3DDevice.h"

// Utils
#include "Source/Utils/GameTimer.h"
#include "Source/Utils/D3DUtil.h"
#include "Source/Utils/MathHelper.h"

// 
#include "Source/D3D11/LightHelper.h"
#include "Source/D3D11/Effect.h"
#include "Source/D3D11/Vertex.h"
#include "Source/D3D11/RenderStates.h"
#include "Source/D3D11/TextureMgr.h"

// Object
#include "Source/Core/Object/Object.h"
#include "Source/Core/Object/Texture.h"
#include "Source/Core/Object/Material.h"

// Component Basic
#include "Source/Core/Object/Component/Interface/CommonComponent.h"
#include "Source/Core/Object/Component/Interface/BaseComponent.h"
#include "Source/Core/Object/GameObject/GameObject.h"

// Components
#include "Source/Core/Object/Component/Transform.h"
#include "Source/Core/Object/Component/Camera.h"
#include "Source/Core/Object/Component/Renderer.h"
#include "Source/Core/Object/Component/MeshRenderer.h"
#include "Source/Core/Object/Component/Light.h"
#include "Source/Core/Object/Component/Mesh.h"

// Geometry

// PhysX Class's
#include "Source/PhysX/PhysXDevice.h"

// Libs
#ifdef _DEBUG
	#pragma comment(lib, "PhysX3DEBUG_x64.lib")				//Always be needed  
	#pragma comment(lib, "PhysX3CommonDEBUG_x64.lib")		//Always be needed
	#pragma comment(lib, "PhysXProfileSDKDEBUG.lib")		//PhysX extended library 
	#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")		//PhysX extended library 
	#pragma comment(lib, "PhysXVisualDebuggerSDKDEBUG.lib") //For PVD only 
	
	#pragma comment(lib, "Effects11d.lib")
#else
	#pragma comment(lib, "PhysX3_x64.lib")	
	#pragma comment(lib, "PhysX3Common_x64.lib") 
	#pragma comment(lib, "PhysXProfileSDK.lib")
	#pragma comment(lib, "PhysX3Extensions.lib")
	#pragma comment(lib, "PhysXVisualDebuggerSDK.lib")

	#pragma comment(lib, "Effects11.lib")
#endif