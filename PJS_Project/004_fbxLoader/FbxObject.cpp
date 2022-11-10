#include "FbxObject.h"

HRESULT MFbxObject::LoadTextures(ID3D11Device* _pDevice, const TCHAR* _pTextureFile)
{
	if (vbTexList.size() > 0)
	{
		W_STR szDefaultDir = L"../../fbxdata/Turret_Deploy/";
		m_pSubTextureList.resize(vbTexList.size());
		for (int ivb = 0; ivb < vbTexList.size(); ivb++)
		{
			W_STR szLoadFile = szDefaultDir + vbTexList[ivb];
			m_pSubTextureList[ivb] = I_Tex.LoadTexture(szLoadFile);
		}
	}
	else
	{
		MActor::LoadTextures(_pDevice, m_szTextureName.c_str());
	}
	
	return S_OK;
}

bool MFbxObject::PostRender(ID3D11DeviceContext* _pContext)
{
	if (m_dxObj.g_pIndexBuffer == nullptr)
	{
		if (vbDataList.size() > 0)
		{
			//MActor::UpdateConstantBuffer(_pContext);
			for (int iSubObj = 0; iSubObj < m_pFbxBuffer.size(); iSubObj++)
			{
				if (vbDataList[iSubObj].size() <= 0)
					continue;		// Null°ª Ã¼Å©
				UINT stride = sizeof(PNCT_VERTEX);
				UINT offset = 0;
				
				_pContext->IASetVertexBuffers(0, 1, &m_pFbxBuffer[iSubObj], &stride, &offset);
				if (m_pSubTextureList[iSubObj] != nullptr)
				{
					_pContext->PSSetShaderResources(0, 1, &m_pSubTextureList[iSubObj]->m_pSrvTexture);
				}
				_pContext->Draw(vbDataList[iSubObj].size(), 0);
			}
		}
		else
		{
			MActor::Render(_pContext);
		}
		
	}
	else
	{
		//_pContext->DrawIndexed();
	}
	return false;
}

bool MFbxObject::CreateVertexData()
{
	return true;
}

HRESULT MFbxObject::CreateVertexBuffer()
{
	HRESULT hr;
	if (vbDataList.size() > 0)
	{
		m_pFbxBuffer.resize(vbDataList.size());
		for (int iVb = 0; iVb < vbDataList.size(); iVb++)
		{
			if (vbDataList[iVb].size() > 0)
			{
				void** pData = nullptr;
				if (vbDataList[iVb].size() > 0)
					pData = (void**)&vbDataList[iVb].at(0);
				m_pFbxBuffer[iVb] = DX::CreateVertexBuffer(m_pd3dDevice, pData, vbDataList[iVb].size(), sizeof(PNCT_VERTEX));
			}
		}
	}
	else
	{
		hr = MActor::CreateVertexBuffer();
	}
	return S_OK;
}
