#include "Player.h"



void Player::OnCreate()
{
	Entity::OnCreate();
	CreateComponent<CameraComponent>();

	GetTransform()->SetPosition(TVector3(0, 0, -10.0f));
}

void Player::OnUpdate(float delta_time)
{
	Entity::OnUpdate(delta_time);
	
}


Player::Player()
{
}

Player::~Player()
{
}
