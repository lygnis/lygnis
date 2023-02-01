#pragma once
#include <d3d11.h>
#include <cassert>
#include <memory>
#include <wrl.h>
#include<d3dcompiler.h>
#include <iostream>
#include "TMath.h"

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
class Texture;
class TextureManager;
class Mesh;
class MeshManager;

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
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;