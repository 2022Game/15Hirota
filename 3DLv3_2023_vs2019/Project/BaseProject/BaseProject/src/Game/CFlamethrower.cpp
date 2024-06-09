#include "CFlamethrower.h"
#include "CFlame.h"
#include "CInput.h"
#include "Maths.h"

// ���̔��ˊԊu����
#define THROW_INTERVAL 0.55f
// ���̔��˕����̃u����
#define FLAME_DIR_RAND 0.02f
// ���̈ړ����x
#define FLAME_MOVE_SPEED 75.0f
// ���̐F
#define FLAME_COLOR CColor(1.0f, 0.25f, 0.1f)

// �R���X�g���N�^
CFlamethrower::CFlamethrower(CObjectBase* owner, const CMatrix* attach,
	const CVector& offsetPos, const CMatrix& offsetRot)
	: mpOwner(owner)
	, mpAttachMtx(attach)
	, mThrowOffsetPos(offsetPos)
	, mThrowOffsetRot(offsetRot)
	, mElapsedTime(0.0f)
	, mIsThrowing(false)
{
}

// �f�X�g���N�^
CFlamethrower::~CFlamethrower()
{
	for (CFlame* flame : mFlames)
	{
		flame->Kill();
	}
}

// ���𔭎ˊJ�n
void CFlamethrower::Start()
{
	mIsThrowing = true;
	mElapsedTime = 0.0f;
}

// ���𔭎˒�~
void CFlamethrower::Stop()
{
	mIsThrowing = false;
}

// ���𔭎˂��Ă��邩�ǂ���
bool CFlamethrower::IsThrowing() const
{
	return mIsThrowing;
}

// ���ˎ��̃I�t�Z�b�g�ʒu��ݒ�
void CFlamethrower::SetThrowOffsetPos(const CVector& pos)
{
	mThrowOffsetPos = pos;
}

// ���ˎ��̃I�t�Z�b�g��]�l��ݒ�
void CFlamethrower::SetThrowOffsetRot(const CMatrix& rot)
{
	mThrowOffsetRot = rot;
}

// ���̔��ˈʒu���擾
CVector CFlamethrower::GetThrowPos() const
{
	// �A�^�b�`����s�񂪐ݒ肳��Ă���ꍇ�́A�s��̍��W��Ԃ�
	if (mpAttachMtx != nullptr)
	{
		CVector pos = mpAttachMtx->Position();
		pos += mpAttachMtx->VectorX().Normalized() * mThrowOffsetPos.X()
			+ mpAttachMtx->VectorY().Normalized() * mThrowOffsetPos.Y()
			+ mpAttachMtx->VectorZ().Normalized() * mThrowOffsetPos.Z();
		return pos;
	}
	// �����傪�ݒ肳��Ă���ꍇ�́A������̍��W��Ԃ�
	else if (mpOwner != nullptr)
	{
		return mpOwner->Position() + (mpOwner->Rotation() * mThrowOffsetPos);
	}

	return CVector::zero;
}

// ���̔��˕������擾
CVector CFlamethrower::GetThrowDir() const
{
	// �A�^�b�`����s�񂪐ݒ肳��Ă���ꍇ�́A�s��̐��ʕ����x�N�g����Ԃ�
	if (mpAttachMtx != nullptr)
	{
		return mThrowOffsetRot * mpAttachMtx->VectorZ();
	}
	// �����傪�ݒ肳��Ă���ꍇ�́A������̐��ʕ����x�N�g����Ԃ�
	else if (mpOwner != nullptr)
	{
		return mThrowOffsetRot * mpOwner->VectorZ();
	}

	return mThrowOffsetRot * CVector::forward;
}

// ���̃G�t�F�N�g���쐬
void CFlamethrower::CreateFlame()
{
	// ���̃G�t�F�N�g���쐬
	CFlame* flame = new CFlame(ETag::eFlame);

	// ���ˈʒu���擾
	CVector pos = GetThrowPos(); // + CVector(0.0f, 10.0f, 0.0f);
	// ���˕������擾
	CVector dir = GetThrowDir(); // + CVector(0.0f, -1.0f, 0.0f);
	// ���˕����������_���Ńu����
	dir.X(dir.X() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Y(dir.Y() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Z(dir.Z() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Normalize();
	// ���ˈʒu�A�����A�ړ����x��ݒ�
	flame->Setup(pos, dir, FLAME_MOVE_SPEED);

	// ���̃J���[��ݒ�
	flame->SetColor(FLAME_COLOR);
	// ���Z�u�����h�ɂ��āA�����������Ă���悤�Ɍ�����
	flame->SetBlendType(EBlend::eAdd);

	// �쐬�������̃G�t�F�N�g�����X�g�ɒǉ�
	mFlames.push_back(flame);
}

// �X�V
void CFlamethrower::Update()
{
	// ���𔭎˂��Ă�����
	if (mIsThrowing)
	{
		// �o�ߎ��Ԃɉ����āA���̃G�t�F�N�g���쐬
		if (mElapsedTime >= THROW_INTERVAL)
		{
			CreateFlame();
			mElapsedTime -= THROW_INTERVAL;
		}
		mElapsedTime += Time::DeltaTime();
	}

	// �����ς݂̉��̃G�t�F�N�g�̍폜����
	auto itr = mFlames.begin();
	auto end = mFlames.end();
	while (itr != end)
	{
		CFlame* flame = *itr;
		// �폜�t���O�������Ă�����A�폜
		if (flame->IsDeath())
		{
			itr = mFlames.erase(itr);
			flame->Kill();
		}
		else
		{
			itr++;
		}
	}
}