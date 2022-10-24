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
    MyMatrix4X4 m, s, t, c;
    float fScale = cos(I_Timer.m_fGameTime) * 0.5f + 0.5f;
    //s = s.Scale(fScale, fScale, fScale);
    m = m.RotationZ(I_Timer.m_fGameTime * 3.0f);
    //s = m.RotationX(I_Timer.m_fGameTime * 3.0f);
    //t = m.RotationY(I_Timer.m_fGameTime * 3.0f);
    //t = t.Translation(cos(I_Timer.m_fGameTime)*10, 0, 0);
    c =  m *t;
    m_cbData.matWorld = c;
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