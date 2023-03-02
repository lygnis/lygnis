#include "MeshManager.h"
#include"Mesh.h"

MeshPtr MeshManager::CreateMeshFromeFile(const wchar_t* file_path)
{
	return std::static_pointer_cast<Mesh>(CreateResourceFromFile(file_path));
}
Resource* MeshManager::CreateResourceFromFileConcre(const wchar_t* file_path)
{
    Mesh* mesh = nullptr;
    try
    {
        mesh = new Mesh(file_path);
    }
    catch (...)
    {

    }
    return mesh;
}
