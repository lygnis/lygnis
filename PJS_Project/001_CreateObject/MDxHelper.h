#pragma once
#pragma comment(lib, "DirectXTK.lib")
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h" 
#include "TStd.h"
namespace DX
{
	////////////////////////// 아래의 경고가 있을 경우 사용한다.
	// 이와 같은 경고는 이미 쉐이더 파이프라인에 할당(리소스 및 상태값들이)되어 사용 중일 경우에 발생한다.
	//D3D11 WARNING : ID3D11DeviceContext::SOSetTargets : Resource being set to SO buffer slot 0 is still bound on input![STATE_SETTING WARNING #10: DEVICE_SOSETTARGETS_HAZARD]
	//D3D11 WARNING : ID3D11DeviceContext::SOSetTargets : Forcing Vertex Buffer slot 0 to NULL.[STATE_SETTING WARNING #1: DEVICE_IASETVERTEXBUFFERS_HAZARD]
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	ID3D11VertexShader* LoadVertexShaderFile(ID3D11Device* _pd3dDevice, const void* pLoadShaderFiile, ID3DBlob** ppBlobOut = nullptr, const char* pFunctionName = 0, bool bBinary = false);
	ID3D11PixelShader*	LoadPixelShaderFile(ID3D11Device* _pd3dDevice, const void* pLoadShaderFiile, const char* pFunctionName = 0, bool bBinary = false, ID3DBlob** ppBlobOut = nullptr);

	ID3D11InputLayout*	CreateInputlayout(ID3D11Device* pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements);
	ID3D11Buffer*		CreateVertexBuffer(ID3D11Device* pd3dDevice, void* vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic = false);
	ID3D11Buffer*		CreateIndexBuffer(ID3D11Device* pd3dDevice, void* indices, UINT iNumIndex, UINT iSize, bool bDynamic = false);
	ID3D11Buffer*		CreateConstantBuffer(ID3D11Device* pd3dDevice, void* data, UINT iNumIndex, UINT iSize, bool bDynamic = false);
	class MDxHelper
	{
	public:
		Microsoft::WRL::ComPtr<ID3D11Buffer>			g_pVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			g_pIndexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer>			g_pConstantBuffer;
		Microsoft::WRL::ComPtr<ID3D11VertexShader>		g_pVertexShader;
		Microsoft::WRL::ComPtr<ID3D11PixelShader>		g_pPixelShader;
		Microsoft::WRL::ComPtr<ID3DBlob>				g_pVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob>				g_pPSBlob;


		Microsoft::WRL::ComPtr<ID3D11InputLayout>			g_pInputlayout;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	g_pTextureSRV;


		UINT				m_iNumVertex;
		UINT				m_iVertexSize;
	};
}

