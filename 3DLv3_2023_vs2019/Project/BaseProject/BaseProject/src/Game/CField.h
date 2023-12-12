#pragma once
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CField : public CObjectBase
{
public:
	CField();
	~CField();

	void Update();
	void Render();

private:
	void CreateFieldObjects();

	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	CColliderMesh* mpWallCol;

	CModel* mpCubeModel;
	CModel* mpCylinderModel;
	CModel* mpGoalModel;
	CModel* mpStone1;
};