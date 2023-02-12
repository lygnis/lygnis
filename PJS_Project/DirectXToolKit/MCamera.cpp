#include "MCamera.h"
TMatrix MCamera::GetCameraTraslation()
{
    return _matWorld;
}
void MCamera::CreateViewMatrix(TVector3 _vEye, TVector3 _vAt, TVector3 _vUp)
{
	m_vCameraPos = _vEye;
	m_vTarget = _vAt;
    m_vUp.x = _vUp.x;
    m_vUp.y = _vUp.y;
    m_vUp.z = _vUp.z;
    m_matView = ViewLookAt(_vEye, _vAt, _vUp);
}

void MCamera::CreateProjMatrix(float _fNear, float _fFar, float fFovY, float fAspecRatio)
{
    m_fNear = _fNear;
    m_fFar = _fFar;
    m_fFovY = fFovY;
    m_fAspectRatio = fAspecRatio;
    // 원근 투영
    //m_matProj.
    m_matProj = PerspectiveFovLH(m_matProj,_fNear, _fFar, fFovY, fAspecRatio);
    //m_matProj.OrthoLH(m_matProj,800, 600, 0.0f, 100.0f);
    //m_matProj.OrthoOffCenterLH(m_matProj, -400, 400, -300, 300,0.0f, 100.0f);
}

void MCamera::CreateOrthoLH(float view_right, float view_bottom, float near_z, float far_z)
{
    mat_ortho_ = TMatrix::CreateOrthographic(view_right, view_bottom, near_z, far_z);
}

bool MCamera::Frame()
{
    float _rx = 0.f;
    float _ry = 0.f;
    float _rz = 0.f;
    static TVector3 _vLook = { 0,0,1 };
    static TVector3 _vUp = {0,1,0};
    static TVector3 _vRight= {1,0,0};
    if (Input::get()->GetKey('W') == KEY_HOLD)
    {
        TVector3 _v = _vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('S') == KEY_HOLD)
    {
        TVector3 _v = _vLook * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('D') == KEY_HOLD)
    {
        TVector3 _v = _vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos -= _v;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('A') == KEY_HOLD)
    {
        TVector3 _v = _vRight * 10 * Timer::get()->m_fDeltaTime;
        m_vCameraPos += _v;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('Q') == KEY_HOLD)
    {
        _rx += Timer::get()->m_fDeltaTime;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('E') == KEY_HOLD)
    {
        _rx -= Timer::get()->m_fDeltaTime;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }
    TMatrix dxCameraRotation = DirectX::XMMatrixRotationRollPitchYaw(_rx, _ry, _rz);

    //_vLook = _vLook * dxCameraRotation;// cameraRotation matrix;
    //_vUp = _vUp * dxCameraRotation;
    //_vRight = _vRight * dxCameraRotation;
    m_vTarget = m_vCameraPos + _vLook;
    TVector3 _vecUp;
    _vecUp= m_vUp;
    m_matView = ViewLookAt(m_vCameraPos, m_vTarget , _vecUp);
	return true;
}

TMatrix MCamera::ViewLookAt(TVector3& _vPosition, TVector3& _vTarget, TVector3& _vUp)
{
    TMatrix _matrix;
    TVector3 _vDir = (_vTarget - _vPosition);
    TVector3 _vRightVec = (_vUp.Cross(_vDir));
    TVector3 _vUpVec = (_vDir.Cross(_vRightVec));
    _vDir.Normalize(); _vRightVec.Normalize(); _vUpVec.Normalize();
    
    _matrix._11 = _vRightVec.x;	_matrix._12 = _vUpVec.x;	_matrix._13 = _vDir.x;
    _matrix._21 = _vRightVec.y;	_matrix._22 = _vUpVec.y;	_matrix._23 = _vDir.y;
    _matrix._31 = _vRightVec.z;	_matrix._32 = _vUpVec.z;	_matrix._33 = _vDir.z;
    
    _matrix._41 = -(_vPosition.x * _matrix._11 + _vPosition.y * _matrix._21 + _vPosition.z * _matrix._31);
    _matrix._42 = -(_vPosition.x * _matrix._12 + _vPosition.y * _matrix._22 + _vPosition.z * _matrix._32);
    _matrix._43 = -(_vPosition.x * _matrix._13 + _vPosition.y * _matrix._23 + _vPosition.z * _matrix._33);
    //memcpy(&_matrix, this, 16 * sizeof(float));
    return _matrix;
}

TMatrix MCamera::PerspectiveFovLH(TMatrix& _mat ,float _fNearplane, float _fFarPlane, float _fOvy, float _Aspect)
{
    float h, w, Q;
    h = 1 / tan(_fOvy * 0.5f);
    w = h / _Aspect;
    Q = _fFarPlane / (_fFarPlane - _fNearplane);

    //MyMatrix4X4 _ret;
    //ZeroMemory(this, sizeof(MyMatrix4X4));
    _mat._11 = w;
    _mat._22 = h;
    _mat._33 = Q;
    _mat._43 = -Q * _fNearplane;
    _mat._34 = 1;
    _mat._44 = 0.0f;
    //memcpy(&_ret, this, 16 * sizeof(float));
    return _mat;
}
