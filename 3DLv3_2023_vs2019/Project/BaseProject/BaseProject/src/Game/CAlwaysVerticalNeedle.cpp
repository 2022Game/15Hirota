#include "CAlwaysVerticalNeedle.h"
#include "CCharaBase.h"

// �U���ҋ@����
#define ATTACKWAIT_TIME 3.0f
// �ҋ@����
#define WAIT_TIME 5.0f
// �߂���
#define RETURN_TIME 5.0f
// �U����̍ċN����
#define WAIT_ATTACK_TIME 5.0f

// �R���X�g���N�^
CAlwaysVerticalNeedle::CAlwaysVerticalNeedle(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eNeedleObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
	, mWaitAttackTime(0.0f)
	, mIsAttack(false)
	, mIsCollision(false)
{
	// �펞�o�Ă���j���f��
	mpNeedleBase = CResourceManager::Get<CModel>("AlwaysNeedle");

	// �펞�o�Ă���j���f���̃R���C�_�[
	CModel* baseCol = CResourceManager::Get<CModel>("AlwaysNeedleBaseCol");
	mpNeedleBaseCol = new CColliderMesh(this, ELayer::eFieldWall, baseCol, true);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	mpNeedleBaseCol->SetCollisionTags({ ETag::ePlayer});
	mpNeedleBaseCol->SetCollisionLayers({ ELayer::ePlayer});

	// �펞�o�Ă���j���f���̐j�R���C�_�[
	CModel* needleCol = CResourceManager::Get<CModel>("AlwaysNeedleCol");
	mpNeedleCol = new CColliderMesh(this, ELayer::eNeedleCol, needleCol, true);
	// �펞�o�Ă���j���f���̐j�R���C�_�[
	mpNeedleCol->SetCollisionTags({ ETag::ePlayer });
	mpNeedleCol->SetCollisionLayers({ ELayer::eDamageCol });

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CAlwaysVerticalNeedle::~CAlwaysVerticalNeedle()
{
	SAFE_DELETE(mpNeedleBaseCol);
	SAFE_DELETE(mpNeedleCol)
}

// �Փˏ���
void CAlwaysVerticalNeedle::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���j�R���C�_�[�ł����
	if (self == mpNeedleCol)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			if (!mIsAttack)
			{
				// �_���[�W��^����
				chara->TakeDamage(1);
				mIsAttack = true;
				//// ���łɍU���ς݂̃L�����łȂ����
				//if (!IsAttackHitObj(chara))
				//{
				//	// �_���[�W��^����
				//	chara->TakeDamage(1);

				//	// �U���ς݃��X�g�ɒǉ�
				//	AddAttackHitObj(chara);

				//	mIsAttack = true;
				//}
			}
			mIsCollision = true;
		}
	}
}

// �X�V����
void CAlwaysVerticalNeedle::Update()
{
	if (mIsAttack)
	{
		mpNeedleCol->SetEnable(false);
		mWaitAttackTime += Time::DeltaTime();
		if (mWaitAttackTime >= WAIT_ATTACK_TIME)
		{
			// �v���C���[�ɓ����������Ԃ����Z�b�g
			mWaitAttackTime = 0.0f;
			mIsAttack = false;
			mAttackHitObjects.clear();
			mpNeedleCol->SetEnable(true);
		}
	}
	mIsCollision = false;
}

// �`�揈��
void CAlwaysVerticalNeedle::Render()
{
	mpNeedleBase->SetColor(mColor);
	mpNeedleBase->Render(Matrix());
}