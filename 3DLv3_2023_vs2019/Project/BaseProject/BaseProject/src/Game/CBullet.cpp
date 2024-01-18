#include "CBullet.h"
#include "CTrailEffect.h"
#include <Test/Primitive.h>

// �R���X�g���N�^
CBullet::CBullet(const CVector& pos, const CVector& dir,
	float speed, float distance)
	: CObjectBase(ETag::eBullet, ETaskPriority::eDefault, 0, ETaskPauseType::eGame)
	, mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mCurrentFlyingDistance(0.0f)
{
	Position(pos);
	Rotation(CQuaternion::LookRotation(dir, CVector::up));

	// �O�Ղ̃G�t�F�N�g���쐬
	mpTrailEffect = new CTrailEffect
	(
		ETag::eBullet,	// �I�u�W�F�N�g�^�O
		this,
		nullptr,
		CVector(0.0f, 0.0f, 0.0f),
		0.01f,			// �X�V�Ԋu�i���ԁj
		10.0f,			// �X�V�Ԋu�i�����j// �ύX����(30.0f)
		2.0f,			// �J�n���̋O�Ղ̕�
		0.0f,			// �I�����̋O�Ղ̕�
		0.0625f			// �\������
	);
	mpTrailEffect->SetTexture("Laser");
	mpTrailEffect->SetColor(CColor(1.0f, 0.0f, 0.0f, 1.0f));

	// �e�ۂ̃R���C�_�[
	mpSpherer = new CColliderSphere
	(
		this, ELayer::eBulletCol,
		2.0f
	);
	mpSpherer->SetCollisionLayers({ ELayer::eDamageCol });
	mpSpherer->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CBullet::~CBullet()
{
	mpTrailEffect->SetOwner(nullptr);
	SAFE_DELETE(mpSpherer);
}

// �X�V
void CBullet::Update()
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

	// �e�ۂ𐳖ʕ����Ɉړ�
	Position(Position() + VectorZ() * moveSpeed);
	// ���݂̔򋗗����X�V
	mCurrentFlyingDistance += abs(moveSpeed);
}

// �`��
void CBullet::Render()
{
	Primitive::DrawSphere(Matrix(), 0.1f, mColor);
}