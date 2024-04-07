#include "CFlame.h"
#include "Easing.h"

// ���̃X�P�[���l�̍ő�l
#define FLAME_SCALE 3.0f
// ���̃X�P�[���l���ő�l�ɂȂ�܂ł̎���
#define FLAME_SCALE_ANIM_TIME 3.0f

// �A�j���[�V������1�R�}�\������
#define ANIM_TIME 0.0625f
// ���̃G�t�F�N�g�̃A�j���[�V�����f�[�^
TexAnimData CFlame::msAnimData = TexAnimData(8, 8, false, 40, ANIM_TIME);

// �R���X�g���N�^
CFlame::CFlame(ETag tag)
	: CBillBoardImage("Effect/flame.png", tag, ETaskPauseType::eGame)
	, mMoveSpeed(CVector::zero)
	, mElapsedTime(0.0f)
	, mIsDeath(false)
{
	SetAnimData(&msAnimData);
}

// �f�X�g���N�^
CFlame::~CFlame()
{
}

// �e�p�����[�^��ݒ�
void CFlame::Setup(const CVector& pos, const CVector& dir, float speed)
{
	Position(pos);
	mMoveSpeed = dir.Normalized() * speed;
}

// �폜�t���O�������Ă��邩�ǂ���
bool CFlame::IsDeath() const
{
	return mIsDeath;
}

// �J���[��ݒ�
void CFlame::SetColor(const CColor& color)
{
	mMaterial.Diffuse()[0] = color.R();
	mMaterial.Diffuse()[1] = color.G();
	mMaterial.Diffuse()[2] = color.B();
	mMaterial.Diffuse()[3] = color.A();
	CObjectBase::SetColor(color);
}

// �u�����h�^�C�v��ݒ�
void CFlame::SetBlendType(EBlend type)
{
	mMaterial.SetBlendType(type);
}

// �X�V
void CFlame::Update()
{
	// ���N���X�̍X�V����
	CBillBoardImage::Update();

	// �X�P�[���ύX���Ԃ��o�߂��Ă��Ȃ�
	if (mElapsedTime < FLAME_SCALE_ANIM_TIME)
	{
		// ���̃G�t�F�N�g���ړ�
		CVector move = mMoveSpeed * Time::DeltaTime();
		Position(Position() + move);

		// �o�ߎ��Ԃɍ��킹�āA���X�ɉ���傫������
		float per = mElapsedTime / FLAME_SCALE_ANIM_TIME;
		if (per < 1.0f)
		{
			float scale = Easing::QuadOut(per, 1.0f, 0.0f, 1.0f);
			Scale(CVector::one * scale * FLAME_SCALE);
		}
		else
		{
			Scale(CVector::one * FLAME_SCALE);
		}

		mElapsedTime += Time::DeltaTime();
	}
	// �ړ����Ԃ��o�߂�����A�폜����
	else
	{
		Scale(CVector::one * FLAME_SCALE);
	}

	// �A�j���[�V�������I�������A�폜�t���O�𗧂Ă�
	if (IsEndAnim())
	{
		mIsDeath = true;
	}
}