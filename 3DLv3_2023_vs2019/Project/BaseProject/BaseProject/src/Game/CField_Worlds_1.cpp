#include "CField_Worlds_1.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CField_Worlds_1::CField_Worlds_1()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// ステージのモデルデータ取得
	mpStageModel = CResourceManager::Get<CModel>("Stage");
	// 道のモデルデータ取得
	mpLoadModel = CResourceManager::Get<CModel>("Load");
	// 雲のモデルデータ取得
	mpCloudModel = CResourceManager::Get<CModel>("Cloud");
	// フェンスのモデルデータ取得
	mpFanceModel = CResourceManager::Get<CModel>("Fance");
	// 花のモデルデータ取得
	mpFlowersModel = CResourceManager::Get<CModel>("Flowers");
	// 草のモデルデータ取得
	mpGrassModel = CResourceManager::Get<CModel>("Grass");
	// 矢印看板のモデルデータ取得
	//mpArrowSignModel = CResourceManager::Get<CModel>("Arrow sign");

	//// キノコのモデルデータ取得
	//CModel* mushroom = CResourceManager::Get<CModel>("Mushroom");
	//mpMushroomSphere = new CColliderSphere
	//(
	//	this, 
	//	ELayer::eFieldWall, 
	//	1.0f
	//);

	//// 岩と低木モデル
	//CModel* rock_shrub = CResourceManager::Get<CModel>("Rock & Shrub");
	//mpRock_Shrud = new CColliderSphere
	//(
	//	this, ELayer::eField,
	//	1.0f
	//);

	//// 木と切り株と木の枝のモデルデータ取得
	//CModel* tree_branch = CResourceManager::Get<CModel>("Tree & Branch");
	//mpTree_BranchCol = new CColliderMesh(this, ELayer::eField, tree_branch, true);

	// 床のコライダー
	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// 壁のコライダー
	CModel* wallCol = CResourceManager::Get<CModel>("WallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);

	// 落下判定用のコライダー
	CModel* fallCol = CResourceManager::Get<CModel>("FallCol");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
}

CField_Worlds_1::~CField_Worlds_1()
{
	// コライダーを削除
	SAFE_DELETE(mpFloorCol);
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpFallCol);

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
CColliderMesh* CField_Worlds_1::GetWallCol() const
{
	return mpWallCol;
}

void CField_Worlds_1::Update()
{

}

void CField_Worlds_1::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
	mpLoadModel->SetColor(mColor);
	mpLoadModel->Render(Matrix());
	mpCloudModel->SetColor(mColor);
	mpCloudModel->Render(Matrix());
	mpFanceModel->SetColor(mColor);
	mpFanceModel->Render(Matrix());
	mpFlowersModel->SetColor(mColor);
	mpFlowersModel->Render(Matrix());
	mpGrassModel->SetColor(mColor);
	mpGrassModel->Render(Matrix());
	/*mpArrowSignModel->SetColor(mColor);
	mpArrowSignModel->Render(Matrix());*/
}