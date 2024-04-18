#include "CAttackPotion.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "Maths.h"
#include "CSound.h"

// �d��
#define GRAVITY 0.0625f
// �U���|�[�V�����̃X�s�[�h
#define ATTACKPOTION_SPEED 45.0f

CAttackPotion::CAttackPotion()
	: mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mMoveVector(0.0f, 0.0f, 0.0f)
	, mStartPos(0.0f, 0.0f, 0.0f)
	, mElapsedTime(0.0f)
	, mIsGround(false)
	, mAttackUsed(false)
	, mIsHeld(false)
{
	// �U���̓A�b�v���f���擾
	mpAttackPotion = CResourceManager::Get<CModel>("AttackPotion");

	// �U���̓A�b�v�R���C�_�[�쐬
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		1.5f
	);
	// �Փ˒�p�̃R���C�_�[�ƏՓ˔�����s��
	// �^�O�t��
	// ���C���[�t��
	// �R���C�_�[�̈ʒu�𒲐�
	mpAttackCol->SetCollisionTags({ ETag::ePlayer, ETag::eRideableObject, ETag::eField, });
	mpAttackCol->SetCollisionLayers({ ELayer::ePlayer, ELayer::eBlockCol, ELayer::eField,ELayer::eFieldWall });
	mpAttackCol->Position(0.0f, 1.0f, 0.0f);

	// �U���̓A�b�v�R���C�_�[�쐬(�n�ʂƕ�)
	mpFieldCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		1.5f
	);
	mpFieldCol->SetCollisionTags({ ETag::eRideableObject, ETag::eField, });
	mpFieldCol->SetCollisionLayers({ ELayer::eField,ELayer::eFieldWall });
	mpFieldCol->Position(0.0f, 1.0f, 0.0f);

	// �ŏ��̓R���C�_�[���I���ɂ��Ă���
	mpAttackCol->SetEnable(true);
	mpFieldCol->SetEnable(true);

}

CAttackPotion::~CAttackPotion()
{
	SAFE_DELETE(mpAttackCol);
	SAFE_DELETE(mpFieldCol);
}

// �Փˏ���
void CAttackPotion::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�̃R���C�_�[�ł����
	if (self == mpAttackCol)
	{
		CPlayer* player = dynamic_cast<CPlayer*>(other->Owner());
		if (player)
		{
			// ���łɍU���͂��㏸���Ă��Ȃ����
			if (!IsAttachHitAttackObj(player) && !mAttackUsed)
			{
				mAttackUsed = true;
				mpAttackCol->SetEnable(false);
				AddAttachHitAttackObj(player);
				UpdateGet();
			}
		}
	}

	if (self == mpFieldCol)
	{
		if (other->Layer() == ELayer::eField)
		{
			mIsGround = true;
			mMoveSpeed.Y(0.0f);
			Position(Position() + hit.adjust);
		}
		else if (other->Layer() == ELayer::eFieldWall)
		{
			Position(Position() + hit.adjust);
		}
	}
}

// �A�C�e�����������̏���
// �E�Ɉړ������̂�����
void CAttackPotion::UpdateGet()
{
	mMoveVector = CVector::zero;
	mMoveSpeed = CVector::zero;
	// ���x��ݒ�
	float moveSpeed = ATTACKPOTION_SPEED;

	CVector moveDirection(CVector::right);

	// mTargetDir �ɑ��x���|���Ĉړ��x�N�g���𓾂�
	mMoveVector = moveDirection * moveSpeed;

	// �ړ��ʂ��v�Z
	mMoveVector *= Time::DeltaTime();

	// ������kill���Ăԗ\��
}

// �X�V����
void CAttackPotion::Update()
{
	// �d��
	mMoveSpeed -= CVector(0.0f, GRAVITY, 0.0f);
	// ��]
	float rot = 1.0f;
	Rotate(0.0f, rot, 0.0f);

	// �^�C�����Z
	mElapsedTime += Time::DeltaTime();
	if (mElapsedTime >= 50.0f)
	{
		Kill();
	}

	// �ړ�
	Position(Position() + mMoveVector + mMoveSpeed * 60.0f * Time::DeltaTime());

	mIsGround = false;
}

// �`��
void CAttackPotion::Render()
{
	mpAttackPotion->SetColor(mColor);
	mpAttackPotion->Render(Matrix());
}