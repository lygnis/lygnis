#include "DebugCamera.h"

bool DebugCamera::Frame()
{
    if (Input::get()->GetKey(VK_RBUTTON)==KEY_HOLD)
    {
        yaw_ += Input::get()->m_pOffset.x * 0.002;
        pitch_ += Input::get()->m_pOffset.y * 0.002;
    }
    if (Input::get()->GetKey('W') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_look_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
        //vTarget.z += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('S') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_look_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
        //vTarget.z -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('D') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_right_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
        //vTarget.x -= 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('A') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_right_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
        //vTarget.x += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('Q') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_up_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
        //vTarget.y += 10.0f * g_fSecondPerFrame;
    }
    if (Input::get()->GetKey('E') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_up_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
        //vTarget.y -= 10.0f * g_fSecondPerFrame;
    }
    
    TBASIS_EX::TVector3 _vPos;
    _vPos.x = camera_pos_.x;
    _vPos.y = camera_pos_.y;
    _vPos.z = camera_pos_.z;
    ////////////////////////////////////////////////////////

    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matProj;
    TBASIS_EX::TQuaternion qRotation;
    mat_world_.Identity;
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, yaw_, pitch_, roll_);
    TBASIS_EX::D3DXMatrixAffineTransformation(&mat_world_, 1.0f, NULL, &qRotation, &_vPos);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &mat_world_);
    mat_view_ = matView;

    Update();
    return true;
}

bool DebugCamera::Update()
{
    v_right_.x = mat_view_._11;
    v_right_.y = mat_view_._21;
    v_right_.z = mat_view_._31;

    v_up_.x = mat_view_._12;
    v_up_.y = mat_view_._22;
    v_up_.z = mat_view_._32;

    v_look_.x = mat_view_._13;
    v_look_.y = mat_view_._23;
    v_look_.z = mat_view_._33;

    v_right_.Normalize();
    v_up_.Normalize();
    v_look_.Normalize();

    return true;
}
