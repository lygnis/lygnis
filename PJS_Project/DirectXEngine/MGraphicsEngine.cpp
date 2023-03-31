#include "MGraphicsEngine.h"
#include "DeviceContext.h"
#include "RenderSystem.h"
#include "Game.h"
#include "Display.h"
#include "MSwapChain.h"
#include "ResourceManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "Material.h"
#include "TMath.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "CameraComponent.h"
#include "Entity.h"

__declspec(align(16))
struct ConstantData
{
	TMatrix world;
	TMatrix view;
	TMatrix proj;
};



MGraphicsEngine::MGraphicsEngine(Game* game) : game_(game)
{
	_render_system = std::make_unique<RenderSystem>();
}

MGraphicsEngine::~MGraphicsEngine()
{
}

RenderSystem* MGraphicsEngine::getRenderSystem()
{
	return _render_system.get();
}

void MGraphicsEngine::AddComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
	{
		meshes_.emplace(c);
	}
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		cameras_.emplace(c);
	}
}

void MGraphicsEngine::RemoveComponent(Component* component)
{
	if (auto c = dynamic_cast<MeshComponent*>(component))
	{
		meshes_.erase(c);
	}
	else if (auto c = dynamic_cast<CameraComponent*>(component))
	{
		cameras_.erase(c);
	}
}

void MGraphicsEngine::Update()
{
	auto swap_chain = game_->display_->swap_chain_;
	
	auto context = _render_system->getImmediateDeviceContext();

	context->ClearRenderTargetColor(swap_chain, 0.5,0.5f,0.5f,1.f);
	auto win_size = game_->display_->GetClientSize();
	context->SetViewportSize(win_size.width, win_size.height);

	ConstantData constData = {};
	constData.view = TMatrix::Identity;
	constData.proj = TMatrix::Identity;

	for (auto c : cameras_)
	{
		c->SetScreenArea(win_size);
		c->GetViewMatrix(constData.view);
		c->GetProjectionMatrix(constData.proj);
	}

	//
	//constData.view.Translation(TVector3(0, 0, 10.f));
	//constData.view = constData.view.Invert();
	//constData.proj = TMatrix::CreatePerspectiveFieldOfView(1.3f, (float)win_size.width / (float)win_size.height, 0.01f, 1000.f);

	for (auto m : meshes_)
	{
		auto transform = m->GetEntity()->GetTransform();
		transform->GetWorldMatrix(constData.world);

		auto mesh = m->GetMesh().get();
		const auto materials = m->GetMaterials();

		context->SetVertexBuffer(mesh->_vertex_buffer);
		context->SetIndexBuffer(mesh->_index_buffer);
		for (auto i = 0; i < mesh->GetNumMaterialSlots(); i++)
		{
			if (i >= materials.size())
				break;
			auto mat = materials[i].get();


			mat->SetData(&constData, sizeof(ConstantData));
			context->SetConstantBuffer(mat->_constant_buffer);

			context->SetVertexShader(mat->_vertex_shader);
			context->SetPixelShader(mat->_pixel_shader);

			context->SetTexture(&mat->_vec_textures[0], mat->_vec_textures.size());
			auto slot = mesh->GetMaterialSlot(i);
			context->DrawIndexTriangleList(slot.num_indices, slot.start_index, 0);
		}
	}

	swap_chain->Present(true);
}


