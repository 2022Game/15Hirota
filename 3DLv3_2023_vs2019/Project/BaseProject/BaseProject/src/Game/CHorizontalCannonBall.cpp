#include "CHorizontalCannonBall.h"

// �d��
#define GRAVITY 0.0625f

// �R���X�g���N�^
CHorizontalCannonBall::CHorizontalCannonBall(const CVector& pos, const CVector& dir,
	float speed, float distance)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
	, mVerticalSpeed(0.0f)
{
	Position(pos);
	Scale(1.2f, 1.2f, 1.2f);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// ��C�̒e���f��
	mpCannonBall = CResourceManager::Get<CModel>("CannonBall");

	// ��C�̒e�̃R���C�_�[
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		1.7f
	);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CHorizontalCannonBall::~CHorizontalCannonBall()
{
	SAFE_DELETE(mpSpherer);
}

// �X�V����
void CHorizontalCannonBall::Update()
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
	float moveSpeed = mMoveSpeed * Time::DeltaTime();
	if (abs(moveSpeed) > remain)
	{
		moveSpeed = remain * (moveSpeed < 0.0f ? -1.0f : 1.0f);
	}

	// �o�E���X���ʂ̃p�����[�^
	static float bounceTime = 0.0f;         // �o�E���X���ʂ̎���
	const float bounceSpeed = 17.0f;         // ���˕Ԃ�̑���
	const float bounceHeight = 0.5f;        // �ő�o�E���X�̍���

	// ��������
	bounceTime += Time::DeltaTime() * bounceSpeed;

	// �V����Y�ʒu���v�Z
	float bounceOffset = sinf(bounceTime) * bounceHeight;

	// �e�ۂ̈ʒu���X�V
	Position(Position() + VectorZ() * moveSpeed + CVector(0.0f, bounceOffset, 0.0f));

	// ���݂̔򋗗����X�V
	mCurrentFlyingDistance += abs(moveSpeed);
}

// �`�揈��
void CHorizontalCannonBall::Render()
{
	mpCannonBall->SetColor(mColor);
	mpCannonBall->Render(Matrix());
}