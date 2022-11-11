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
		W_STR szDefaultDir = L"../../fbxdata//Girl_FBX2020/";
		m_pSubTextureList.resize(vbTexList.size());
		for (int ivb = 0; ivb < vbTexList.size(); ivb++)
		{
			W_STR szLoadFile = szDefaultDir + vbTexList[ivb];
			m_pSubTextureList[ivb] = I_Tex.LoadTexture(szLoadFile);
		}
	}
	else
	{
		W_STR szDefaultDir = L"../../fbxdata//Girl_FBX2020/";
		W_STR szLoadFile = szDefaultDir + m_szTextureName;
		MActor::LoadTextures(_pDevice, szLoadFile.c_str());
	}
	
	return S_OK;
}

bool MFbxObject::PostRender(ID3D11DeviceContext* _pContext)
{
	//if (m_dxObj.g_pIndexBuffer == nullptr)
	//{
	//	if (vbDataList.size() > 0)
	//	{
	//		//MActor::UpdateConstantBuffer(_pContext);
	//		for (int iSubObj = 0; iSubObj < m_pFbxBuffer.size(); iSubObj++)
	//		{
	//			if (vbDataList[iSubObj].size() <= 0)
	//				continue;		// Null값 체크
	//			UINT stride = sizeof(PNCT_VERTEX);
	//			UINT offset = 0;
	//			
	//			_pContext->IASetVertexBuffers(0, 1, &m_pFbxBuffer[iSubObj], &stride, &offset);
	//			_pContext->PSSetShaderResources(0, 1, &m_pSubTextureList[iSubObj]->m_pSrvTexture);
	//			
	//			_pContext->Draw(vbDataList[iSubObj].size(), 0);
	//		}
	//	}
	//	else
	//	{
	//		MActor::Render(_pContext);
	//	}
	//	
	//}
	m_pImmediateContext = _pContext;
	if (m_bSkinned)
	{
		m_pImmediateContext->VSSetConstantBuffers(1, 1, &m_pSkinBoneCB);
	}
	if (m_dxObj.g_pIndexBuffer == nullptr)
	{
		if (vbDataList.size() > 0)
		{
			for (int iSubObj = 0; iSubObj < m_pFbxBuffer.size(); iSubObj++)
			{
				if (vbDataList[iSubObj].size() <= 0)
					continue;
				UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(IW_VERTEX) };
				UINT offset[2] = { 0,0 };
				ID3D11Buffer* buffer[2] = { m_pFbxBuffer[iSubObj], m_pFbxBuffer_IW[iSubObj] };
				m_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);
				if (m_pSubTextureList.size() > 0 && m_pSubTextureList[iSubObj] != nullptr)
				{
					m_pImmediateContext->PSSetShaderResources(0, 1, &m_pSubTextureList[iSubObj]->m_pSrvTexture);
				}
				m_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
			}
		}
		else
		{
			UINT stride[2] = { sizeof(PNCT_VERTEX), sizeof(IW_VERTEX) };
			UINT offset[2] = { 0,0 };
			ID3D11Buffer* buffer[2] = { m_dxObj.g_pVertexBuffer.Get(), m_pVertexBuffer_IW };
			m_pImmediateContext->IASetVertexBuffers(0, 2, buffer, stride, offset);
			m_pImmediateContext->Draw(m_dxObj.m_iNumVertex, 0);
		}
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
	if (vbDataListIW.size() > 0)
	{
		m_pFbxBuffer_IW.resize(vbDataListIW.size());
		for (int ivb = 0; ivb < vbDataListIW.size(); ivb++)
		{
			void** pData = nullptr;
			if (vbDataListIW[ivb].size() > 0)
			{
				pData = (void**)&vbDataListIW[ivb].at(0);
				m_pFbxBuffer_IW[ivb] = DX::CreateVertexBuffer(m_pd3dDevice, pData, vbDataListIW[ivb].size(), sizeof(PNCT_VERTEX));
			}
		}
	}
	else
	{
		m_pVertexBuffer_IW = DX::CreateVertexBuffer(m_pd3dDevice, &m_VertexList_IW.at(0), m_VertexList_IW.size(), sizeof(IW_VERTEX));
	}

	return S_OK;
}

HRESULT MFbxObject::CreateConstantBuffer()
{
	MActor::CreateConstantBuffer();
	for (int iBone = 0; iBone < 255; iBone++)
	{
		D3DXMatrixIdentity(&m_cbDataBone.matBone[iBone]);
	}
	HRESULT hr;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.CPUAccessFlags = 0;

	bd.ByteWidth = sizeof(VS_CONSTANT_BONE_BUFFER);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = &m_cbDataBone;

	if (FAILED(hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pSkinBoneCB)))
	{
		assert(false);
		return hr;
	}
	return hr;
}

HRESULT MFbxObject::SetInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{ "INDEX", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "WEIGHT", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,16,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(ied) / sizeof(ied[0]);
	m_dxObj.g_pInputlayout.Attach(DX::CreateInputlayout(m_pd3dDevice, (DWORD)m_dxObj.g_pVSBlob.Get()->GetBufferSize()
		, m_dxObj.g_pVSBlob.Get()->GetBufferPointer(), ied, NumElements));

	return hr;
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

TMatrix MFbxObject::Interplate(float fFrame, MAnimScene _scene)
{
	// 10프레임				20 프레임
	// A=0 -----------------B = 20
	// t 0			0.5		1
	// 정규화 한후 중간값을 만들어 보간해준다.
	TMatrix matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	if (m_AnimTrack.size() == 0)
		return matIdentity;

	MAnimTrack A, B;
	int index = (int)fFrame;
	if (m_AnimTrack.size() <= index)
	{
		return m_AnimTrack[index-1].matAnim;
	}
	assert(m_AnimTrack.size() > index);
	A = m_AnimTrack[max(_scene.iStartFrame, index)];
	B = m_AnimTrack[min(_scene.iEndFrame-1, index + 1)];
	if (A.iFrame == B.iFrame)
	{
		return m_AnimTrack[fFrame].matAnim;
	}
	float t = (fFrame - A.iFrame) / (B.iFrame - A.iFrame);
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
	TMatrix matCurrent = matScale * matRotation;
	matCurrent._41 = pos.x;
	matCurrent._42 = pos.y;
	matCurrent._43 = pos.z;
	return matCurrent;
}
