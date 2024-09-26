#include "CNumberFloor2.h"
#include "CColliderMesh.h"
#include "CStageManager.h"

// �R���X�g���N�^
CNumberFloor2::CNumberFloor2(const CVector& pos, const CVector& scale, const CVector& rot,
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

	SetModelPath("Number2");

	Position(pos);
	Scale(scale);
	Rotate(rot);

	mStartPos = Position();
}

// �f�X�g���N�^
CNumberFloor2::~CNumberFloor2()
{
	CStageManager::RemoveTask(this);
}

// �҂���Ԃ̏���
void CNumberFloor2::UpdateWaiting()
{
	if (mIsCollision)
	{
		SetColor(CColor(0.5f, 0.1f, 0.1f, 1.0f));
	}
	else
	{
		SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	}

	switch (mStateStep)
	{
		// �X�e�b�v0 �I�u�W�F�N�g�\���̕ύX
	case 0:
	{
		if (!mCase0End)
		{
			// �v���C���[�����ꂽ��Idle�ɑJ��
			if (!mIsCollision)
			{
				mpModel = CResourceManager::Get<CModel>("Number1");
				mStateStep++;
				mCase0End = true;
				ChangeState(EState::Idle);
			}
			break;
		}

		if (!mIsCollision && mCase0End)
		{
			SetColor(CColor(0.5f, 0.0f, 0.0f, 1.0f));
			mStateStep++;
		}
		break;
	}
	// �X�e�b�v1 ��ԑJ��
	case 1:
	{
		if (!mIsCollision)
		{
			mpModel = CResourceManager::Get<CModel>("Number0");
			mStateStep = 0;
			ChangeState(EState::Falling);
		}
	}
	break;
	}
}

void CNumberFloor2::Update()
{
	CNumberFloorBase::Update();
}