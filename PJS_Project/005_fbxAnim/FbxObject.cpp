#include "FbxObject.h"

void MFbxObject::SetParent(MFbxObject* pObj)
{
	pObj->m_pFbxChilds.push_back(this);
	m_pParent = pObj;
}

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
					continue;		// Null값 체크
				UINT stride = sizeof(PNCT_VERTEX);
				UINT offset = 0;
				
				_pContext->IASetVertexBuffers(0, 1, &m_pFbxBuffer[iSubObj], &stride, &offset);
				_pContext->PSSetShaderResources(0, 1, &m_pSubTextureList[iSubObj]->m_pSrvTexture);
				
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
	return true;
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

bool MFbxObject::Release()
{
	MActor::Release();
	for (int iSubObj = 0; iSubObj < m_pFbxBuffer.size(); iSubObj++)
	{
		if (m_pFbxBuffer[iSubObj])
		{
			m_pFbxBuffer[iSubObj]->Release();
		}
	}
	return true;
}

TMatrix MFbxObject::Interplate(float fFrame)
{
	// 10프레임				20 프레임
	// A=0 -----------------B = 20
	// t 0			0.5		1
	// 정규화 한후 중간값을 만들어 보간해준다.
	MAnimTrack A, B;
	A = m_AnimTrack[max(m_AnimScene.iStartFrame, fFrame + 0)];
	B = m_AnimTrack[min(m_AnimScene.iEndFrame, fFrame + 1)];
	if (A.iFrame == B.iFrame)
	{
		return m_AnimTrack[fFrame].matAnim;
	}
	float t = (fFrame - A.iFrame) * (B.iFrame - A.iFrame);
	TVector3 pos;
	D3DXVec3Lerp(&pos, &A.t, &B.t, t);
	TVector3 scale;
	D3DXVec3Lerp(&scale, &A.s, &B.s, t);
	TQuaternion qRotation;
	D3DXQuaternionSlerp(&qRotation, &A.r, &B.r, t);
	TMatrix matScale;
	D3DXMatrixScaling(&matScale, scale.x, scale.y, scale.z);
	TMatrix matRotation;
	D3DXMatrixRotationQuaternion(&matRotation, &qRotation);
	TMatrix matCurrent = /*matScale **/ matRotation;
	matCurrent._41 = pos.x;
	matCurrent._42 = pos.y;
	matCurrent._43 = pos.z;
	return matCurrent;
}
