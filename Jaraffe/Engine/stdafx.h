#pragma once

//Debug 
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

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

// DirectX11 lib
#include <d3dx11effect.h>

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
