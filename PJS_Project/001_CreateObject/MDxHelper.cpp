#include "MDxHelper.h"
namespace DX
{
	HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
	{
		HRESULT hr;
		ID3DBlob* pErrorCode = nullptr;
		hr = D3DCompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel, 0, 0, ppBlobOut, &pErrorCode);
		if (FAILED(hr))
		{
			if(pErrorCode != NULL)
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
			return hr;
		}
		pErrorCode->Release();

		return hr;
	}

	ID3D11VertexShader* LoadVertexShaderFile(ID3D11Device* _pd3dDevice, const void* pLoadShaderFiile, ID3DBlob** ppBlobOut, const char* pFunctionName, bool bBinary)
	{
		HRESULT hr;
		ID3D11VertexShader* pVertexShader;
		ID3DBlob* pVsBlob = NULL;
		DWORD dwSize = 0;
		LPCVOID lpData = NULL;
		if (bBinary == false)
		{
			if (pFunctionName == 0)
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pLoadShaderFiile, "VS", "vs_5_0", &pVsBlob)))
				{
					return nullptr;
				}
			}
			else
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pLoadShaderFiile, pFunctionName, "vs_5_0", &pVsBlob)))
				{
					return nullptr;
				}
			}
			dwSize = (DWORD)pVsBlob->GetBufferSize();
			lpData = pVsBlob->GetBufferPointer();
		}
		else
		{
			pVsBlob = *ppBlobOut;
			if (pVsBlob == nullptr)
				return nullptr;
			dwSize = (DWORD)pVsBlob->GetBufferSize();
			lpData = pVsBlob->GetBufferPointer();
		}
		if (FAILED(hr = _pd3dDevice->CreateVertexShader(lpData, dwSize, NULL, &pVertexShader)))
		{
			pVsBlob->Release();
			return nullptr;
		}
		if (ppBlobOut == nullptr)
			pVsBlob->Release();
		else
		{
			*ppBlobOut = pVsBlob;
		}
		return pVertexShader;
	}

	ID3D11PixelShader* LoadPixelShaderFile(ID3D11Device* _pd3dDevice, const void* pLoadShaderFiile, const char* pFunctionName, bool bBinary, ID3DBlob** ppBlobOut)
	{
		HRESULT hr;
		ID3D11PixelShader* pPixelShader;
		ID3DBlob* pPsBlob = nullptr;
		DWORD dwSize = 0;
		LPCVOID lpData;
		if (bBinary == false)
		{
			if (pFunctionName == 0)
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pLoadShaderFiile, "PS", "ps_5_0", &pPsBlob)))
				{
					return nullptr;
				}
			}
			else
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pLoadShaderFiile, pFunctionName, "ps_5_0", &pPsBlob)))
				{
					return nullptr;
				}
			}
			dwSize = (DWORD)pPsBlob->GetBufferSize();
			lpData = pPsBlob->GetBufferPointer();
		}
		else
		{
			dwSize = sizeof(pLoadShaderFiile);
			lpData = pLoadShaderFiile;
		}
		if (FAILED(hr = _pd3dDevice->CreatePixelShader(lpData, dwSize, NULL, &pPixelShader)))
		{
			pPsBlob->Release();
			return nullptr;
		}
		if (ppBlobOut == nullptr)
		{
			pPsBlob->Release();
		}
		else
		{
			*ppBlobOut = pPsBlob;
		}
		return pPixelShader;
	}
	ID3D11InputLayout* CreateInputlayout(ID3D11Device* pd3dDevice, DWORD dwSize, LPCVOID lpData, D3D11_INPUT_ELEMENT_DESC* layout, UINT numElements)
	{
		HRESULT hr;
		ID3D11InputLayout* pInputLayout = nullptr;
		if (FAILED(hr = pd3dDevice->CreateInputLayout(layout, numElements, lpData, dwSize, &pInputLayout)))
		{
			return nullptr;
		}
		return pInputLayout;
	}
	ID3D11Buffer* CreateVertexBuffer(ID3D11Device* pd3dDevice, void* vertices, UINT iNumVertex, UINT iVertexSize, bool bDynamic)
	{
		// 버텍스 4개로 사각형 생성
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;
		/*UINT ByteWidth;
		D3D11_USAGE Usage;
		UINT BindFlags;
		UINT CPUAccessFlags;
		UINT MiscFlags;
		UINT StructureByteStride;*/
		ZeroMemory(&bd, sizeof(bd));

		return nullptr;
	}
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* pd3dDevice, void* indices, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		return nullptr;
	}
	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* pd3dDevice, void* data, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		return nullptr;
	}
}
