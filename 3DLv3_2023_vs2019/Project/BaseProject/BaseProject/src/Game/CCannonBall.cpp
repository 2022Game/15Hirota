#include "CCannonBall.h"

// �d��
#define GRAVITY 0.0625f

// �R���X�g���N�^
CCannonBall::CCannonBall(const CVector& pos, const CVector& dir,
	float speed, float distance, float verticalSpeed)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mMoveSpeed(speed)
	, mDirection(dir)
	, mFlyingDistance(distance)
	, mVerticalSpeed(verticalSpeed)
	, mCurrentFlyingDistance(0.0f)
{
	Position(pos);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// ��C�̒e�̃R���C�_�[
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		5.0f
	);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CCannonBall::~CCannonBall()
{
	SAFE_DELETE(mpSpherer);
}

// �����x��ݒ�
void CCannonBall::SetVerticalSpeed(float speed) 
{
	mVerticalSpeed = speed;
}

// �X�V����
void CCannonBall::Update()
{
	if (IsKill()) return;

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
	float moveSpeed = mMoveSpeed;
	if (abs(moveSpeed) > remain)
	{
		moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
	}

	mVerticalSpeed -= GRAVITY; // �d�͂����Z

	// �e�ۂ̈ʒu���X�V
	Position(Position() + mDirection * moveSpeed + CVector(0.0f, mVerticalSpeed, 0.0f));

	// ���݂̔򋗗����X�V
	mCurrentFlyingDistance += abs(moveSpeed);
	CDebugPrint::Print("mCurrentFlyingDistance:%f\n", mCurrentFlyingDistance);
	CDebugPrint::Print("mFlyingDistance:%f\n", mFlyingDistance);
}

// �`�揈��
void CCannonBall::Render()
{

}