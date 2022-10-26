#include "MyShape.h"

bool ShapeBox::Init()
{
    m_pDirLinShape = new ShapeDirectLine;
    m_pDirLinShape->SetDevice(m_p3dDevice, m_pImmediateContext);
    m_pDirLinShape->Create(L"DefaultShape.txt", L"");
    return true;
}

bool ShapeBox::Frame()
{
    /*MyMatrix4X4 m, s, t, c;
    float fScale = cos(I_Timer.m_fGameTime) * 0.5f + 0.5f;
    s = s.Scale(fScale, fScale, fScale);
    m = m.RotationZ(I_Timer.m_fGameTime * 5.0f);
    t = t.Translation(cos(I_Timer.m_fGameTime), 0, 0);
    c = t * s * m;
    for (int i = 0; i < m_pInitVertexBuffer.size(); i++)
    {
        Vector3D _vec = m_pInitVertexBuffer[i].position;
        _vec = _vec * c;
        m_pVertexList[i].position = _vec;
    }
    MyMatrix4X4 m, s, t, c;*/
    //float fScale = cos(I_Timer.m_fGameTime) * 0.5f + 0.5f;
    //m = s.Scale(1, 1, 2);
    /*s = m.RotationX(I_Timer.m_fGameTime * 3.0f);
    t = m.RotationY(I_Timer.m_fGameTime * 3.0f);
    m = m.RotationZ(I_Timer.m_fGameTime * 3.0f);*/
    /*s = t.Translation(cos(I_Timer.m_fGameTime)*10, 0, 0);
    c =  s*m;
    m_matWorld = c;*/
    static float _rx =0.f;
    static float _ry = 0.f;
    static float _rz = 0.f;
    _rx += 5*I_Timer.m_fDeltaTime;
    _ry += 5*I_Timer.m_fDeltaTime;
    //_rz += I_Timer.m_fDeltaTime;
    TBASIS_EX::TVector3 vPos;
    TBASIS_EX::TQuaternion dxCameraRotation;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&dxCameraRotation, _rx, _ry, _rz);
    TBASIS_EX::D3DXMatrixAffineTransformation((TBASIS_EX::TMatrix*)&m_matWorld, 1.0f, NULL, &dxCameraRotation, &vPos);
    //MyMatrix4X4 cameraRotationMat = *(MyMatrix4X4*)&dxCameraRotation;
    //m_matWorld = cameraRotationMat * m_matWorld;
    return true;
}
void ShapeBox::CreateVertexData()
{
    // ¾Õ¸é
    m_pVertexList.resize(24);
    m_pVertexList[0] = ObjectVertex{ Vector3D(-1.0f, 1.0f,-1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[1] = ObjectVertex{ Vector3D(1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[2] = ObjectVertex{ Vector3D(1.0f, -1.0f,-1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[3] = ObjectVertex{ Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(1.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f) };
    // µÞ¸é                        {
    m_pVertexList[4] = ObjectVertex{ Vector3D(1.0f, 1.0f, 1.0f), Vector4D(0.0f, 0.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[5] = ObjectVertex{ Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[6] = ObjectVertex{ Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[7] = ObjectVertex{ Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f) };
    // ¿À¸¥ÂÊ                      {
    m_pVertexList[8] = ObjectVertex{ Vector3D(1.0f, 1.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[9] = ObjectVertex{ Vector3D(1.0f, 1.0f, 1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[10] = ObjectVertex{ Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[11] = ObjectVertex{ Vector3D(1.0f, -1.0f, -1.0f), Vector4D(0.0f, 0.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f) };
    // ¿ÞÂÊ           ObjectVertex(
    m_pVertexList[12] = ObjectVertex{ Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[13] = ObjectVertex{ Vector3D(-1.0f, 1.0f, -1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[14] = ObjectVertex{ Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[15] = ObjectVertex{ Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(1.0f, 1.0f, 0.0f, 1.0f), Vector2D(0.0f, 1.0f) };
    // À­¸é           ObjectVertex(
    m_pVertexList[16] = ObjectVertex{ Vector3D(-1.0f, 1.0f, 1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[17] = ObjectVertex{ Vector3D(1.0f, 1.0f, 1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[18] = ObjectVertex{ Vector3D(1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[19] = ObjectVertex{ Vector3D(-1.0f, 1.0f, -1.0f), Vector4D(1.0f, 0.5f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f) };
    // ¾Æ·§¸é
    m_pVertexList[20] = ObjectVertex{ Vector3D(-1.0f, -1.0f, -1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 0.0f) };
    m_pVertexList[21] = ObjectVertex{ Vector3D(1.0f, -1.0f, -1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 0.0f) };
    m_pVertexList[22] = ObjectVertex{ Vector3D(1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(1.0f, 1.0f) };
    m_pVertexList[23] = ObjectVertex{ Vector3D(-1.0f, -1.0f, 1.0f), Vector4D(0.0f, 1.0f, 1.0f, 1.0f), Vector2D(0.0f, 1.0f) };


    m_pInitVertexBuffer = m_pVertexList;
}
void ShapeBox::CreateIndexData()
{
    m_pIndexList.resize(36);
    int iIndex = 0;
    // »ó´Ü
      // 5    6
      // 1    2
      // ÇÏ´Ü
      // 4    7
      // 0    3  
    // ¾Õ¸é
    //   0    1
    //   3    2
    // µÞ¸é
    //  5    4
    //  6    7
    // ¾Õ¸é ÀÎµ¦½º
    m_pIndexList[iIndex++] = 0;  m_pIndexList[iIndex++] = 1;  m_pIndexList[iIndex++] = 2;  
    m_pIndexList[iIndex++] = 0;	m_pIndexList[iIndex++] = 2;  m_pIndexList[iIndex++] = 3;
    // µÞ¸é
    m_pIndexList[iIndex++] = 4;  m_pIndexList[iIndex++] = 5;  m_pIndexList[iIndex++] = 6;  
    m_pIndexList[iIndex++] = 6;	m_pIndexList[iIndex++] = 7;  m_pIndexList[iIndex++] = 4;
    m_pIndexList[iIndex++] = 8;  m_pIndexList[iIndex++] = 9;  m_pIndexList[iIndex++] = 10; m_pIndexList[iIndex++] = 8;	m_pIndexList[iIndex++] = 10; m_pIndexList[iIndex++] = 11;
    m_pIndexList[iIndex++] = 12; m_pIndexList[iIndex++] = 13; m_pIndexList[iIndex++] = 14; m_pIndexList[iIndex++] = 12;	m_pIndexList[iIndex++] = 14; m_pIndexList[iIndex++] = 15;
    m_pIndexList[iIndex++] = 16; m_pIndexList[iIndex++] = 17; m_pIndexList[iIndex++] = 18; m_pIndexList[iIndex++] = 16;	m_pIndexList[iIndex++] = 18; m_pIndexList[iIndex++] = 19;
    m_pIndexList[iIndex++] = 20; m_pIndexList[iIndex++] = 21; m_pIndexList[iIndex++] = 22; m_pIndexList[iIndex++] = 20;	m_pIndexList[iIndex++] = 22; m_pIndexList[iIndex++] = 23;
}
void ShapeBox::SetMatrix(MyMatrix4X4* _matWorld, MyMatrix4X4* _matView, MyMatrix4X4* _matProj)
{
    BObject::SetMatrix(_matWorld, _matView, _matProj);
    m_vPos.x = m_matWorld._41;
    m_vPos.y = m_matWorld._42;
    m_vPos.z = m_matWorld._43;

    m_vRight.x = m_matWorld._11;
    m_vRight.y = m_matWorld._12;
    m_vRight.z = m_matWorld._13;

    m_vUp.x = m_matWorld._21;
    m_vUp.y = m_matWorld._22;
    m_vUp.z = m_matWorld._23;

    m_vLook.x = m_matWorld._31;
    m_vLook.y = m_matWorld._32;
    m_vLook.z = m_matWorld._33;

    MyMatrix4X4 matLineScale;
    matLineScale.Scale(3.f, 3.f, 3.f);
    matLineScale = matLineScale * m_matWorld;
    if (m_pDirLinShape)
        m_pDirLinShape->SetMatrix(&matLineScale, _matView, _matProj);
}
bool ShapeBox::Render()
{
    BObject::Render();
    m_pDirLinShape->Render();
    return true;
}

bool ShapeBox::Release()
{
    if (m_pDirLinShape)
        m_pDirLinShape->Release();
    delete m_pDirLinShape;
    BObject::Release();
    return true;
}
