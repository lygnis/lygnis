#pragma once
#include "DX3D/Math/Rect.h"
#include"MStd.h"
class Texture2D
{
public:
	enum class Type
	{
		// ∑ª¥ı≈∏∞Ÿ ≈∏¿‘
		NORMAL = 0,
		RENDERTARGET,
		DEPTHSTECIL
	};
public:
	Texture2D(const wchar_t* full_path, RenderSystem* system);
	Texture2D(const TMath::Rect& size, Texture2D::Type type , RenderSystem* system);
	~Texture2D() {};

	TMath::Rect GetSize();
private:
	ComPtr<ID3D11Resource> _texture = nullptr;
	ComPtr<ID3D11ShaderResourceView> _srview;
	ComPtr<ID3D11RenderTargetView> render_target_view_;
	ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
	ComPtr<ID3D11SamplerState> _sampler_state;

	Texture2D::Type t_type_ = Texture2D::Type::NORMAL;
	TMath::Rect rt_size_;

	RenderSystem* r_system_;
	friend class DeviceContext;
};

