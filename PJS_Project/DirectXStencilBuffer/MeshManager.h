#pragma once
#include "ResourceManager.h"
#include "MStd.h"
class MeshManager : public ResourceManager
{
public:
	MeshManager() {};
	virtual~MeshManager() {};
	//bool Release();
public:
	MeshPtr CreateMeshFromeFile(const wchar_t* file_path);
protected:
	virtual Resource* CreateResourceFromFileConcre(const wchar_t* file_path);

};

