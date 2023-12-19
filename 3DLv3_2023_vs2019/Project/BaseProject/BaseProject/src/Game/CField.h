#pragma once
#include "CObjectBase.h"
#include "CColliderMesh.h"

class CField : public CObjectBase
{
public:
	CField();
	~CField();


	// �ǂ̃R���C�_�[�擾
	CColliderMesh* GetWallCol() const;

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