#pragma once
#include <d3d11.h>
#include "MStd.h"
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "Sprite.h"
#include "Material.h"

class MGraphicsEngine
{
public:
	MGraphicsEngine();
	~MGraphicsEngine();
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	void		GetVertexMeshLayoutShader(void** byte_code, size_t* size);
public:
	// ∏”∆º∏ÆæÛ ∑ª¥ı∏µ
	MaterialPtr CreateMaterial(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	MaterialPtr CreateMaterial(const MaterialPtr& material);
	void		SetMaterial(const MaterialPtr& material, const bool wire_frame);
	// Ω∫«¡∂Û¿Ã∆Æ ∑ª¥ı∏µ
	SpritePtr	CreateSprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	SpritePtr	CreateSprite(const SpritePtr& sprite);
	void		SetSprite(const SpritePtr& sprite, bool tex_anim, int anim_count);
	void        SetTesttingSprite(const SpritePtr& sprite, bool tex_anim, int anim_count);
	void		SetState(const bool wire_frame, bool on_z_buffer, bool z_buffer_write, bool blend_state);
public:
	// ΩÃ±€≈Ê
	static MGraphicsEngine* get();
	static void				Create();
	static void				Release();
private:
	std::shared_ptr<RenderSystem> _render_system;
	TextureManager* _tex_manager = nullptr;
	MeshManager* _mesh_manger = nullptr;

	static std::shared_ptr<MGraphicsEngine> _engine;

	unsigned char _mesh_layout_byte_code[1024];
	size_t _mesh_layout_size = 0;
};

