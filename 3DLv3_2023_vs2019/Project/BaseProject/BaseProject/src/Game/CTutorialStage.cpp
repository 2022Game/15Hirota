#include "CTutorialStage.h"
#include "CCollisionManager.h"

CTutorialStage::CTutorialStage()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// �X�e�[�W�̃��f���f�[�^�擾
	mpStageModel = CResourceManager::Get<CModel>("TutorialStage");

	// ���̃R���C�_�[
	CModel* floorCol = CResourceManager::Get<CModel>("TutorialFCol");
	mpFloor = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �ǂ̃R���C�_�[
	CModel* wallCol = CResourceManager::Get<CModel>("TutorialWCol");
	mpWall = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);
}

CTutorialStage::~CTutorialStage()
{
	// �R���C�_�[���폜
	SAFE_DELETE(mpFloor);
	SAFE_DELETE(mpWall);
}

void CTutorialStage::Update()
{

}

void CTutorialStage::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}