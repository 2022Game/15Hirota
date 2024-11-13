#include "CHorizontalCannonBall.h"
#include "CStageManager.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CInput.h"

// �d��
#define GRAVITY 0.0625f
// ��������
#define FALLTIME 2.0f
// �����X�s�[�h
#define FALLSPEED 1.0f

// �R���X�g���N�^
CHorizontalCannonBall::CHorizontalCannonBall(const CVector& pos, const CVector& dir,
	float speed, float distance)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mState(EState::eIdle)
	, mStateStep(0)
	, mJumpedElapsedTime(0.0f)
	, mIsFall(false)
	, mIsCollisionPlayer(false)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
	, mVerticalSpeed(0.0f)
	, mFallTime(0.0f)
	, mBounceTime(0.0f)
{
	Position(pos);
	Scale(1.2f, 1.2f, 1.2f);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// ��C�̒e���f��
	mpCannonBall = CResourceManager::Get<CModel>("CannonBall");

	// ��C�̒e�̏�R���C�_�[
	CModel* CannonCol = CResourceManager::Get<CModel>("CannonUpCol");
	mpCannonCol = new CColliderMesh(this, ELayer::eField, CannonCol, true);

	// ��C�̒e�̃R���C�_�[
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		1.7f
	);
	mpSpherer->Position(0.0f, -0.5f, 0.0f);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CHorizontalCannonBall::~CHorizontalCannonBall()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpSpherer);
	SAFE_DELETE(mpCannonCol);
}

// �Փˏ���
void CHorizontalCannonBall::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
	CObjectBase* owner = other->Owner();
	if (owner == nullptr) return;

	// ���]���������߂��x�N�g���Ə�����̃x�N�g���̓���(�p�x)�����߂�
	float dot = CVector::Dot(-hit.adjust.Normalized(), CVector::up);
	// ��ɏ�����Ɣ��f���邽�߂�cos�֐��ɓn�����p�x�����߂�
	float cosAngle = cosf(Math::DegreeToRadian(10.0f));
	// ���߂��p�x���w�肵���p�x�͈͓̔��ł���΁A
	if (dot >= cosAngle)
	{
		if (mJumpedElapsedTime <= 0.2f)
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				mIsFall = true;
				mpCannonCol->SetEnable(false);
				mpSpherer->SetEnable(false);
				player->UpdateHighJumpingStart();
				ChangeState(EState::eFall);
			}
		}
		else
		{
			CPlayer* player = dynamic_cast<CPlayer*>(owner);
			if (player)
			{
				mIsFall = true;
				mpCannonCol->SetEnable(false);
				mpSpherer->SetEnable(false);
				player->UpdateJumpingStart();
				ChangeState(EState::eFall);
			}
		}
		mIsCollisionPlayer = true;
	}
}

// ��Ԃ�؂�ւ���
void CHorizontalCannonBall::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
}

// �ʏ���
void CHorizontalCannonBall::UpdateIdle()
{
	if (IsKill()) return;

	// �o�E���X���ʂ̃p�����[�^
	const float bounceSpeed = 10.0f;         // ���˕Ԃ�̑���
	const float bounceHeight = 0.5f;        // �ő�o�E���X�̍���

	// �c��򋗗���0�Ȃ�΁A�e�ۍ폜
	float remain = mFlyingDistance - mCurrentFlyingDistance;
	if (remain <= 0.0f)
	{
		Kill();
		return;
	}

	// �ړ����x���v�Z
	// �ړ����x���c��̔򋗗����傫���ꍇ�́A
	// �c��̔򋗗����ړ����x�Ƃ���
	float moveSpeed = mMoveSpeed * Time::DeltaTime();
	if (abs(moveSpeed) > remain)
	{
		moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
	}

	// ��������
	mBounceTime += Time::DeltaTime() * bounceSpeed;

	if (!mIsFall)
	{

		// �V����Y�ʒu���v�Z
		float bounceOffset = sinf(mBounceTime) * bounceHeight;

		// �e�ۂ̈ʒu���X�V
		Position(Position() + VectorZ() * moveSpeed + CVector(0.0f, bounceOffset, 0.0f));

		// ���݂̔򋗗����X�V
		mCurrentFlyingDistance += abs(moveSpeed);

		CDebugPrint::Print("bounceOffset:%f\n", bounceOffset);
	}
	CDebugPrint::Print("bounceTime:%f\n", mBounceTime);
	CDebugPrint::Print("bounceSpeed:%f\n", bounceSpeed);
	CDebugPrint::Print("bounceHeight:%f\n", bounceHeight);
}

// �������
void CHorizontalCannonBall::UpdateFall()
{
	if (IsKill()) return;

	// �e�ۂ̈ʒu���X�V
	Position(Position() + CVector(0.0f, -FALLSPEED, 0.0f));

	if (mFallTime <= FALLTIME)
	{
		mFallTime += Time::DeltaTime();
	}
	else
	{
		Kill();
		return;
	}
}

// �X�V����
void CHorizontalCannonBall::Update()
{
	if (CInput::PushKey(VK_SPACE))
	{
		mJumpedElapsedTime = 0.0f;
	}
	else
	{
		mJumpedElapsedTime += Time::DeltaTime();
	}

	// ���݂̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// ����Ă�����
	case EState::eFall:
		UpdateFall();
		break;

	}
	// �Փ˃t���O��������
	mIsCollisionPlayer = false;
}

// �`�揈��
void CHorizontalCannonBall::Render()
{
	mpCannonBall->SetColor(mColor);
	mpCannonBall->Render(Matrix());
}