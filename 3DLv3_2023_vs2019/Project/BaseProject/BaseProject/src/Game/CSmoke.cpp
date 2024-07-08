#include "CSmoke.h"
#include "Easing.h"

// ���̃X�P�[���l�̍ő�l
#define SMOKE_SCALE 3.0f
// ���̃X�P�[���l���ő�l�ɂȂ�܂ł̎���
#define SMOKE_SCALE_ANIM_TIME 2.0f

// �A�j���[�V������1�R�}�\������
#define ANIM_TIME 0.0625f
// ���̃G�t�F�N�g�̃A�j���[�V�����f�[�^
//TexAnimData CSmoke::msAnimData = TexAnimData(8, 8, false, 64, ANIM_TIME);
TexAnimData CSmoke::msAnimData = TexAnimData(2, 8, false, 16, ANIM_TIME);

// �R���X�g���N�^
CSmoke::CSmoke(ETag tag,ETaskPriority prio)
	: CBillBoardImage("Effect/Smoke(2_8_GIMP).png", tag, ETaskPauseType::eGame)
	, mMoveSpeed(CVector::zero)
	, mElapsedTime(0.0f)
	, mIsDeath(false)
{
	SetAnimData(&msAnimData);
	SetColor(CColor(1.0f, 1.0f, 1.0f, 0.5f));
	SetPriority(ETaskPriority::eSmokeEffecit);
}

// �f�X�g���N�^
CSmoke::~CSmoke()
{

}

//// �e�p�����[�^��ݒ�
//void CSmoke::Setup(const CVector& pos, const CVector& dir, float speed)
//{
//	Position(pos);
//	mMoveSpeed = dir.Normalized() * speed;
//}

// �폜�t���O�������Ă��邩�ǂ���
bool CSmoke::IsDeath() const
{
	return mIsDeath;
}

// �J���[��ݒ�
void CSmoke::SetColor(const CColor& color)
{
	mMaterial.Diffuse()[0] = color.R();
	mMaterial.Diffuse()[1] = color.G();
	mMaterial.Diffuse()[2] = color.B();
	mMaterial.Diffuse()[3] = color.A();
	CObjectBase::SetColor(color);
}

// �u�����h�^�C�v��ݒ�
void CSmoke::SetBlendType(EBlend type)
{
	mMaterial.SetBlendType(type);
}

//// �Փˏ���
//void CSmoke::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
//{
//	if (other->Layer() == ELayer::eField)
//	{
//		/*float length = mMoveSpeed.Length();
//		CVector n = hit.adjust.Normalized();
//		float d = CVector::Dot(n, mMoveSpeed);
//		mMoveSpeed = (mMoveSpeed - n * d).Normalized() * length;
//		Position(Position() + hit.adjust * hit.weight);*/
//
//		// �����n�ʂɓ��������Ƃ��A���x���[���ɂ���
//		mMoveSpeed = CVector::zero;
//
//		// �Փ�
//		Position(Position() + hit.adjust * hit.weight);
//	}
//}

// �X�V
void CSmoke::Update()
{
	// ���N���X�̍X�V����
	CBillBoardImage::Update();

	// ���̃G�t�F�N�g���ړ�
	/*CVector move = mMoveSpeed * Time::DeltaTime();
	Position(Position() + move);*/


	// �X�P�[���ύX���Ԃ��o�߂��Ă��Ȃ�
	if (mElapsedTime < SMOKE_SCALE_ANIM_TIME)
	{
		// �o�ߎ��Ԃɍ��킹�āA���X�ɉ���傫������
		float per = mElapsedTime / SMOKE_SCALE_ANIM_TIME;
		if (per < 1.0f)
		{
			float scale = Easing::QuadOut(per, 0.7f, 0.0f, 0.7f);
			Scale(CVector::one * scale * SMOKE_SCALE);
		}
		else
		{
			Scale(CVector::one * SMOKE_SCALE);
		}

		mElapsedTime += Time::DeltaTime();
	}
	// �ړ����Ԃ��o�߂�����A�폜����
	else
	{
		Scale(CVector::one * SMOKE_SCALE);
	}

	// �A�j���[�V�������I�������A�폜�t���O�𗧂Ă�
	if (IsEndAnim())
	{
		mIsDeath = true;
	}
}