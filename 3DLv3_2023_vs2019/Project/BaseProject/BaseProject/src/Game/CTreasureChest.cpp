#include "CTreasureChest.h"
#include "CCollisionManager.h"
#include "CPlayer.h"
#include "CInput.h"
#include "Maths.h"
#include "CModel.h"
#include "CStageManager.h"
#include "COperationUI.h"

#define WAIT_TIME 5.0f
#define FOV_ANGLE 100.0f
#define ROTATE_TIME 0.5f

CTreasureChest::CTreasureChest(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
{
	// �󔠃��f��
	mpChest =  CResourceManager::Get<CModel>("TreasureChest");
	// �󔠃��f���̃R���C�_�[
	CModel* col = CResourceManager::Get<CModel>("TreasureChestWallCol");
	mpChestCol = new CColliderMesh(this, ELayer::eFieldWall, col, true);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpChestCol->SetCollisionTags({ ETag::ePlayer});
	mpChestCol->SetCollisionLayers({ ELayer::ePlayer});

	Position(pos);
	Scale(scale);
	Rotation(rot);

	mpChestCol->SetEnable(true);

	// �����ʒu��ݒ�
	mStartPos = Position();
}

CTreasureChest::~CTreasureChest()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpChestCol);
}

void CTreasureChest::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}

void CTreasureChest::Update()
{
}

void CTreasureChest::Render()
{
	mpChest->SetColor(mColor);
	mpChest->Render(Matrix());
}

CTreasureChestTwo::CTreasureChestTwo(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: mStateStep(0)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mDefaultRot(rot)
	, mWaitTime(0.0f)
	, mRotateEndAngle(0.0f)
	, mRotateStartAngle(0.0f)
	, mStartPos(CVector::zero)
{
	// T�L�[�̉摜�\��
	mpKey = new COperationUI("TUI");
	mpKey->SetShow(false);

	// �󔠊W���f��
	mpChestTwo =  CResourceManager::Get<CModel>("TreasureChestTwo");

	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(mDefaultRot);

	mStartPos = Position();
}

CTreasureChestTwo::~CTreasureChestTwo()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
}

void CTreasureChestTwo::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@���
void CTreasureChestTwo::UpdateIdle()
{
	CPlayer* player = CPlayer::Instance();
	// �v���C���[�����������
	// R�L�[�������ƃA�C�e������肵�ĕ󔠂̊W���J���鏈��
	if (IsFoundPlayer())
	{
		if (CInput::PushKey('T'))
		{
			int Rondom = Math::Rand(1, 2);
			// �񕜃A�C�e��
			if (Rondom == 1)
			{
				player->AddItem(CPlayer::ItemType::HEALING);
			}
			// ���G�A�C�e��
			else if (Rondom == 2)
			{
				player->AddItem(CPlayer::ItemType::ATTACK_UP);
			}
			mWaitTime = 0.0f;
			mRotateStartAngle = 0.0f;
			mRotateEndAngle = 85.0f;
			ChangeState(EState::Two);
		}

		mpKey->SetShow(true);
	}
	else
	{
		mpKey->SetShow(false);
	}
}

// �󔠂̊W���J������
void CTreasureChestTwo::UpdateTwo()
{
	if (mWaitTime < ROTATE_TIME)
	{
		// ��]�J�n���̊p�x���珙�X�ɉ�]�I�����̊p�x�։�]����
		float per = mWaitTime / ROTATE_TIME;
		float angleZ = Math::Lerp
		(
			mRotateStartAngle,
			mRotateEndAngle,
			per
		);
		Rotation(mDefaultRot * CQuaternion(CVector(0.0f, 0.0f, angleZ)));
		mWaitTime += Time::DeltaTime();
	}
	else
	{
		mWaitTime = 0.0f;
		Rotation(mDefaultRot * CQuaternion(CVector(0.0f, 0.0f, mRotateEndAngle)));
		ChangeState(EState::End);
	}
}

void CTreasureChestTwo::UpdateEnd()
{
	mpKey->SetShow(false);
}

// �X�V
void CTreasureChestTwo::Update()
{
	switch (mState)
	{
	case EState::Idle:
		UpdateIdle();
		break;
	case EState::Two:
		UpdateTwo();
		break;
	case EState::End:
		UpdateEnd();
		break;
	}

	CVector object = Position();
	CVector chestPos = object + CVector(0.0f, 25.0f, 0.0f) + VectorX() * 3.0f;
	mpKey->SetWorldPos(chestPos);
	/*CDebugPrint::Print("chestPos: %f %f %f\n", chestPos.X(), chestPos.Y(), chestPos.Z());*/
}

// �v���C���[�ǐ�
bool CTreasureChestTwo::IsFoundPlayer() const
{
	CVector playerPos = CPlayer::Instance()->Position();
	CVector object = Position();

	// �v���C���[�Ƃ̋������v�Z����
	float distance = (playerPos - object).Length();
	const float detectionRadius = 20.0f;

	// �v���C���[�Ƃ̋��������o���a�ȓ��ł���΁A�v���C���[��F������
	if (distance <= detectionRadius)
	{
		return true;
	}

	return false;
}

// �`��
void CTreasureChestTwo::Render()
{
	mpChestTwo->SetColor(mColor);
	mpChestTwo->Render(Matrix());
}