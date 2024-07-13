#include "CGoalObject.h"
#include "CPlayer.h"
#include "CStageManager.h"

// �R���X�g���N�^
CGoalObject::CGoalObject(const CVector& pos, const CVector& scale, const CVector& rot)
{
	// �S�[���̓y�䃂�f���擾
	mpModel = CResourceManager::Get<CModel>("GoalCube");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, mpModel, true);

	// �S�[���̃|�X�g���f���擾
	mpGoalPost = CResourceManager::Get<CModel>("GoalPost");

	// �|�X�g�̃R���C�_�[���쐬
	mpColliderLine = new CColliderLine
	(
		this, ELayer::eGoalCol,
		CVector(0.0f, 5.0f, 0.0f),
		CVector(0.0f, 30.0, 0.0f)
	);
	mpColliderLine->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderLine->SetCollisionTags({ ETag::ePlayer });

	// �Ă��؂�̃R���C�_�[���쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eGoalCol,
		2.0f//0.5f
	);
	mpColliderSphere->SetCollisionLayers({ ELayer::ePlayer });
	mpColliderSphere->SetCollisionTags({ ETag::ePlayer });
	// �S�[���R���C�_�[��������ւ��炷
	mpColliderSphere->Position(0.0f, 20.0f, 0.0f);


	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CGoalObject::~CGoalObject()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpColliderMesh);
	SAFE_DELETE(mpColliderLine);
	SAFE_DELETE(mpColliderSphere);
}

// �X�V����
void CGoalObject::Update()
{
	
}

// �`�揈��
void CGoalObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
	mpGoalPost->SetColor(mColor);
	mpGoalPost->Render(Matrix());
}