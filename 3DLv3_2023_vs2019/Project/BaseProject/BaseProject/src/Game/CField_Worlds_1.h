#ifndef CFIELD_WORLDS_1_H
#define CFIELD_WORLDS_1_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

class CField_Worlds_1 : public CObjectBase
{
public:
	CField_Worlds_1();
	~CField_Worlds_1();

	// 壁のコライダー取得
	CColliderMesh* GetWallCol() const;

	void Update();
	void Render();

private:

	CModel* mpStageModel;
	CModel* mpLoadModel;
	CModel* mpCloudModel;
	CModel* mpFanceModel;
	CModel* mpFlowersModel;
	CModel* mpGrassModel;
	CModel* mpArrowSignModel;

	CColliderMesh* mpFloorCol;
	CColliderMesh* mpWallCol;
	CColliderMesh* mpFallCol;
	CColliderMesh* mpTree_BranchCol;

	CColliderSphere* mpMushroomSphere;
	CColliderSphere* mpRock_Shrud;
};
#endif