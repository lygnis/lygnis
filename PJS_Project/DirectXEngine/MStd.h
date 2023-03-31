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
class Input;
class TransformComponent;
class MeshComponent;
class CameraComponent;
class World;
class Entity;
class Component;
class FbxLoader;
class MFbxObject;

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
typedef std::shared_ptr<MFbxObject> MFbxObjectPtr;

typedef std::basic_string<wchar_t> W_STR;
typedef std::basic_string<char>  C_STR;

enum class CameraType
{
	ORTHOGONAL =0,
	PERSPECTIVE
};


static bool GetWtM(const WCHAR* src, char* pDest)
{
	// 변형되는 문자열의 크기가 반환된다.
	int iLength = WideCharToMultiByte(CP_ACP, 0,
		src, -1, 0, 0, NULL, NULL);
	int iRet = WideCharToMultiByte(CP_ACP, 0,
		src, -1,  //  소스
		pDest, iLength, // 대상
		NULL, NULL);
	if (iRet == 0) return false;
	return true;
}

#define DX3DError(message) \
{\
std::wclog << "DX3D Error : " << message << std::endl; \
throw std::runtime_error("");\
}

#define DX3DWarning(message) \
std::wclog << "DX3D Error : " << message << std::endl;

#define DX3DInfo(message) \
std::wclog << "DX3D Info : " << message << std::endl;