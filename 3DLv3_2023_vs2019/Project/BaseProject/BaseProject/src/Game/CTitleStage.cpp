#include "CTitleStage.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CStageManager.h"

// �R���X�g���N�^
CTitleStage::CTitleStage()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// �^�C�g���X�e�[�W�̃��f��
	mpStageModel = CResourceManager::Get<CModel>("TitleStage");

	// �^�C�g���X�e�[�W�̏��R���C�_�[
	CModel* TitleCol = CResourceManager::Get<CModel>("TitleCol");
	mpTitleCol = new CColliderMesh(this, ELayer::eField, TitleCol, true);
}

// �f�X�g���N�^
CTitleStage::~CTitleStage()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpTitleCol);
}

// �X�V����
void CTitleStage::Update()
{

}

// �`�揈��
void CTitleStage::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}