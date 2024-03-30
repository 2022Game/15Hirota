#include "CWireMeshClimbWall.h"

// �R���X�g���N�^
CWireMeshClimbWall::CWireMeshClimbWall(std::string wireName, std::string topName,
	const CVector& moveUp, const CVector& moveForward)
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
	, mClimbedMoveUp(moveUp)
	, mClimbMoveForward(moveForward)
{
	// �o�����ԃ��f���擾
	mpWireMeshModel = CResourceManager::Get<CModel>(wireName);

	// �o�����Ԃ̃R���C�_�[�擾
	CModel* wireCol = CResourceManager::Get<CModel>("WireMeshCol");
	mpWallCol = new CColliderMesh(this, ELayer::eWireClimb, wireCol, true);
	mpWallCol->SetCollisionTags({ ETag::ePlayer });
	
	// �o�����Ԃ̒���R���C�_�[�擾
	CModel* top = CResourceManager::Get<CModel>(topName);
	mpWallTopCol = new CColliderMesh(this, ELayer::eWireClimbedTop, top, true);
	mpWallTopCol->SetCollisionTags({ ETag::ePlayer });
	mpWallTopCol->SetCollisionLayers({ ELayer::ePlayer });

}

// �f�X�g���N�^
CWireMeshClimbWall::~CWireMeshClimbWall()
{
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpWallTopCol);
}

// ����֏��؂������̈ړ��ʂ��擾
void CWireMeshClimbWall::GetClimbedMoveVec(CVector* outUp, CVector* outForward) const
{
	*outUp = mClimbedMoveUp;
	*outForward = mClimbMoveForward;
}

// �X�V
void CWireMeshClimbWall::Update()
{

}

// �`��
void CWireMeshClimbWall::Render()
{
	mpWireMeshModel->SetColor(mColor);
	mpWireMeshModel->Render(Matrix());
}