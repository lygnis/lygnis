#pragma once
#include "MStd.h"
#include "Component.h"
#include <vector>
class MeshComponent : public Component
{
public:
	MeshComponent();
	virtual ~MeshComponent();

	void SetMesh(const MeshPtr& mesh);
	const MeshPtr& GetMesh();

	void AddMaterial(const MaterialPtr& material);
	void RemoveMaterial(int index);
	const std::vector<MaterialPtr>& GetMaterials();
protected:
	virtual void OnCreateInternal();
private:
	MeshPtr mesh_;
	std::vector<MaterialPtr> materials_;

};

