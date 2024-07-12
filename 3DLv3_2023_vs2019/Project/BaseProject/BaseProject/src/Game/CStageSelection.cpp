#include "CStageSelection.h"
#include "CCollisionManager.h"
#include "CStageManager.h"
#include "CCamera.h"

CStageSelection::CStageSelection()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// ���f���f�[�^�擾
	mpModel = CResourceManager::Get<CModel>("StageSelect");


	/*CModel* wallCol = CResourceManager::Get<CModel>("StageSelectionWallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);*/

	CModel* floorCol = CResourceManager::Get<CModel>("StageSelectFloor");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, floorCol, true);

	CreateFieldObjects();
}

CStageSelection::~CStageSelection()
{
	CStageManager::RemoveTask(this);
	// �R���C�_�[��j��
	SAFE_DELETE(mpColliderMesh);

	//if (mpWallCol != nullptr)
	//{
	//	// ���C���J��������ǂ̃R���C�_�[�ւ̎Q�Ƃ���菜��
	//	CCamera* mainCamera = CCamera::MainCamera();
	//	if (mainCamera != nullptr)
	//	{
	//		mainCamera->RemoveCollider(mpWallCol);

	//	}
	//	delete mpWallCol;
	//	mpWallCol = nullptr;
	//}
}

//// �ǂ̃R���C�_�[�擾
//CColliderMesh* CStageSelection::GetWallCol() const
//{
//	return mpWallCol;
//}

void CStageSelection::CreateFieldObjects()
{

}

void CStageSelection::Update()
{
}

void CStageSelection::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}