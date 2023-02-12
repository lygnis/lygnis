#include "ThirdPersonCamera.h"

bool ThirdPersonCamera::Frame()
{
    if (Input::get()->GetKey(VK_RBUTTON) == KEY_HOLD)
    {
        yaw_ += Input::get()->m_pOffset.x * 0.002;
        pitch_ += Input::get()->m_pOffset.y * 0.002;
        // X 축 회전을 통해 상하가 반전되지 않게 방지한다.
        if (pitch_ >= 1.57f)
            pitch_ = 1.57f;
        else if (pitch_ <= -1.57f)
            pitch_ = -1.57f;
    }
    TVector3 cam_rot(pitch_, yaw_, roll_);
    //current_camera_rot = TVector3::Lerp(current_camera_rot, cam_rot, 2.f * Timer::get()->m_fDeltaTime);
   /* if (Input::get()->GetKey('W') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_look_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
    }
    if (Input::get()->GetKey('S') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_look_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
    }
    if (Input::get()->GetKey('D') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_right_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
    }
    if (Input::get()->GetKey('A') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_right_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
    }
    if (Input::get()->GetKey('Q') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_up_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ += _v;
    }
    if (Input::get()->GetKey('E') == KEY_HOLD)
    {
        TBASIS_EX::TVector3 _v = v_up_ * 10 * Timer::get()->m_fDeltaTime;
        camera_pos_ -= _v;
    }*/

    mat_world_.Identity;
   
    ////////////////////////////////////////////////////////

    TBASIS_EX::TMatrix matView;
    TBASIS_EX::TMatrix matProj;
    TBASIS_EX::TQuaternion qRotation;
    //TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, current_camera_rot.y, current_camera_rot.x, current_camera_rot.z);
    TBASIS_EX::D3DXQuaternionRotationYawPitchRoll(&qRotation, yaw_, pitch_, roll_);
    TBASIS_EX::D3DXMatrixAffineTransformation(&mat_world_, 1.0f, NULL, &qRotation, &camera_pos_);
    TBASIS_EX::D3DXMatrixInverse(&matView, NULL, &mat_world_);

    mat_view_ = matView;
    Update();
    return true;
}

bool ThirdPersonCamera::Update()
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
