#pragma once
#include "Resource.h"
#include "Rect.h"
#include"MStd.h"

class Texture : public Resource
{
public:
	enum Type
	{
		// ∑ª¥ı≈∏∞Ÿ ≈∏¿‘
		NORMAL = 0,
		RENDERTARGET,
		DEPTHSTECIL
	};
public:
	Texture(const wchar_t* full_path);
	Texture(const TMath::Rect& size, Texture::Type type);
	~Texture();

	TMath::Rect GetSize();
	Texture::Type GetType();
private:
	ComPtr<ID3D11Resource> _texture = nullptr;
	ID3D11ShaderResourceView* _srview;
	ComPtr<ID3D11RenderTargetView> render_target_view_;
	ComPtr<ID3D11DepthStencilView> depth_stencil_view_;
	ID3D11SamplerState* _sampler_state;

	Texture::Type t_type_ = Texture::Type::NORMAL;
	TMath::Rect rt_size_;

	friend class DeviceContext;
};

