#include "MyMatrix.h"

MyMatrix3X3::MyMatrix3X3()
{
    Identity();
}

void MyMatrix3X3::Identity()
{
    // 단위 행렬을 생성합니다.
    _11 = _22 = _33 = 1.0f;
    _12 = _13 = 0.0f;
    _21 = _23 = 0.0f;
    _31 = _32 = 0.0f;
}

MyMatrix3X3 MyMatrix3X3::Transpose()
{
    // 행렬 전치하기
    MyMatrix3X3 _mat;
    _mat._11 = _11; _mat._12 = _21; _mat._13 = _31;
    _mat._21 = _12; _mat._22 = _22; _mat._23 = _13;
    _mat._31 = _13; _mat._32 = _23; _mat._33 = _33;
    return _mat;
}

MyMatrix3X3 MyMatrix3X3::Rotation(float _fRadian)
{
    float _fCostheta = cos(_fRadian);
    float _fSintheta = sin(_fRadian);
    MyMatrix3X3 _mat;
    _mat._11 = _fCostheta; _mat._12 = _fSintheta;
    _mat._21 = -_fSintheta; _mat._22 = _fCostheta;
    return _mat;
}

MyMatrix3X3 MyMatrix3X3::Scale(float _x, float _y)
{
    MyMatrix3X3 _mat;
    _mat._11 = _x;
    _mat._22 = _y;
    return _mat;
}

MyMatrix3X3 MyMatrix3X3::Translate(float _x, float _y)
{
    MyMatrix3X3 _mat;
    _mat._31 = _x;
    _mat._32 = _y;
    return _mat;
}

MyMatrix3X3 MyMatrix3X3::operator*(MyMatrix3X3& _mat)
{
    MyMatrix3X3 _m;
    for (int iCol = 0; iCol < 3; iCol++)
    {
        for (int iRow = 0; iRow < 3; iRow++)
        {
            _m.m[iRow][iCol] =
                m[iRow][0] * _mat.m[0][iCol] +
                m[iRow][1] * _mat.m[1][iCol] +
                m[iRow][2] * _mat.m[2][iCol];
        }
    }
    return _m;
}



MyMatrix4X4::MyMatrix4X4()
{
    Identity();
}

void MyMatrix4X4::Identity()
{
    // 단위 행렬을 생성합니다.
    _11 = _22 = _33 = _44 =1.0f;
    _12 = _13 =_14= 0.0f;
    _21 = _23 =_24= 0.0f;
    _31 = _32 =_34 = 0.0f;
    _41 = _42 = _43 = 0.0f;
}

MyMatrix4X4 MyMatrix4X4::Transpose()
{
    // 행렬 전치하기
    MyMatrix4X4 _mat;
    _mat._11 = _11; _mat._12 = _21; _mat._13 = _31; _mat._14 = _41;
    _mat._21 = _12; _mat._22 = _22; _mat._23 = _32; _mat._24 = _42;
    _mat._31 = _13; _mat._32 = _23; _mat._33 = _33; _mat._34 = _43;
    _mat._41 = _14; _mat._42 = _24; _mat._43 = _34; _mat._44 = _44;
    return _mat;
}

MyMatrix4X4 MyMatrix4X4::RotationX(float _fRadian)
{
    float _fCostheta = cos(_fRadian);
    float _fSintheta = sin(_fRadian);
    MyMatrix4X4 _mat;
    _mat._22 = _fCostheta; _mat._23 = _fSintheta;
    _mat._32 = -_fSintheta; _mat._33 = _fCostheta;
    return _mat;
}
MyMatrix4X4 MyMatrix4X4::RotationY(float _fRadian)
{
    float _fCostheta = cos(_fRadian);
    float _fSintheta = sin(_fRadian);
    MyMatrix4X4 _mat;
    _mat._11 = _fCostheta; _mat._13 = -_fSintheta;
    _mat._31 = _fSintheta; _mat._33 = _fCostheta;
    return _mat;
}
MyMatrix4X4 MyMatrix4X4::RotationZ(float _fRadian)
{
    float _fCostheta = cos(_fRadian);
    float _fSintheta = sin(_fRadian);
    MyMatrix4X4 _mat;
    _mat._11 = _fCostheta; _mat._12 = -_fSintheta;
    _mat._21 = _fSintheta; _mat._22 = _fCostheta;
    return _mat;
}

MyMatrix4X4 MyMatrix4X4::Scale(float _x, float _y, float _z)
{
    MyMatrix4X4 _mat;
    _mat._11 = _x;
    _mat._22 = _y;
    _mat._33 = _z;
    return _mat;
}

MyMatrix4X4 MyMatrix4X4::Translation(float _x, float _y, float _z)
{
    MyMatrix4X4 _mat;
    _mat._41 = _x;
    _mat._42 = _y;
    _mat._43 = _z;
    return _mat;
}

MyMatrix4X4 MyMatrix4X4::operator*(MyMatrix4X4& _mat)
{
    MyMatrix4X4 _m;
    for (int iCol = 0; iCol < 4; iCol++)
    {
        for (int iRow = 0; iRow < 4; iRow++)
        {
            _m.m[iRow][iCol] =
                m[iRow][0] * _mat.m[0][iCol] +
                m[iRow][1] * _mat.m[1][iCol] +
                m[iRow][2] * _mat.m[2][iCol] +
                m[iRow][3] * _mat.m[3][iCol];
        }
    }
    return _m;
}
