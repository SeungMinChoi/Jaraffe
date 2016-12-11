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
#include <unordered_set>

// MSVC COM Support
#include <comip.h>
#include <comdef.h>

// C RunTime Header Files
#include <stdlib.h>
#include <memory.h>
#include <tchar.h>

// Windows Header Files:
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <psapi.h>

//=============================================================================
// 1) 3rdPartySDK
//=============================================================================

// JF Project
#include "JFCommonClasses.h"
#include "JFObjectClasses.h"

// DirectX11
#pragma warning( push )
#pragma warning( disable : 4005 4838  ) 
#include <d3d11_1.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <xnamath.h>

#include "d3dx11effect.h"
#pragma warning( pop )

// Physice
#include "PxPhysics.h"
#include "PxPhysicsAPI.h"

// Assimp
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//=============================================================================
// 2) Interface
//=============================================================================

//=============================================================================
// 3) Common
//=============================================================================
#include "Source/Core/Common/GlobalValues.h"
#include "Source/Core/Common/Exception/JFException.h"
#include "Source/Core/Common/Utile/JFUtile.h"
#include "Source/Core/Common/Timer/GameTimer.h"
#include "Source/Core/Common/GenericPlatformType.h"
#include "Source/Core/Common/ForwardDeclaration.h"

//=============================================================================
// 4) Manager
//=============================================================================
#include "Source/Core/Manager/Input/Input.h"

//=============================================================================
// 5) Platforms
//=============================================================================
#include "Source/Core/Platform/PlatformWindow/OS/JFPlatformWindows.h"

//=============================================================================
// 6) Device
//=============================================================================

// DirectX11
#include "Source/Core/Device/DirectX11/InterfacePointers.h"
#include "Source/Core/Device/DirectX11/JFDeviceDirectX11.h"

//=============================================================================
// 7) PhysX Mapping Classes
//=============================================================================
#include "Source/Core/PhysX/PhysXDevice.h"

//=============================================================================
// 8) RenderMap Classes
//=============================================================================
#include "Source/Core/RenderMap/JFSSAO.h"
#include "Source/Core/RenderMap/JFGBuffer.h"

//=============================================================================
// 9) Utiles
//=============================================================================
#include "Source/D3D11/LightHelper.h"
#include "Source/D3D11/Effect.h"
#include "Source/D3D11/Vertex.h"
#include "Source/D3D11/RenderStates.h"
#include "Source/D3D11/TextureMgr.h"

#include "Source/Utils/D3DUtil.h"
#include "Source/Utils/MathHelper.h"
#include "Source/Utils/GeometryGenerator.h"

//=============================================================================
// 10) App
//=============================================================================
#include "App/JFApp.h"
#include "App/JFWindowsApp.h"

//=============================================================================
// 11) Object
//=============================================================================
#include "Source/Core/Object/Object.h"
#include "Source/Core/Object/Texture.h"
#include "Source/Core/Object/Material.h"

//=============================================================================
// 12) Basic Component 
//=============================================================================
#include "Source/Core/Object/Component/Interface/CommonComponent.h"
#include "Source/Core/Object/Component/Interface/BaseComponent.h"
#include "Source/Core/Object/GameObject/GameObject.h"

//=============================================================================
// 13) Components
//=============================================================================
#include "Source/Core/Object/Component/Transform.h"
#include "Source/Core/Object/Component/Camera.h"
#include "Source/Core/Object/Component/Renderer.h"
#include "Source/Core/Object/Component/MeshRenderer.h"
#include "Source/Core/Object/Component/Mesh.h"
#include "Source/Core/Object/Component/Colision.h"
#include "Source/Core/Object/Component/ColisionBox.h"
#include "Source/Core/Object/Component/SkyBox.h"

#include "Source/Core/Object/Component/JFSpotLight.h"
#include "Source/Core/Object/Component/JFPointLight.h"
#include "Source/Core/Object/Component/JFDirectionalLight.h"

//=============================================================================
// 14) Scene
//=============================================================================
#include "Source/Core/Scene/Scene.h"

//=============================================================================
// 15) Loader
//=============================================================================
#include "Source/Utils/MeshLoader.h"
#include "Source/Utils/JFMeshLoader.h"

// Debug
#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

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