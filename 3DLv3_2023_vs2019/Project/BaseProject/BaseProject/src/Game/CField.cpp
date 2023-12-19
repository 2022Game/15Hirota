#include "CField.h"
#include "CCollisionManager.h"
#include "CMoveFloor.h"
#include "CRotateFloor.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CCamera.h"

CField::CField()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// モデルデータ取得
	mpModel = CResourceManager::Get<CModel>("Field");

	CModel* wallCol = CResourceManager::Get<CModel>("WallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);

	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, floorCol, true);

	CreateFieldObjects();
}

CField::~CField()
{
	if (mpColliderMesh != nullptr)
	{
		delete mpColliderMesh;
		mpColliderMesh = nullptr;
	}

	if (mpWallCol != nullptr)
	{
		// メインカメラから壁のコライダーへの参照を取り除く
		CCamera* mainCamera = CCamera::MainCamera();
		if (mainCamera != nullptr)
		{
			mainCamera->RemoveCollider(mpWallCol);

		}
		delete mpWallCol;
		mpWallCol = nullptr;
	}
}

// 壁のコライダー取得
CColliderMesh* CField::GetWallCol() const
{
	return mpWallCol;
}

void CField::CreateFieldObjects()
{
	mpCubeModel = CResourceManager::Get<CModel>("FieldCube");
	mpCylinderModel = CResourceManager::Get<CModel>("FieldCylinder");

	//new CMoveFloor
	//(
	//	mpCubeModel,
	//	CVector(0.0f, 10.0f, -50.0f), CVector(1.0f, 1.0f, 1.0f),
	//	CVector(50.0f, 0.0f, 0.0f), 10.0f
	//);
	//new CRotateFloor
	//(
	//	mpCylinderModel,
	//	CVector(-40.0f, 15.0f, 20.0f), CVector(1.0f, 1.0f, 1.0f),
	//	1.0f
	//);

	// 動かない床①
	new CMoveFloor
	(
		mpCubeModel,
		CVector(-20.0f, -20.0f, -340.0f), CVector(5.5f, 1.0f, 3.25f),
		CVector(0.0f, 0.0f, 0.0f), 5.0f
	);
	//// 動く床①
	//new CMoveFloor
	//(
	//	mpCubeModel,
	//	CVector(60.0f, 20.0f, 0.0f), CVector(0.25f, 1.0f, 0.25f),
	//	CVector(20.0f, 0.0f, 0.0f), 5.0f
	//);
	//// 動かない床②
	//new CMoveFloor
	//(
	//	mpCubeModel,
	//	CVector(100.0f, 20.0f, 0.0f), CVector(0.25f, 1.0f, 0.25f),
	//	CVector(0.0f, 0.0f, 0.0f), 5.0f
	//);
	//// 回転する床①
	//new CRotateFloor
	//(
	//	mpCubeModel,
	//	CVector(135.0f, 20.0f, 0.0f), CVector(1.0f, 1.0f, 0.25f),
	//	0.5f
	//);
	//// 動かない床②
	//new CMoveFloor
	//(
	//	mpCubeModel,
	//	CVector(135.0f, 20.0f, -35.0f), CVector(0.25f, 1.0f, 0.25f),
	//	CVector(0.0f, 0.0f, 0.0f), 5.0f
	//);
	//// 動かない床②
	//new CMoveFloor
	//(
	//	mpCubeModel,
	//	CVector(135.0f, 70.0f, -52.5f), CVector(0.25f, 1.0f, 0.25f),
	//	CVector(0.0f, 50.0f, 0.0f), 5.0f
	//);

	// ゴールモデル
	new CGoalObject
	(
		mpGoalModel,
		CVector(0.0f, 0.0f, -100.0f), CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);

	// 岩1モデル
	new CStone1
	(
		mpStone1,
		CVector(-80.0f, 0.0f, -200.0f), CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

	//// 岩1モデル
	//new CStone1
	//(
	//	mpStone1,
	//	CVector(30.0f, 0.0f, -700.0f), CVector(10.0f, 10.0f, 10.0f),
	//	CVector(60.0f, 0.0f, 0.0f)
	//);
}

void CField::Update()
{
}

void CField::Render()
{
	mpModel->Render(Matrix());
}
