#include "CNeedleLeftRight.h"
#include "CCharaBase.h"
#include "Maths.h"

// �j�̏㏸����ۂ̍ő�l
#define MAXHEIGHT 0.8f
// �j�̏㏸�X�s�[�h
#define NEEDLE_INCREASE_VALUE 30.0f
// �j�̉��~�X�s�[�h
#define NEEDLE_DESCENDING_VALUE 20.0f

// �U���ҋ@����
#define ATTACKWAIT_TIME 3.0f
// �ҋ@����
#define WAIT_TIME 4.0f
// �߂���
#define RETURN_TIME 5.0f
// �U����̍ċN����
#define WAIT_ATTACK_TIME 5.0f

// �R���X�g���N�^
CNeedleLeftRight::CNeedleLeftRight(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eNeedleObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mWait(0.0f)
	, mAttackWait(0.0f)
	, mElapsedTime(0.0f)
	, mWaitAttackTime(0.0f)
	, mStartPosition(0.0f)
	, mEndPosition(0.0f)
	, mIsCollision(false)
	, mIsAttack(false)
{
	// �j���f���擾
	mpNeedle = CResourceManager::Get<CModel>("NeedleLeftRight");

	// �j���f���̃R���C�_�[���쐬
	CModel* Col = CResourceManager::Get<CModel>("NeedleColLeftRight");
	mpColliderMesh = new CColliderMesh(this, ELayer::eNeedleCol, Col, true);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer, ETag::eItemRecover, ETag::eItemInvincible });
	mpColliderMesh->SetCollisionLayers({ ELayer::eDamageCol, ELayer::eRecoverCol, ELayer::eInvincbleCol });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderMesh->SetCollisionTag(mReactionTag, true);
	mpColliderMesh->SetCollisionLayer(mReactionLayer, true);

	Position(pos);
	Scale(scale);
	Rotation(rot);

	// �����ʒu��ݒ�
	mStartPos = Position();
}

// �f�X�g���N�^
CNeedleLeftRight::~CNeedleLeftRight()
{
	SAFE_DELETE(mpColliderMesh);
}

// �Փˏ���
void CNeedleLeftRight::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���j�R���C�_�[�ł����
	if (self == mpColliderMesh)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			// ���łɍU���ς݂̃L�����łȂ����
			if (!IsAttackHitObj(chara))
			{
				// �_���[�W��^����
				chara->TakeDamage(1);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);

				mIsAttack = true;
			}
			mIsCollision = true;
		}
	}

}

// �X�e�[�W�J�n���̈ʒu��ݒ�
void CNeedleLeftRight::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �U���J�n
void CNeedleLeftRight::AttackStart()
{
	CObjectBase::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpColliderMesh->SetEnable(true);
}

// �U���I��
void CNeedleLeftRight::AttackEnd()
{
	CObjectBase::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpColliderMesh->SetEnable(false);
}

// ��Ԃ�؂�ւ���
void CNeedleLeftRight::ChangeState(EState state)
{
	mState = state;
	mElapsedTime = 0.0f;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CNeedleLeftRight::UpdateIdle()
{
	if (mWait <= WAIT_TIME)
	{
		// �����ʒu��ݒ�
		mStartPosition = 0.0f;
		// �Ō�̈ʒu��ݒ�
		mEndPosition = 7.0f;
		mElapsedTime = 0.0f;
		// �U����Ԃֈڍs
		ChangeState(EState::Attack);
	}
}
#define NEEDLE_TIME 0.05f

// �U�����
void CNeedleLeftRight::UpdateAttack()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �U����̑҂�����
	case 0:
		if (mElapsedTime < NEEDLE_TIME)
		{
			mpColliderMesh->SetEnable(true);

			float per = mElapsedTime / NEEDLE_TIME;
			float positionX = Math::Lerp
			(
				mStartPosition,
				mEndPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(positionX, 0.0f, 0.0f));
		}
		else
		{
			Position(mStartPos + CVector(mEndPosition, 0.0f, 0.0f));
			mAttackWait += Time::DeltaTime();
			if (mAttackWait >= ATTACKWAIT_TIME)
			{
				mElapsedTime = 0.0f;
				mStateStep++;
			}
		}
		break;
		// �X�e�b�v1 �j��߂�
	case 1:
		// ���~������
		if (mElapsedTime < NEEDLE_TIME)
		{
			float per = mElapsedTime / NEEDLE_TIME;
			float positionX = Math::Lerp
			(
				mEndPosition,
				mStartPosition,
				per
			);
			mElapsedTime += Time::DeltaTime();

			Position(mStartPos + CVector(positionX, 0.0f, 0.0f));
		}
		else
		{
			// ����������̏�ԂɑJ��
			ChangeState(EState::AttackEnd);
			mStateStep = 0;
			mAttackWait = 0.0f;
			mElapsedTime = 0.0f;
			Position(mStartPos + CVector(mStartPosition, 0.0f, 0.0f));
			mpColliderMesh->SetEnable(false);
		}
		break;
	}
}

// �U���I�����
void CNeedleLeftRight::UpdateAttackEnd()
{
	mWait += Time::DeltaTime();
	if (mWait >= WAIT_TIME)
	{
		mWait = 0.0f;
		ChangeState(EState::Idle);
	}
}

// �X�V
void CNeedleLeftRight::Update()
{
	//CDebugPrint::Print("PositoinY:%f\n", Position().Y());
	if (mIsAttack)
	{
		mpColliderMesh->SetEnable(false);
		mWaitAttackTime += Time::DeltaTime();
		if (mWaitAttackTime >= WAIT_ATTACK_TIME)
		{
			// �v���C���[�ɓ����������Ԃ����Z�b�g
			mWaitAttackTime = 0.0f;
			mIsAttack = false;
			mAttackHitObjects.clear();
		}
	}

	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �U�����
	case EState::Attack:
		UpdateAttack();
		break;
		// �U���I�����
	case EState::AttackEnd:
		UpdateAttackEnd();
		break;
	}
	//CDebugPrint::Print("wait%f\n", mWait);
	//CDebugPrint::Print("attackwait%f\n", mAttackWait);
	//CDebugPrint::Print("waitAttackTime%f\n", mWaitAttackTime);
}

// �`��
void CNeedleLeftRight::Render()
{
	mpNeedle->SetColor(mColor);
	mpNeedle->Render(Matrix());
}


// �j���f���̓y��
CNeedleLeftRightBase::CNeedleLeftRightBase(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CObjectBase(ETag::eNeedleObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
{
	// �j�x�[�X���f��
	mpNeedleBase = CResourceManager::Get<CModel>("NeedleBaseLeftRight");	

	// �j���f���̃R���C�_�[���쐬
	CModel* Col1 = CResourceManager::Get<CModel>("NeedleBaseColLeftRight");
	mpColliderBaseMesh = new CColliderMesh(this, ELayer::eFieldWall, Col1, true);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpColliderBaseMesh->SetCollisionTags({ ETag::ePlayer, ETag::eItemRecover, ETag::eItemInvincible });
	mpColliderBaseMesh->SetCollisionLayers({ ELayer::ePlayer, ELayer::eRecoverCol, ELayer::eInvincbleCol });

	// �������ɐݒ肳�ꂽ�G�ꂽ���ɔ�������I�u�W�F�N�g�^�O��
	// �R���C�_�[�̃��C���[���ʂɐݒ�
	mpColliderBaseMesh->SetCollisionTag(mReactionTag, true);
	mpColliderBaseMesh->SetCollisionLayer(mReactionLayer, true);
	mpColliderBaseMesh->SetEnable(true);

	Position(pos);
	Scale(scale);
	Rotation(rot);

	// �����ʒu��ݒ�
	mStartPos = Position();
}

// �f�X�g���N�^
CNeedleLeftRightBase::~CNeedleLeftRightBase()
{
	SAFE_DELETE(mpColliderBaseMesh)
}

void CNeedleLeftRightBase::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

void CNeedleLeftRightBase::Update()
{
	mpColliderBaseMesh->SetEnable(true);
}

void CNeedleLeftRightBase::Render()
{
	mpNeedleBase->SetColor(mColor);
	mpNeedleBase->Render(Matrix());
}