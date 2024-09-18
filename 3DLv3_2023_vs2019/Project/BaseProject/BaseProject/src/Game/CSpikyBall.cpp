#include "CSpikyBall.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "CTrailEffect.h"
#include <Test/Primitive.h>

// �d��
#define GRAVITY 0.0625f

CSpikyBall::CSpikyBall(const CVector& pos, const CVector& dir,
	float speed, float distance)
	: mMoveSpeedY(0.0f)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
	, mHasLaunched(false)
	, mMoveSpeedXZ(CVector::zero)
{
	Position(pos);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	mpSpikyBallModel = CResourceManager::Get<CModel>("SpikyBall");

	// �O�Ղ̃G�t�F�N�g���쐬
	mpTrailEffect = new CTrailEffect
	(
		ETag::eWeapon,	// �I�u�W�F�N�g�^�O
		this,
		nullptr,
		CVector(0.0f, 0.0f, 0.0f),
		0.01f,			// �X�V�Ԋu�i���ԁj
		30.0f,			// �X�V�Ԋu�i�����j// �ύX����(30.0f)
		3.0f,			// �J�n���̋O�Ղ̕�
		0.0f,			// �I�����̋O�Ղ̕�
		0.0625f			// �\������
	);
	mpTrailEffect->SetTexture("Laser");
	mpTrailEffect->SetColor(CColor(1.0f, 1.0f, 1.0f, 0.6f));

	// �U������p�̃R���C�_�[���쐬
	mpAttackCol = new CColliderSphere
	(
		this, ELayer::eAttackCol,
		5.0f
	);
	// �U������p�̃R���C�_�[�ƏՓ˔�����s��
	// ���C���[�ƃ^�O��ݒ�
	mpAttackCol->SetCollisionLayers({ ELayer::eDamageCol });
	mpAttackCol->SetCollisionTags({ ETag::eEnemy });

	// �ŏ��͍U������p�̃R���C�_�[���I�t�ɂ��Ă���
	mpAttackCol->SetEnable(true);

	//SetAlpha(0.0f);
}

CSpikyBall::~CSpikyBall()
{
	mpTrailEffect->SetOwner(nullptr);
	// �R���C�_�[��j��
	SAFE_DELETE(mpAttackCol);
}

// �Փˏ���
void CSpikyBall::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	// �Փ˂��������̃R���C�_�[���U������p�R���C�_�[�ł����
	if (self == mpAttackCol)
	{
		// �L�����̃|�C���^�ɕϊ�
		CCharaBase* chara = dynamic_cast<CCharaBase*>(other->Owner());
		// ����̃R���C�_�[�̎����傪�L�����ł����
		if (chara != nullptr)
		{
			// ���łɍU���ς݂̃L�����łȂ����
			if (!IsAttackHitObj(chara))
			{
				//�@�_���[�W��^����
				chara->TakeDamage(2);

				// �U���ς݃��X�g�ɒǉ�
				AddAttackHitObj(chara);
			}
		}
	}
}

// �U���J�n
void CSpikyBall::AttackStart()
{
	// ���łɍU�����ł���΁A�ēx�J�n�����͎��s���Ȃ�
	if (mIsAttack) return;

	CWeapon::AttackStart();
	// �U�����n�܂�����A�U������p�̃R���C�_�[���I���ɂ���
	mpAttackCol->SetEnable(true);
}

// �U���I��
void CSpikyBall::AttackEnd()
{
	CWeapon::AttackEnd();
	// �U�����I���΁A�U������p�̃R���C�_�[���I�t�ɂ���
	mpAttackCol->SetEnable(false);
}

// ����̍s����擾
CMatrix CSpikyBall::Matrix() const
{
	const CMatrix* attachMtx = GetAttachMtx();
	// �����Ă��Ȃ��Ƃ��́A�������g�̍s���Ԃ�
	if (attachMtx == nullptr)
	{
		return CTransform::Matrix();
	}
	// �����Ă���Ƃ��́A�A�^�b�`���Ă���s���Ԃ�
	else
	{
		CMatrix sm;
		sm.Scale(8.5f, 8.5f, 8.5f);

		return sm * (*attachMtx);
	}
}

void CSpikyBall::SetSpeed(float newSpeed)
{
	mMoveSpeed = newSpeed;
}

void CSpikyBall::SetDistance(float newDistance)
{
	mFlyingDistance = newDistance;
}

// �X�V����
void CSpikyBall::Update()
{
	if (IsKill()) return;
	
	CPlayer* player = CPlayer::Instance();
	bool hand = player->IsSpikyBall();

	if (hand)
	{
		if (!mHasLaunched)
		{
			mHasLaunched = true;
			mMoveSpeedY = 1.4f;
		}
		else
		{

		}

		CDebugPrint::Print("has:%s\n", mHasLaunched ? "true" : "false");
		// �c��򋗗���0�Ȃ�΁A�e�ۍ폜
		float remain = mFlyingDistance - mCurrentFlyingDistance;
		if (remain <= 0.0f)
		{
			Kill();
			return;
		}

		mMoveSpeedY -= GRAVITY;

		// �ړ����x���v�Z
		// �ړ����x���c��̔򋗗����傫���ꍇ�́A
		// �c��̔򋗗����ړ����x�Ƃ���
		float moveSpeed = mMoveSpeed * Time::DeltaTime();
		if (abs(moveSpeed) > remain)
		{
			moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
		}

		// ���������̈ړ�
		Position(Position() + player->VectorZ() * moveSpeed);

		CVector moveSpeedXZ = mMoveSpeedXZ + CVector(0.0f, mMoveSpeedY, 0.0f * Time::DeltaTime());

		// �ړ�
		Position(Position() + moveSpeedXZ * 60.0f * Time::DeltaTime());

		// ���݂̔򋗗����X�V
		mCurrentFlyingDistance += abs(moveSpeed);

		//CDebugPrint::Print("mMoveSpeedY:%f\n", mMoveSpeedY);
	}
	else
	{

	}
	/*CDebugPrint::Print("distance:%f\n", mFlyingDistance);
	CDebugPrint::Print("speed:%f\n", mMoveSpeed);*/
}

// �`�揈��
void CSpikyBall::Render()
{
	mpSpikyBallModel->SetColor(mColor);
	mpSpikyBallModel->Render(Matrix());
	Primitive::DrawSphere(Matrix(), 0.5f, mColor);
}