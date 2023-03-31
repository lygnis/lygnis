#include "MyGame.h"
#include "Player.h"
MyGame::MyGame()
{
}

MyGame::~MyGame()
{
}

void MyGame::OnCreate()
{
	Game::OnCreate();
	auto mesh = GetResourceManager()->CreateResourceFromFile<Mesh>(L"../../data/Meshes/house.obj");
	auto tex = GetResourceManager()->CreateResourceFromFile<Texture>(L"../../data/Textures/wood.jpg");

	auto material = GetResourceManager()->CreateResourceFromFile<Material>(L"MyMaterial.hlsl");
	auto fbxLoader = GetResourceManager()->CreateResourceFromFile<FbxLoader>(L"");

	material->AddTexture(tex);

	entity_ = GetWorld()->CreateEntity<Entity>();
	auto mesh_component = entity_->CreateComponent<MeshComponent>();
	mesh_component->SetMesh(mesh);
	mesh_component->AddMaterial(material);
	mesh_component->AddMaterial(material);
	mesh_component->AddMaterial(material);
	mesh_component->AddMaterial(material);

	GetWorld()->CreateEntity<Player>();
}

void MyGame::OnUpdate(float delta_time)
{
	Game::OnUpdate(delta_time);
	rotation_ += 1.57f * delta_time;

	entity_->GetTransform()->SetRotation(TVector3(0, rotation_, 0));
}
