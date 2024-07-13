#include "CHopsAndHoopsField.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CStageManager.h"

// �R���X�g���N�^
CHopsAndHoopsField::CHopsAndHoopsField()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// �X�e�[�W�̃��f���擾
	mpStageModel = CResourceManager::Get<CModel>("HopsAndHoops(Base)");

	// �X�e�[�W�̃R���C�_�[�擾
	CModel* floorCol = CResourceManager::Get<CModel>("HopsAndHoops(Col)");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);
}

// �f�X�g���N�^
CHopsAndHoopsField::~CHopsAndHoopsField()
{
	CStageManager::RemoveTask(this);
	// �R���C�_�[�폜
	SAFE_DELETE(mpFloorCol);
}

// �X�V����
void CHopsAndHoopsField::Update()
{

}

// �`�揈��
void CHopsAndHoopsField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}