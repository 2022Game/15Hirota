#include "CSpikyBall.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "CPlayer.h"
#include "CTrailEffect.h"
#include <Test/Primitive.h>
#include "CPointLine.h"

// �d��
#define GRAVITY 0.0625f

CSpikyBall::CSpikyBall(const CVector& pos, const CVector& dir,
	float speed, float distance, float initialVelocityY)
	: mMoveSpeed(speed)
	, mFlyingDistance(distance)
	, mMoveSpeedY(initialVelocityY)
	, mMoveSpeedXZ(CVector::zero)
	, mCurrentFlyingDistance(0.0f)
	, ForwardVectorZ(CVector::zero)
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

// ���݂̃X�s�[�h�ݒ�
void CSpikyBall::SetSpeed(float newSpeed)
{
	mMoveSpeed = newSpeed;
}

// ���݂̔򋗗��ݒ�
void CSpikyBall::SetDistance(float newDistance)
{
	mFlyingDistance = newDistance;
}

// ���݂̈ʒu�ݒ�
void CSpikyBall::SetPosition(CVector pos)
{
	mPosition = pos;
}

// ���݂̈ʒu��Ԃ�
CVector CSpikyBall::GetPosition() const
{
	return mPosition;
}

void CSpikyBall::PlayerVectorZ(const CPlayer& player)
{
	ForwardVectorZ = player.VectorZ();
}

// �X�V����
void CSpikyBall::Update()
{
	if (IsKill()) return;
	
	CPlayer* player = CPlayer::Instance();
	bool hand = player->IsSpikyBall();

	if (hand)
	{
		// �c��򋗗���0�Ȃ�΁A�Ƃ��폜
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
		Position(Position() + ForwardVectorZ * moveSpeed);
		// ���������̈ړ�
		CVector moveSpeedXZ = mMoveSpeedXZ + CVector(0.0f, mMoveSpeedY, 0.0f);
		// �ړ�
		Position(Position() + moveSpeedXZ * 60.0f * Time::DeltaTime());


		//// ���������̈ړ�
		//Position(Position() + player->VectorZ() * moveSpeed);

		//// ���������̈ړ�
		//CVector VelocityY(0.0f, mMoveSpeedY, 0.0f);
		//// ���������̈ړ�
		//CVector moveSpeedXZ = mMoveSpeedXZ * Time::DeltaTime();

		//// �ړ�
		//Position(Position() + CVector(moveSpeedXZ.X(), VelocityY.Y(), moveSpeedXZ.Z()));

		printf("mPosition:%f %f %f\n", mPosition.X(), mPosition.Y(), mPosition.Z());

		// ���݂̔򋗗����X�V
		mCurrentFlyingDistance += abs(moveSpeed);
	}
	else
	{

	}
	//CDebugPrint::Print("mPosition:%f %f %f\n", mPosition.X(), mPosition.Y(), mPosition.Z());
	/*CDebugPrint::Print("distance:%f\n", mFlyingDistance);
	CDebugPrint::Print("speed:%f\n", mMoveSpeed);*/
	//float speed = player->GetSpikyBallSpeed();
	//CDebugPrint::Print("speed%f\n", speed);
	//CDebugPrint::Print("mMoveSpeed:%f\n", mMoveSpeed);
}

// �\�����̃p�X��ݒ�
void CSpikyBall::DrawProjectilePath(const CVector& startPosition, const CVector& initialVelocityXZ, float initialVelocityY, float gravity, float timeStep, int numPoints, const CColor& color, float lineWidth)
{
	// �e�̏����l�_
	CVector currentPosition = startPosition;
	// XZ���ʂł̌��݂̑��x
	CVector velocityXZ = initialVelocityXZ;
	// ���������ł̌��݂̑��x
	float velocityY = initialVelocityY;

	std::vector<CVector> pathPoints;

	float t = 0.0f;

	for (int i = 0; i < numPoints; ++i) 
	{
		// ���݂̈ʒu�����X�g�ɒǉ�
		pathPoints.push_back(currentPosition);

		// ���Ԃ�i�߂�
		t += timeStep;

		// ���������̈ʒu�̍X�V
		CVector displacementXZ = velocityXZ * timeStep;
		currentPosition += displacementXZ;

		// Y���W�̍X�V
		float currentY = startPosition.Y() + velocityY * t - 0.5f * gravity * t * t;
		currentPosition = CVector(currentPosition.X(), currentY, currentPosition.Z());

		// ���������̑��x���X�V
		velocityY -= gravity * timeStep;
	}

	// ����`��
	for (size_t i = 0; i < pathPoints.size() - 1; ++i) {
		Primitive::DrawLine(pathPoints[i], pathPoints[i + 1], color, lineWidth);
	}
}

// �e���̗\�����C����`�悷��֐�
void CSpikyBall::RenderPredictionLine()
{
	CPlayer* player = CPlayer::Instance();
	// �ʒu���Ⴄ�̂Ō�ŕύX
	CVector startPosition = player->Position() + CVector(0.0f, 18.0f, 0.0f) + player->VectorZ() * 5.0f;

	// �v���C���[���瑬�x���擾
	float speed = player->GetSpikyBallSpeed();

	// �v���C���[�̑O�����x�N�g�����擾���Đ��K��
	CVector forwardDirection = player->VectorZ();
	if (forwardDirection.Length() != 0.0f) 
	{
		forwardDirection.Normalize();
	}

	// �����x���v���C���[�̑O�����x�N�g���Ɋ�Â��Đݒ�
	// �K�X�ύX
	CVector initialVelocityXZ = forwardDirection * speed * 0.032f;
	//printf("velocityXZ:%f %f %f\n", initialVelocityXZ.X(), initialVelocityXZ.Y(), initialVelocityXZ.Z());

	// ���������̏����x
	float initialVelocityY = mMoveSpeedY;
	// �d��
	float gravity = GRAVITY;

	// �p�X�̐F
	CColor lineColor(1.0f, 0.0f, 0.0f, 0.5f);
	// ���C���̑���
	float lineWidth = 6.0f;

	// �p�X��`��
	float stepInterval = 8.0f;
	int numSteps = 15;
	DrawProjectilePath(startPosition, initialVelocityXZ, initialVelocityY, gravity, stepInterval, numSteps, lineColor, lineWidth);
}

// �`�揈��
void CSpikyBall::Render()
{
	CPlayer* player = CPlayer::Instance();
	// �Ƃ����o�����Ă��邩
	bool spik = player->IsSpikyBallAppearance();
	// �Ƃ��{�[���̗\������`�悷�邩�ǂ����𔻒f
	if (spik) 
	{
		RenderPredictionLine();
	}

	// �Ƃ��{�[���̕`��
	mpSpikyBallModel->SetColor(mColor);
	mpSpikyBallModel->Render(Matrix());

	// �Ƃ��{�[���̃X�t�B�A�`��
	Primitive::DrawSphere(Matrix(), 0.5f, mColor);
}