#include "CNeedle.h"
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
#define WAIT_TIME 5.0f
// �߂���
#define RETURN_TIME 5.0f
// �U����̍ċN����
#define WAIT_ATTACK_TIME 5.0f

// �R���X�g���N�^
CNeedle::CNeedle(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNeedle)
	, mState(EState::Idle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
	, mStateStep(0)
	, mWait(0.0f)
	, mReturnTime(0.0f)
	, mAttackWait(0.0f)
	, mWaitAttackTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mIsCollision(false)
	, mIsAttack(false)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// �j���f���擾
	mpNeedle = CResourceManager::Get<CModel>("Needle");

	// �j���f���̃R���C�_�[���쐬
	CModel* Col = CResourceManager::Get<CModel>("NeedleCol");
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


	// �j���f���̃R���C�_�[���쐬
	CModel* Col1 = CResourceManager::Get<CModel>("NeedleBaseCol");
	mpColliderBaseMesh = new CColliderMesh(this, ELayer::eField, Col1, true);
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


	ChangeState(EState::Idle);

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CNeedle::~CNeedle()
{
	SAFE_DELETE(mpColliderMesh);
	SAFE_DELETE(mpColliderBaseMesh)
}

// �Փˏ���
void CNeedle::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
void CNeedle::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

// �U���J�n
void CNeedle::AttackStart()
{
	CRideableObject::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I�t�ɂ���
	mpColliderMesh->SetEnable(true);
}

// �U���I��
void CNeedle::AttackEnd()
{
	CRideableObject::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpColliderMesh->SetEnable(false);
}

// ��Ԃ�؂�ւ���
void CNeedle::ChangeState(EState state)
{
	mState = state;
	mStateStep = 0;
}

// �ҋ@��Ԃ̏���
void CNeedle::UpdateIdle()
{
	mpColliderBaseMesh->SetEnable(true);
	if (mWait <= WAIT_TIME)
	{
		ChangeState(EState::Attack);
	}
}

// �U�����
void CNeedle::UpdateAttack()
{
	// �X�e�b�v���Ƃɏ�����؂�ւ�
	switch (mStateStep)
	{
		// �X�e�b�v0 �U����̑҂�����
	case 0:
		// �j���㏸������
		if (Position().Y() < mStartPos.Y() + MAXHEIGHT)
		{
			mpColliderMesh->SetEnable(true);
			// �㏸������
			CVector mSpeed = mMoveSpeed;
			mSpeed = CVector(0.0f, NEEDLE_INCREASE_VALUE * Time::DeltaTime(), 0.0f);
			Position(Position() + mSpeed);
		}
		// �ő�l�ɂȂ�����A�ҋ@������
		else
		{
			mAttackWait += Time::DeltaTime();
			if (mAttackWait >= ATTACKWAIT_TIME)
			{
				mStateStep++;
			}
		}
		break;
		// �X�e�b�v1 �j��߂�
	case 1:
		// ���~������
		CVector mDawnSpeed = mMoveSpeed;
		mDawnSpeed = CVector(0.0f, NEEDLE_DESCENDING_VALUE * Time::DeltaTime(), 0.0f);
		Position(Position() - mDawnSpeed);

		// �j�I�u�W�F�N�g�̈ʒu��0.5f�ɂȂ�����
		// ���̈ʒu�ɖ߂�
		if (CVector::Distance(Position(), mStartPos) < 0.5f)
		{
			Position(mStartPos);
			// ����������̏�ԂɑJ��
			ChangeState(EState::AttackEnd);
			mStateStep = 0;
			mAttackWait = 0.0f;
			mpColliderMesh->SetEnable(false);
		}
		break;
	}
}

// �U���I�����
void CNeedle::UpdateAttackEnd()
{
	mpColliderBaseMesh->SetEnable(true);
	mWait += Time::DeltaTime();
	if (mWait >= WAIT_TIME)
	{
		mWait = 0.0f;
		ChangeState(EState::Idle);
	}
}

// �X�V
void CNeedle::Update()
{
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
void CNeedle::Render()
{
	mpNeedle->SetColor(mColor);
	mpNeedle->Render(Matrix());
}


// �j���f���̓y��
CNeedleBase::CNeedleBase(const CVector& pos, const CVector& scale, const CVector& rot,
	ETag reactionTag, ELayer reactionLayer)
	: CRideableObject(ETaskPriority::eNeedle)
	, mReactionTag(reactionTag)
	, mReactionLayer(reactionLayer)
{
	// �����ʒu��ݒ�
	mStartPos = Position();

	// �j�x�[�X���f��
	mpNeedleBase = CResourceManager::Get<CModel>("Needlebase");

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CNeedleBase::~CNeedleBase()
{
	
}

void CNeedleBase::SetStartPosition(const CVector& pos)
{
	mStartPos = pos;
	Position(mStartPos);
}

void CNeedleBase::Update()
{
}

void CNeedleBase::Render()
{
	mpNeedleBase->SetColor(mColor);
	mpNeedleBase->Render(Matrix());
}