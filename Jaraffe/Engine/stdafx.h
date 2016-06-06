#pragma once

// Windows Header Files:
#include <windows.h>
#include <windowsx.h>

// DirectX11
#include <d3d11_1.h>
#include <d3dx11.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include <xnamath.h>

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

// Boost
#include <boost/any.hpp>

// Defines
#include "Common/Defines.h"

// ForwardDeclaration
#include "Common/ForwardDeclaration.h"

// Platform
#include "Source/Core/GenericPlatform/GenericPlatform.h"

// Interface
#include "Source/Interface/IObject.h"

// Renderer
#include "Source/RHI/D3D11/D3DDevice.h"

// Utils
#include "Source/Utils/GameTimer.h"
#include "Source/Utils/D3DUtil.h"

// 
#include "Source/D3D11/LightHelper.h"
#include "Source/D3D11/Effect.h"
#include "Source/D3D11/Vertex.h"
#include "Source/D3D11/RenderStates.h"

// Component Basic
#include "Source/Core/Object/CommonComponent.h"
#include "Source/Core/Object/BaseComponent.h"
#include "Source/Core/Object/GameObject.h"

// Components
#include "Source/Core/Object/Component/Transform.h"
#include "Source/Core/Object/Component/Camera.h"
#include "Source/Core/Object/Component/Mesh.h"

// Geometry
