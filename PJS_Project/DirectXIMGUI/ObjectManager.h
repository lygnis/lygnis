#pragma once
#include "MStd.h"
#include <map>
//#include "rapidjson/document.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//using namespace rapidjson;
class ObjectManager
{
public:
	ObjectManager() {};
	~ObjectManager() {};
public:
	// √ ±‚»≠
	void		Initalize(const TMatrix& view_port, const TMatrix& ortho_mat);
	SpritePtr	CreateSprite(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	ButtonPtr	CreateButton(const wchar_t* vertex_shader_path, const wchar_t* pixel_shader_path);
	void		InsertUI(UINT index, ControlUIPtr& sprite );
	void        InsertButton(UINT index, ButtonPtr& button);
	void		UpdateUI(const UINT index);
public:
	//void SaveToJson(const char* filename);
	//void LoadFromFile(const std::string& filename, Document& outdoc);
public:
	std::map<UINT, ControlUIPtr> ui_list_;
private:
	TMatrix view_port_;
	TMatrix view_mat_;
	TMatrix ortho_proj_;
};