#include "MyShape.h"

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
    }*/

    MyMatrix4X4 matView;
    Vector3D vTarget = { 5,0,0 };
    Vector3D _upVec = { 0,1,0 };
    Vector3D vPos = { 0,0,0 };
    static Vector3D _vMovePosition{10,0,0};
    if (I_Input.GetKey('W') == KEY_HOLD)
    {
        _vMovePosition.z += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('S') == KEY_HOLD)
    {
        _vMovePosition.z -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('A') == KEY_HOLD)
    {
        _vMovePosition.x -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('D') == KEY_HOLD)
    {
        _vMovePosition.x += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('Q') == KEY_HOLD)
    {
        _vMovePosition.y += 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (I_Input.GetKey('E') == KEY_HOLD)
    {
        _vMovePosition.y -= 10.0f * I_Timer.m_fDeltaTime;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }

    MyMatrix4X4 mCamera; //= mCamera.RotationY(I_Timer.m_fGameTime);
    vPos = (vPos + _vMovePosition) * mCamera;
    matView.ViewLookAt(_vMovePosition, vTarget, _upVec);
    MyMatrix4X4 matProj;
    matProj = matProj.PerspectiveFovLH(1.0f, 100.0f, PI*0.5f, 800.0f/600.0f);
    //matProj = matProj.OrthoOffCenterLH(matProj, -400, 400, -300, 300, 0.0f, 100.0f);
    MyMatrix4X4 s, m, t, c;
    //s = s.Scale(100, 100, 10);
    //c = s * m * t;
    m_cbData.matWorld = c;
    m_cbData.matView = matView;
    m_cbData.matProj = matProj;

    UpdateConstantBuffer();
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
bool ShapeBox::Render()
{
    BObject::Render();
    return true;
}