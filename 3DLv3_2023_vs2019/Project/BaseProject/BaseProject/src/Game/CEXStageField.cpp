#include "CEXStageField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CEXStageField::CEXStageField()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// �X�e�[�W�̃��f���f�[�^�擾
	mpStageModel = CResourceManager::Get<CModel>("StageModel");
	
	// ���̃R���C�_�[
	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �ǂ̃R���C�_�[
	CModel* wallCol = CResourceManager::Get<CModel>("WallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);
}

CEXStageField::~CEXStageField()
{
	// �R���C�_�[���폜
	SAFE_DELETE(mpFloorCol);
	SAFE_DELETE(mpWallCol);

	if (mpWallCol != nullptr)
	{
		// ���C���J��������ǂ̃R���C�_�[�ւ̎Q�Ƃ���菜��
		CCamera* mainCamera = CCamera::MainCamera();
		if (mainCamera != nullptr)
		{
			mainCamera->RemoveCollider(mpWallCol);
		}
		delete mpWallCol;
		mpWallCol = nullptr;
	}
}

CColliderMesh* CEXStageField::GetWallCol() const
{
	return mpWallCol;
}

void CEXStageField::Update()
{
}

void CEXStageField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}