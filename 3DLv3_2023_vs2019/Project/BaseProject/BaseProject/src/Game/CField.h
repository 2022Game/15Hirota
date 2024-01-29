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
	CModel* mpModelSky;
	CColliderMesh* mpColliderMesh;
	CColliderMesh* mpWallCol;
	CColliderMesh* mpEnemyWallCol;

	CModel* mpCubeModel;
	CModel* mpCylinderModel;
	CModel* mpGoalModel;
	CModel* mpStone1;
};