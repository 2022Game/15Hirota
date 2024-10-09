#include "COneShotFloorField.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CStageManager.h"

// �R���X�g���N�^
COneShotFloorField::COneShotFloorField()
	: CObjectBase(ETag::eField,ETaskPriority::eDefault)
{
	// �X�e�[�W�̃��f���擾
	mpStageModel = CResourceManager::Get<CModel>("Stage1Base");

	// ���C���̃��f���擾
	mpLineModel = CResourceManager::Get<CModel>("Stage1Line");

	// �X�e�[�W�̃R���C�_�[�擾
	CModel* floorCol = CResourceManager::Get<CModel>("Stage1FloorCol");
	mpStageFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);
}

COneShotFloorField::~COneShotFloorField()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpStageFloorCol);
}

void COneShotFloorField::Update()
{

}

void COneShotFloorField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
	mpLineModel->SetColor(mColor);
	mpLineModel->Render(Matrix());
}