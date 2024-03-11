#include "CClimbWall.h"

// �R���X�g���N�^
CClimbWall::CClimbWall(std::string climbName, std::string topName, const CVector& moveVec)
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
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
const CVector& CClimbWall::GetClimbedMoveVec() const
{
	return mClimbedMoveVec;
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