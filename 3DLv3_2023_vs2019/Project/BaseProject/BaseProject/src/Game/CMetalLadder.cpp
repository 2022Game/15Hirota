#include "CMetalLadder.h"
#include "CStageManager.h"

// �R���X�g���N�^
CMetalLadder::CMetalLadder(std::string wireName, std::string wireCol, std::string topName,
	const CVector& moveUp, const CVector& moveForward)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, mClimbedMoveUp(moveUp)
	, mClimbMoveForward(moveForward)
{
	// �o�����ԃ��f���擾
	mpMetalLadderModel = CResourceManager::Get<CModel>(wireName);

	// �o�����Ԃ̃R���C�_�[�擾
	CModel* wirecol = CResourceManager::Get<CModel>(wireCol);
	mpWallCol = new CColliderMesh(this, ELayer::eMetalLadder, wirecol, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });

	// �o�����Ԃ̒���R���C�_�[�擾
	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eMetalLadderTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });

}

// �f�X�g���N�^
CMetalLadder::~CMetalLadder()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// ����֏��؂������̈ړ��ʂ��擾
void CMetalLadder::GetClimbedMoveVec(CVector* outUp, CVector* outForward) const
{
	*outUp = mClimbedMoveUp;
	*outForward = mClimbMoveForward;
}

// �X�V
void CMetalLadder::Update()
{
}

// �`��
void CMetalLadder::Render()
{
	mpMetalLadderModel->SetColor(mColor);
	mpMetalLadderModel->Render(Matrix());
}