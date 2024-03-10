#include "CClimbWall.h"

// �R���X�g���N�^
CClimbWall::CClimbWall()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// �o��郂�f���擾
	mpWallModel = CResourceManager::Get<CModel>("Stage2Climb");

	mpWallCol = new CColliderMesh(this, ELayer::eClimb, mpWallModel, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CClimbWall::~CClimbWall()
{
	SAFE_DELETE(mpWallCol);
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