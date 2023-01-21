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
			assert(false);
			if(pErrorCode != NULL)
				OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
			pErrorCode->Release();
			return hr;
		}
		if(pErrorCode)
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
					assert(false);
					return nullptr;
				}
			}
			else
			{
				if (FAILED(hr = CompileShaderFromFile((TCHAR*)pLoadShaderFiile, pFunctionName, "ps_5_0", &pPsBlob)))
				{
					assert(false);
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
			assert(false);
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
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iNumVertex * iVertexSize; // 버텍스 사이즈 * 버텍스 개수
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = vertices;
		if (vertices != NULL)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))
			{
				return nullptr;
			}
		}
		return pBuffer;
	}
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device* pd3dDevice, void* indices, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		HRESULT hr;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iSize * iNumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		
		D3D11_SUBRESOURCE_DATA sd;
		sd.pSysMem = indices;
		if (indices != NULL)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))
			{
				return nullptr;
			}
		}
		return pBuffer;
	}
	ID3D11Buffer* CreateConstantBuffer(ID3D11Device* pd3dDevice, void* data, UINT iNumIndex, UINT iSize, bool bDynamic)
	{
		HRESULT hr;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iSize * iNumIndex;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

		D3D11_SUBRESOURCE_DATA sd;
		sd.pSysMem = data;
		if (data != NULL)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &sd, &pBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))
			{
				return nullptr;
			}
		}
		return pBuffer;
	}
	ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath)
	{
		HRESULT hr;
		if (strFilePath == NULL)
			return nullptr;
		ID3D11ShaderResourceView* pSRV = nullptr;
		ComPtr<ID3D11Resource> res;
		DirectX::DDS_ALPHA_MODE alphaMode;

		hr = DirectX::CreateWICTextureFromFile(pDevice, strFilePath, res.GetAddressOf(), &pSRV);
		if (FAILED(hr))
		{
			assert(false);
			hr = DirectX::CreateDDSTextureFromFile(pDevice, strFilePath, res.GetAddressOf(), &pSRV, 0, &alphaMode);
		}
		if (FAILED(hr))
		{
			assert(false);
			return nullptr;
		}
		return pSRV;
	}
	ID3D11ShaderResourceView* CreateShaderResourceView(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const TCHAR* strFilePath)
	{
		HRESULT hr;
		if (strFilePath == NULL)
			return nullptr;
		ID3D11ShaderResourceView* pSRV = nullptr;
		ComPtr<ID3D11Resource> res;
		DirectX::DDS_ALPHA_MODE alphaMode;
		hr = DirectX::CreateWICTextureFromFile(pDevice, pContext, strFilePath, res.GetAddressOf(), &pSRV);
		if (FAILED(hr))
		{
			hr = DirectX::CreateDDSTextureFromFile(pDevice, pContext, strFilePath, res.GetAddressOf(), &pSRV, 0, &alphaMode);
		}
		if (FAILED(hr))
		{
			assert(false);
			return nullptr;
		}
		return pSRV;
	}
	ID3D11DepthStencilView* CreateDepthStencilView(ID3D11Device* pDevice, DWORD dwWidth, DWORD dwHeight)
	{
		// 1번 텍스처를 생성한다.
		HRESULT hr;
		ID3D11DepthStencilView* pDSV = nullptr;
		ComPtr<ID3D11Texture2D> pDsTexture = nullptr;
		D3D11_TEXTURE2D_DESC DescDepth;
		DescDepth.Width = dwWidth;
		DescDepth.Height = dwHeight;
		DescDepth.MipLevels = 1;
		DescDepth.ArraySize =1;
		DescDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		DescDepth.SampleDesc.Count = 1;
		DescDepth.SampleDesc.Quality = 0;
		DescDepth.Usage = D3D11_USAGE_DEFAULT;
		DescDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		DescDepth.CPUAccessFlags = 0;
		DescDepth.MiscFlags = 0;
		if (FAILED(hr = pDevice->CreateTexture2D(&DescDepth, NULL, &pDsTexture)))
		{
			return nullptr;
		}
		// 2번 깊이스텐실 뷰로 생성한다.
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = DescDepth.Format;
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;
		if (FAILED(hr = pDevice->CreateDepthStencilView(pDsTexture.Get(), &dsvd, &pDSV)))
		{
			return nullptr;
		}
		return pDSV;
	}
	void MDxHelper::PreRender(ID3D11DeviceContext* _pContext, UINT iVertexSize)
	{
		_pContext->IASetInputLayout(g_pInputlayout.Get());
		UINT stride = iVertexSize;
		UINT offset = 0;
		if (iVertexSize == 0)
			stride = m_iVertexSize;

		_pContext->IASetVertexBuffers(0, 1, g_pVertexBuffer.GetAddressOf(), &stride, &offset);
		_pContext->IASetIndexBuffer(g_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		_pContext->VSSetConstantBuffers(0, 1, g_pConstantBuffer.GetAddressOf());
		_pContext->PSSetConstantBuffers(0, 1, g_pConstantBuffer.GetAddressOf());
		_pContext->VSSetShader(g_pVertexShader.Get(), NULL, 0);
		_pContext->PSSetShader(g_pPixelShader.Get(), NULL, 0);
		_pContext->PSSetShaderResources(0, 1, g_pTextureSRV.GetAddressOf());
	}
	void MDxHelper::PostRender(ID3D11DeviceContext* _pContext, UINT iCount)
	{
		if (iCount == 0)
			iCount = m_iNumIndex;
		if (iCount != 0)
		{
			_pContext->DrawIndexed(iCount, 0, 0);
		}
		else
			_pContext->Draw(m_iNumVertex, 0);
	}
	bool MDxHelper::Render(ID3D11DeviceContext* _pContext, UINT iVertexSize, UINT iCount)
	{
		return false;
	}
}
