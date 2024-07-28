#include "CSeesawAdventure.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CStageManager.h"

// �R���X�g���N�^
CSeesawAdventure::CSeesawAdventure()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// �X�e�[�W�̃��f���擾
	mpStageModel = CResourceManager::Get<CModel>("SeesawStage(Base)");

	// �X�e�[�W�̃R���C�_�[�擾
	CModel* floorCol = CResourceManager::Get<CModel>("SeesawStage(Floor)");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �ǂ̃R���C�_�[
	CModel* wallCol = CResourceManager::Get<CModel>("SeesawStage(Wall)");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);
}

// �f�X�g���N�^
CSeesawAdventure::~CSeesawAdventure()
{
	CStageManager::RemoveTask(this);
	// �R���C�_�[�폜
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

// �ǂ̃R���C�_�[�擾
CColliderMesh* CSeesawAdventure::GetWallCol() const
{
	return mpWallCol;
}

// �X�V����
void CSeesawAdventure::Update()
{

}

// �`�揈��
void CSeesawAdventure::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}