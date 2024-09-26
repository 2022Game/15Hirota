#include "CNumberFloor1.h"
#include "CColliderMesh.h"
#include "CStageManager.h"

// �R���X�g���N�^
CNumberFloor1::CNumberFloor1(const CVector& pos, const CVector& scale, const CVector& rot,
	std::string modelPath)
	: CNumberFloorBase(pos, scale, rot)
	, mStateStep(0)
{
	// ���̃��f���擾
	mpModel = CResourceManager::Get<CModel>(modelPath);

	// ���̃R���C�_�[�쐬
	mpCollider = new CColliderMesh(this, ELayer::eField, mpModel, true);
	mpCollider->SetCollisionTags({ ETag::ePlayer });
	mpCollider->SetCollisionLayers({ ELayer::ePlayer });

	SetModelPath("Number1");

	Position(pos);
	Scale(scale);
	Rotate(rot);

	mStartPos = Position();
}

// �f�X�g���N�^
CNumberFloor1::~CNumberFloor1()
{
	CStageManager::RemoveTask(this);
}

// �҂���Ԃ̏���
void CNumberFloor1::UpdateWaiting()
{
	if (mIsCollision)
	{
		SetColor(CColor(0.5f, 0.1f, 0.1f, 1.0f));
	}

	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g�\���̕ύX
	case 0:
	{
		if (!mIsCollision)
		{
			mStateStep++;
		}
		break;
	}
	case 1:
	{
		mpModel = CResourceManager::Get<CModel>("Number0");
		mStateStep = 0;
		ChangeState(EState::Falling);
		break;
	}
	break;
	}
}

void CNumberFloor1::Update()
{
	CNumberFloorBase::Update();
}