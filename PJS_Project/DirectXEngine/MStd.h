#pragma once
#include <d3d11.h>
#include <cassert>
#include <memory>
#include <wrl.h>
#include<d3dcompiler.h>
#include <iostream>
#include "TMath.h"
#include <stdexcept>

class MSwapChain;
class DeviceContext;
class MVertexShader;
class PixelShader;
class ConstantBuffer;
class MGraphicsEngine;
class IndexBuffer;
class RenderSystem;
class MVertexBuffer;
class Resource;
class ResourceManager;
class Texture2D;
class Texture;
class TextureManager;
class Mesh;
class MeshManager;
class Material;
class MWindow;
class Game;
class Display;

using namespace Microsoft::WRL;
using namespace TBASIS_EX;
extern HWND g_hWnd;

typedef std::shared_ptr<MSwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<MVertexBuffer> MVertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<MVertexShader> MVertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Texture2D> Texture2DPtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Material> MaterialPtr;



#define DX3DError(message) \
{\
std::wclog << "DX3D Error : " << message << std::endl; \
throw std::runtime_error("");\
}

#define DX3DWarning(message) \
std::wclog << "DX3D Error : " << message << std::endl;

#define DX3DInfo(message) \
std::wclog << "DX3D Info : " << message << std::endl;