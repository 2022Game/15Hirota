#include "CCannonBall.h"

// �d��
#define GRAVITY 0.0625f
// �d��
//#define GRAVITY 9.81f

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
	Scale(2.0f, 2.0f, 2.0f);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// ��C�̒e���f��
	mpCannonBall = CResourceManager::Get<CModel>("CannonBall");

	// ��C�̒e�̃R���C�_�[
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		2.5f
	);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
	//mpSpherer->Position(0.0f, 1.5f, -5.5f);
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
}

// �`�揈��
void CCannonBall::Render()
{
	mpCannonBall->SetColor(mColor);
	mpCannonBall->Render(Matrix());
}