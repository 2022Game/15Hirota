#include "CClimbWall.h"

// �R���X�g���N�^
CClimbWall::CClimbWall(std::string climbName, std::string topName,
	const CVector& moveUp, const CVector& moveForward)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
	, mClimbedMoveUp(moveUp)
	, mClimbMoveForward(moveForward)
{
	// �o��郂�f���擾
	mpWallModel = CResourceManager::Get<CModel>(climbName);

	mpWallCol = new CColliderMesh(this, ELayer::eClimb, mpWallModel, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });

	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eClimbedTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });
}

// �f�X�g���N�^
CClimbWall::~CClimbWall()
{
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// ����֏��؂������̈ړ��ʂ��擾
void CClimbWall::GetClimbedMoveVec(CVector* outUp, CVector* outForward) const
{
	*outUp = mClimbedMoveUp;
	*outForward = mClimbMoveForward;
}

// �X�V
void CClimbWall::Update()
{

}

// �`��
void CClimbWall::Render()
{
	mpWallModel->SetColor(mColor);
	mpWallModel->Render(Matrix());
}