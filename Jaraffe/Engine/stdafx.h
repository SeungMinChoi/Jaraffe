#pragma once

// Add common controls 6.0 DLL to the manifest
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

// Platform SDK defines, specifies that our min version is Windows Vista
#ifndef WINVER
#define WINVER 0x0600
#endif

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0410
#endif

#ifndef _WIN32_IE
#define _WIN32_IE 0x0700
#endif

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define STRICT							// Use strict declarations for Windows types

// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <psapi.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// C++ Standard Library Header Files
#include <functional>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <cmath>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <unordered_map>
#include <float.h>

// MSVC COM Support
#include <comip.h>
#include <comdef.h>

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

// 
#include "Source/D3D11/InterfacePointers.h"
#include "Source/D3D11/LightHelper.h"
#include "Source/D3D11/Effect.h"
#include "Source/D3D11/Vertex.h"
#include "Source/D3D11/RenderStates.h"
#include "Source/D3D11/TextureMgr.h"
#include "Source/D3D11/Input.h"

// Utils
#include "Source/Utils/GameTimer.h"
#include "Source/Utils/D3DUtil.h"
#include "Source/Utils/MathHelper.h"
#include "Source/Utils/GeometryGenerator.h"
#include "Source/Utils/MeshLoader.h"

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
#include "Source/Core/Object/Component/Colision.h"
#include "Source/Core/Object/Component/ColisionBox.h"
#include "Source/Core/Object/Component/CubeMap.h"

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