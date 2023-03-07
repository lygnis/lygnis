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

void MGraphicsEngine::Update(const MeshData& data)
{
	auto swap_chain = game_->display_->swap_chain_;
	
	auto context = _render_system->getImmediateDeviceContext();

	context->ClearRenderTargetColor(swap_chain, 1,0,0,1);
	auto win_size = game_->display_->GetClientSize();
	context->SetViewportSize(win_size.width, win_size.height);

	ConstantData constData = {};
	constData.world = TMatrix::Identity;
	constData.view = TMatrix::Identity;
	constData.proj = TMatrix::Identity;

	constData.world = TMatrix::CreateRotationY(0.707f);
	constData.view.Translation(TVector3(0, 0, -10.f));
	constData.view = constData.view.Invert();
	constData.proj = TMatrix::CreatePerspectiveFieldOfView(1.3f, (float)win_size.width / (float)win_size.height, 0.01f, 1000.f);


	context->SetVertexBuffer(data.mesh->_vertex_buffer);
	context->SetIndexBuffer(data.mesh->_index_buffer);
	for (auto i = 0; i < data.mesh->GetNumMaterialSlots(); i++)
	{
		data.material->SetData(&constData, sizeof(ConstantData));
		context->SetConstantBuffer(data.material->_constant_buffer);

		context->SetVertexShader(data.material->_vertex_shader);
		context->SetPixelShader(data.material->_pixel_shader);

		context->SetTexture(&data.material->_vec_textures[0], data.material->_vec_textures.size());
		auto slot = data.mesh->GetMaterialSlot(i);
		context->DrawIndexTriangleList(slot.num_indices, slot.start_index, 0);
	}

	swap_chain->Present(true);
}


