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
    //*this = _mat;
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
    *this = _mat;
    return *this;
}

void MyMatrix4X4::ObjectLookAt(Vector3D& _vPosition, Vector3D& _vTarget, Vector3D& _vUp)
{
    // 바라보는 방향 구하기
    Vector3D _vDir = _vTarget - _vPosition;
    _vDir = _vDir.Normalized();
    // 내적으로 업벡터 구하기
    float fDot = _vUp | _vDir;              
    Vector3D _vC = _vDir * fDot;
    Vector3D _vD = (_vDir * fDot);
    Vector3D _vUpVector = _vUp - _vD;
    _vUpVector = _vUpVector.Normalized();
    Vector3D _vRightVec = _vUpVector ^ _vDir;

    _11 = _vRightVec.x; _12 = _vRightVec.y; _13 = _vRightVec.z;
    _21 = _vUpVector.x; _22 = _vUpVector.y; _23 = _vUpVector.z;
    _31 = _vDir.x;      _31 = _vUpVector.y; _33 = _vUpVector.z;
    _41 = _vPosition.x; _42 = _vPosition.y; _43 = _vPosition.z;
}

//MyMatrix4X4 MyMatrix4X4::ViewLookAt(Vector3D& _vPosition, Vector3D& _vTarget, Vector3D& _vUp)
//{
//    // 외적으로 구하기
//    MyMatrix4X4 _matrix;
//    Vector3D _vDir = (_vTarget - _vPosition).Normalized();
//    Vector3D _vRightVec = (_vUp ^ _vDir).Normalized();
//    Vector3D _vUpVec = (_vDir ^ _vRightVec).Normalized();
//
//    _11 = _vRightVec.x;	_12 = _vUpVec.x;	_13 = _vDir.x;
//    _21 = _vRightVec.y;	_22 = _vUpVec.y;	_23 = _vDir.y;
//    _31 = _vRightVec.z;	_32 = _vUpVec.z;	_33 = _vDir.z;
//
//    _41 = -(_vPosition.x * _11 + _vPosition.y * _21 + _vPosition.z * _31);
//    _42 = -(_vPosition.x * _12 + _vPosition.y * _22 + _vPosition.z * _32);
//    _43 = -(_vPosition.x * _13 + _vPosition.y * _23 + _vPosition.z * _33);
//    memcpy(&_matrix, this, 16 * sizeof(float));
//    return _matrix;
//}
//
//MyMatrix4X4 MyMatrix4X4::PerspectiveFovLH(float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect)
//{
//    float h, w, Q;
//    h = 1 / tan(_fOvy * 0.5f);
//    w = h / _Aspect;
//    Q = _fFarPlane / (_fFarPlane - _fNearplane);
//
//    MyMatrix4X4 _ret;
//    ZeroMemory(this, sizeof(MyMatrix4X4));
//    _11 = w;
//    _22 = h;
//    _33 = Q;
//    _43 = -Q * _fNearplane;
//    _34 = 1;
//    _44 = 0.0f;
//
//    memcpy(&_ret, this, 16 * sizeof(float));
//    return _ret;
//}

MyMatrix4X4 MyMatrix4X4::OrthoLH(MyMatrix4X4& _mat, float _w, float _h, float _n, float _f)
{
    Identity();
    _11 = 2.0f / _w;
    _22 = 2.0f / _h;
    _33 = 1.0f / (_f - _n);
    _43 = -_n / (_f - _n);
    return *this;
}

MyMatrix4X4 MyMatrix4X4::OrthoOffCenterLH(MyMatrix4X4& _mat, float _l, float _r, float _b, float _t, float _n, float _f)
{
    Identity();
    _11 = 2.0f / (_r - _l);
    _22 = 2.0f / (_t - _b);
    _33 = 1.0f / (_f - _n);
    _43 = -_n / (_f - _n);
    _41 = (_l + _r) / (_l - _r);
    _42 = (_t + _b) / (_b - _t);
    return *this;
}

MyMatrix4X4 MyMatrix4X4::Translation(float _x, float _y, float _z)
{
    MyMatrix4X4 _mat;
    _mat._41 = _x;
    _mat._42 = _y;
    _mat._43 = _z;
    *this = _mat;
    return *this;
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
