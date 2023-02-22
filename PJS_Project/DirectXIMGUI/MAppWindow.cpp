#include "MAppWindow.h"
#include "MVertexBuffer.h"
#include <Windows.h>
#include "InputSystem.h"
#include "Mesh.h"
#include "Sprite.h"
#include "Button.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "ImFileDialog.h"
#include <filesystem>
#include <Commdlg.h>
#include "Texture.h"
#include <random>

__declspec(align(16))
struct Constant
{
	TMatrix _world;
	TMatrix _view;
	TMatrix _proj;
	TVector4 _light_dir;
	TVector4 _cameraPos;
	TVector4 _light_position = TVector4(0,1,0,0);
	float    discard;
	float _light_radius;
	float _cTime = 0.0f;
};
struct UIConstant
{
	TVector3 position;
	TVector2 texcoord;

};

void MAppWindow::UpdateQuadPosition()
{
	UpdateCamera();
	UpdateLight();
	UpdateSkyBox();
}

void MAppWindow::UpdateCamera()
{
	_camera->Frame();
	_view_cam = _camera->m_matView;
	_proj_cam = _camera->m_matProj;
}
void MAppWindow::UpdateLight()
{
	_light_position = TVector4(180,140,70,1.0f);
}

void MAppWindow::UpdateSkyBox()
{
	// 스카이 박스 업데이트
	Constant cc;
	cc._world.Identity;
	cc._world = TMatrix::CreateScale(TVector3(1000.f, 1000.f, 1000.f));
	TVector3 camWorld = _camera->m_vCameraPos;
	cc._world.Translation(camWorld);
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	_skyMat->SetData(&cc, sizeof(Constant));
}

void MAppWindow::UpdateModel(TVector3 position, const std::vector<MaterialPtr>& list_material)
{
	Constant cc;
	cc._world.Identity;
	cc._world.Translation(position);
	TMatrix _light_rot_mat;
	_light_rot_mat.Identity;
	_light_rot_mat = TMatrix::CreateRotationY(_light_tor_y);

	TVector3 temp_light = _light_rot_mat.Backward();
	cc._light_dir.x = temp_light.x; cc._light_dir.y = temp_light.y; cc._light_dir.z = temp_light.z; cc._light_dir.w = 1.0f;
	TVector4 temp;
	temp.x = _camera->m_vCameraPos.x; temp.y = _camera->m_vCameraPos.y; temp.z = _camera->m_vCameraPos.z; temp.w = 1.0f;

	cc._cameraPos = temp;
	cc._view = _view_cam;
	cc._proj = _proj_cam;
	cc._light_position = _light_position;
	cc._light_radius = _light_radius;

	cc._cTime = _time;
	for (size_t m = 0; m < list_material.size(); m++)
	{
		list_material[m]->SetData(&cc, sizeof(Constant));
	}
}

void MAppWindow::UpdateUI(const SpritePtr& spr)
{
	Constant cc;
	TMatrix temp;
	temp = temp.Identity;
	cc._world.Identity;
	temp = TMatrix::CreateScale(spr->GetSclae());
	cc._world = cc._world*temp;
	temp= temp.Identity;
	temp.Translation(spr->GetPosition());
	cc._world = cc._world*temp;
	cc._view = _camera->mat_ui_view_;
	cc._proj = _camera->mat_ortho_;
	cc.discard = alpha_test_val_;
	spr->SetData(&cc, sizeof(Constant));
}

void MAppWindow::UpdateBTN(ButtonPtr& spr)
{
	Constant cc;
	TMatrix temp;
	spr->SetState(BTN_NORMAL);
	temp = temp.Identity;
	cc._world.Identity;
	temp = TMatrix::CreateScale(spr->GetSclae());
	cc._world = cc._world * temp;
	temp = temp.Identity;
	temp.Translation(spr->GetPosition());
	cc._world = cc._world * temp;
	cc._view = _camera->mat_ui_view_;
	cc._proj = _camera->mat_ortho_;

	spr->CoordUpdate(cc._world, view_port_);
	RECT rt = spr->GetRect();
	if (PtInRect(&rt, Input::get()->m_pMpos))
	{
		spr->SetState(BTN_HOVER);
		if (Input::get()->GetKey(VK_LBUTTON))
		{
			spr->SetState(BTN_CLICK);
		}
	}
	spr->SetData(&cc, sizeof(Constant));
}

void MAppWindow::DrawMesh(const MeshPtr& mesh, const std::vector<MaterialPtr>& list_material)
{
	// 오브젝트 렌더링
	// 버텍스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(mesh->getVertexBuffer());
	// 인덱스로 삼각형
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(mesh->getIndexBuffer());

	// 현재 고려하고 있는 머티리얼을 여기서 그래픽 파이프라인에 바인딩한다.
	for (size_t m = 0; m < mesh->GetNumMaterialSlots(); m++)
	{
		if (m >= list_material.size())
			break;
		MaterialSlot mat = mesh->GetMaterialSlot(m);
		// 머티리얼 설정 방법을 사용하여 머티리얼을 그래픽 파이프 라인에 바인딩 한다.
		MGraphicsEngine::get()->SetMaterial(list_material[m], wireframe_);
		
		MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(mat.num_indices, 0, mat.start_index);

	}
}

void MAppWindow::DrawSprite(const SpritePtr& spr)
{
	//if (spr->anim_loop_)
	//	animcount_ = (UINT)Timer::get()->m_fGameTime % spr->_vec_textures.size();
	//else
	//{

	//}
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(spr->GetVertexBuffer());
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(spr->GetIndexBuffer());
	MGraphicsEngine::get()->SetState(wireframe_, on_z_buffer_, z_buffer_write_, on_blend_state);
	if (on_blend_testing) //&& !spr->_vec_textures.empty())
		MGraphicsEngine::get()->SetTesttingSprite(spr, spr->anim_loop_, 0);
	else
		MGraphicsEngine::get()->SetSprite(spr, spr->anim_loop_, spr->set_tex_index);

	
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(spr->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
}

void MAppWindow::DrawButton(const ButtonPtr& btn)
{
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetVertexBuffer(btn->GetVertexBuffer());
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetIndexBuffer(btn->GetIndexBuffer());
	MGraphicsEngine::get()->SetState(wireframe_, on_z_buffer_, z_buffer_write_, true);
	MGraphicsEngine::get()->SetButton(btn,btn->GetState());
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->DrawIndexTriangleList(btn->GetIndexBuffer()->GetSizeIndexList(), 0, 0);
}

void MAppWindow::OnCreate()
{
	// 타이머
	Timer::get()->Init();
	Input::get()->Init();
	InputSystem::get()->addListener(this);
	// 카메라 생성 및 초기화
	_camera = std::make_shared<DebugCamera>();
	_camera->CreateViewMatrix(TVector3(0, 0, -3), TVector3(0, 0, 0), TVector3(0, 1, 0));
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(this->GetClientRect().right) / (float)(this->GetClientRect().bottom));
	RECT rc = GetClientRect();
	_camera->CreateOrthoLH((float)(this->GetClientRect().right), (float)(this->GetClientRect().bottom),0.f,1000.f);
	_swapChain = MGraphicsEngine::get()->getRenderSystem()->CreateSwapChain(_hwnd, rc.right-rc.left,rc.bottom-rc.top);


	test_button_ = MGraphicsEngine::get()->GetObjectManager()->CreateButton(L"VertexShader.hlsl", L"UIPixelShader.hlsl");
	test_button_->Position(0,0,0);
	test_button_->Scale(150,70,1);
	// 텍스쳐 로딩
	_sky_Tex =	MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(L"../../data/Textures/sky.jpg");


	// 스왑체인 생성
	// 스카이 박스 메쉬
	_sky_mesh = MGraphicsEngine::get()->getMeshManager()->CreateMeshFromeFile(L"../../data/meshes/sphere.obj");

	// 머티리얼 생성
	_mater = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"PointLightShader.hlsl");
	_mater->AddTexture(_sky_Tex);
	_mater->SetCullMode(CULL_MODE_BACK);

	// 스카이 박스
	_skyMat = MGraphicsEngine::get()->CreateMaterial(L"PointLightVertex.hlsl", L"SkyBoxShader.hlsl");
	_skyMat->AddTexture(_sky_Tex);	
	_skyMat->SetCullMode(CULL_MODE_FRONT);
	view_port_ = TMatrix::Identity;
	view_port_._11 = 1; view_port_._22 = -1; view_port_._41 = (float)this->GetClientRect().right /2; view_port_._42 = (float)this->GetClientRect().bottom / 2;

	_list_materials.reserve(32);
}

void MAppWindow::OnUpdate()
{
	Timer::get()->Frame();
	Input::get()->Frame();
	if (Input::get()->GetKey('F') == KEY_UP)
	{
		_fullscreen_state = !_fullscreen_state;
		RECT size_screen = this->GetSizeScreen();

		_swapChain->SetFullScreen(_fullscreen_state, size_screen.right, size_screen.bottom);
	}
	this->Render();
}

void MAppWindow::Render()
{
	// 렌더링
	// 렌더타겟 색 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->ClearRenderTargetColor(this->_swapChain,
		0.2, 0.2, 0.2, 1);
	RECT rc = this->GetClientRect();
	// 뷰포트 설정
	MGraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	// 카메라 라이트 스카이 박스 업데이트
	UpdateQuadPosition();
	_list_materials.clear();
	_list_materials.push_back(_skyMat);
	DrawMesh(_sky_mesh, _list_materials);



	for (int i = 0; i < sprite_count_; i++)
	{
		//const SpritePtr& spr = MGraphicsEngine::get()->GetObjectManager()->GetSprite(i);
		UpdateUI(MGraphicsEngine::get()->GetObjectManager()->sprite_list_[i]);
		DrawSprite(MGraphicsEngine::get()->GetObjectManager()->sprite_list_[i]);
	}

	for (int i = 0; i < button_count_; i++)
	{
		UpdateBTN(MGraphicsEngine::get()->GetObjectManager()->button_list_[i]);
		DrawButton(MGraphicsEngine::get()->GetObjectManager()->button_list_[i]);
	}
	// imgui stuff
	ImGuiStuff();
	// 버퍼 바꾸기
	_swapChain->Present(true);
	// 상수버퍼 시간 갱신
	_time += Timer::get()->m_fDeltaTime;
}

void MAppWindow::OnDestroy()
{
	MWindow::OnDestroy();
	_swapChain->SetFullScreen(false, 1, 1);
}

void MAppWindow::OnFocus()
{
	InputSystem::get()->addListener(this);
}

void MAppWindow::OnKillFocus()
{
	InputSystem::get()->removeListener(this);
}
void MAppWindow::OnSize()
{
	RECT rc = this->GetClientRect();
	_swapChain->Resize(rc.right, rc.bottom);
	_camera->CreateProjMatrix(0.1f, 1000.0f, 3.141 * 0.5f, (float)(rc.right) / (float)(rc.bottom));
	_camera->CreateOrthoLH((float)(rc.right), (float)(rc.bottom),0.f,1000.f);
	Render();
}

void MAppWindow::ImGuiStuff()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//
	ImGuiMainMenuBar();
	std::string selectSpritename = "";
	bool hasselectedsprite = (selectSpriteID != -1 && MGraphicsEngine::get()->GetObjectManager()->sprite_list_.count(selectSpriteID) > 0);
	if (hasselectedsprite)
	{
		selectSpritename = MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->names_;
	}
	if (ImGui::ListBoxHeader("Sprite", ImVec2(0, 200)))
	{
		for (auto& spr : MGraphicsEngine::get()->GetObjectManager()->sprite_list_)
		{
			std::string sprname = spr.second->names_;
			if (!spr.second->names_.empty())
			{
				sprname = spr.second->names_;
			}
			bool is_sprite_selected = (selectSpriteID == spr.first);
			if (ImGui::Selectable(sprname.c_str(), is_sprite_selected))
			{
				selectSpriteID = spr.first;
				selectedImageID = 0;
			}
		}
		//for (auto& btn : MGraphicsEngine::get()->GetObjectManager()->button_list_)
		//{
		//	std::string sprname = btn.second->names_;
		//	if (!btn.second->names_.empty())
		//	{
		//		sprname = btn.second->names_;
		//	}
		//	bool is_sprite_selected = (selectSpriteID == btn.first);
		//	if (ImGui::Selectable(sprname.c_str(), is_sprite_selected))
		//	{
		//		selectSpriteID = btn.first;
		//		selectedImageID = 0;
		//	}
		//}
		ImGui::ListBoxFooter();
	}
	if (hasselectedsprite)
	{
		if (MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->list_textures_.empty())
		{
			ImGui::Text("No Image");
		}
		else
		{
			ImGui::Text("Image");
			for (auto& image : MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->list_textures_)
			{
				std::string imagename = std::to_string(image.first);
				if (!image.second->tex_name_.empty())
				{
					imagename = image.second->tex_name_;
				}
				bool is_image_selected = (selectedImageID == image.first);
				if (ImGui::Selectable(imagename.c_str(), is_image_selected))
				{
					selectedImageID = image.first;
					MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->set_tex_index = selectedImageID;
				}
			}
		}
		ImGui::Separator();
		if (ImGui::Button("Load a texture"))
		{
			ifd::FileDialog::Instance().Open("TextureOpenDialog", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga*.dds;){.png,.jpg,.jpeg,.bmp,.tgam,.dds},.*");
		}
		if (ifd::FileDialog::Instance().IsDone("TextureOpenDialog"))
		{
			if (ifd::FileDialog::Instance().HasResult())
			{
				std::wstring res = ifd::FileDialog::Instance().GetResult().wstring();
				TexturePtr load_texture = MGraphicsEngine::get()->getTextureManager()->CreateTuextureFromeFile(res.c_str());
				MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->AddTexture(load_texture);
			}
			ifd::FileDialog::Instance().Close();
		}
	}
	if (!MGraphicsEngine::get()->GetObjectManager()->sprite_list_.empty())
	{
		ImGui::Text("Selected Sprite : %s", selectSpritename.c_str());
		ImGui::Text("Position x , y , z: %.1f, %.1f, %.1f", MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->GetPosition().x,
			MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->GetPosition().y, MGraphicsEngine::get()->GetObjectManager()->sprite_list_[selectSpriteID]->GetPosition().z);
		ImGui::Separator();
		ImGui::Text("Selected Image ID : %u", selectedImageID);
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void MAppWindow::ImGuiMainMenuBar()
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::Button("Open a texture"))
			{
				ifd::FileDialog::Instance().Open("TextureOpenDialog", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
			}
			if (ImGui::Button("Save a texture"))
			{
				ifd::FileDialog::Instance().Save("TextureSaveDialog", "Open a texture", "Image file (*.png;*.jpg;*.jpeg;*.bmp;*.tga){.png,.jpg,.jpeg,.bmp,.tga},.*");
			}
			if (ifd::FileDialog::Instance().IsDone("TextureOpenDialog"))
			{
				if (ifd::FileDialog::Instance().HasResult())
				{
					
				}
				ifd::FileDialog::Instance().Close();
			}
			if (ifd::FileDialog::Instance().IsDone("TextureSaveDialog"))
			{
				if (ifd::FileDialog::Instance().HasResult())
				{
					std::wstring res = ifd::FileDialog::Instance().GetResult().wstring();

					//printf("SAVE[%s]\n", res.c_str());//콘솔
					//OutputDebugStringA(res.c_str());//스튜디오
				}
				ifd::FileDialog::Instance().Close();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Make Sprite"))
		{
			ImGui::Begin("Make Sprite");
			ImGui::Text("Set Scale and Position");

			if (showButton)
			{
				if (ImGui::Button("Sprite Setting"))
				{
					showButton = false;
					showMakeButton = true;
				}
			}

			if (showMakeButton)
			{
				ImGui::Text("Scale");
				ImGui::InputInt("scale X", &scale_valuex_);
				ImGui::InputInt("scale Y", &scale_valuey_);
				ImGui::Separator();
				ImGui::Text("Position");
				ImGui::InputInt("position X", &position_valuex_);
				ImGui::InputInt("position Y", &position_valuey_);
				ImGui::InputInt("position Z", &position_valuez_);
				ImGui::Separator();
				if (ImGui::Button("Make"))
				{
					SpritePtr spr = MGraphicsEngine::get()->GetObjectManager()->CreateSprite(L"VertexShader.hlsl", L"PixelShader.hlsl");
					UINT spriteid = sprite_count_++;
					spr->Scale(scale_valuex_, scale_valuey_, 1);
					spr->Position(position_valuex_, position_valuey_, position_valuez_);
					spr->names_ = "Sprite" + std::to_string(sprite_count_);
					spr->SpriteID_ = spriteid;

					MGraphicsEngine::get()->GetObjectManager()->InsertSprite(spriteid, spr);
					showButton = true;
					showMakeButton = false;
					scale_valuex_ = 0;
					scale_valuey_ = 0;
					position_valuex_ = 0;
					position_valuey_ = 0;
					position_valuez_ = 0;
				}
				ImGui::Separator();
				ImGui::Spacing();
				if (ImGui::Button("Random"))
				{
					RECT rc = this->GetClientRect();
					std::random_device rd;
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> dis(-(rc.right/2)+35, (rc.right / 2)-35);
					TVector3 rand_pos; rand_pos.x = dis(gen);
					std::uniform_int_distribution<> disy(-(rc.bottom / 2)+35, (rc.bottom / 2)-35);
					rand_pos.y = disy(gen); rand_pos.z = 0;
					SpritePtr spr = MGraphicsEngine::get()->GetObjectManager()->CreateSprite(L"VertexShader.hlsl", L"PixelShader.hlsl");
					spr->Scale(70, 70, 1);
					spr->Position(rand_pos.x, rand_pos.y, rand_pos.z);
					spr->names_ = "Sprite" + std::to_string(sprite_count_);
					spr->SpriteID_ = sprite_count_;
					//list_sprite_.push_back(spr);
					showButton = true;
					showMakeButton = false;

					sprite_count_++;
				}
			}
			ImGui::End();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Make Button"))
		{
			ImGui::Begin("Make Button");
			ImGui::Text("Set Scale and Position");

			if (showButton)
			{
				if (ImGui::Button("Button Setting"))
				{
					showButton = false;
					showMakeButton = true;
				}
			}

			if (showMakeButton)
			{
				ImGui::Text("Scale");
				ImGui::InputInt("scale X", &scale_valuex_);
				ImGui::InputInt("scale Y", &scale_valuey_);
				ImGui::Separator();
				ImGui::Text("Position");
				ImGui::InputInt("position X", &position_valuex_);
				ImGui::InputInt("position Y", &position_valuey_);
				ImGui::InputInt("position Z", &position_valuez_);
				ImGui::Separator();
				if (ImGui::Button("Make"))
				{
					ButtonPtr btn = MGraphicsEngine::get()->GetObjectManager()->CreateButton(L"VertexShader.hlsl", L"UIPixelShader.hlsl");
					UINT btncount = button_count_++;
					btn->Scale(scale_valuex_, scale_valuey_, 1);
					btn->Position(position_valuex_, position_valuey_, position_valuez_);
					btn->names_ = "Button" + std::to_string(button_count_);
					btn->SpriteID_ = btncount;

					MGraphicsEngine::get()->GetObjectManager()->InsertButton(btncount, btn);
					showButton = true;
					showMakeButton = false;
					scale_valuex_ = 0;
					scale_valuey_ = 0;
					position_valuex_ = 0;
					position_valuey_ = 0;
					position_valuez_ = 0;
				}
			}
			ImGui::End();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Set State"))
		{
			ImGui::Begin("Set State");
			ImGui::Text("Set Culling Mode");
			ImGui::Checkbox("On Wire Frame", &wireframe_);
			ImGui::Separator();
			ImGui::Text("Set Z Buffer Setting");
			ImGui::Checkbox("Z buffer On", &on_z_buffer_);
			ImGui::SameLine(100.0f, 15.f);
			ImGui::Checkbox("Z buffer Write On", &z_buffer_write_);
			ImGui::Separator();
			ImGui::Checkbox("Blend State On", &on_blend_state);
			ImGui::SameLine(100.0f, 40.f);
			ImGui::Checkbox("Blend testting On", &on_blend_testing);
			ImGui::Separator();
			ImGui::DragFloat("testting drag", &alpha_test_val_, 0.01f, 0.1f, 0.9f);
			ImGui::End();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}







void MAppWindow::onKeyDown(int key)
{
	
}

void MAppWindow::onKeyUp(int key)
{
	
}

void MAppWindow::OnMouseMove(const Point& delta_mouse_pos)
{
}
void MAppWindow::OnLeftMouseDown(const Point& delta_mouse_pos)
{
}
void MAppWindow::OnLeftMouseUp(const Point& delta_mouse_pos)
{
}
void MAppWindow::OnRightMouseDown(const Point& delta_mouse_pos)
{
}
void MAppWindow::OnRightMouseUp(const Point& delta_mouse_pos)
{
}

MAppWindow::~MAppWindow()
{
}