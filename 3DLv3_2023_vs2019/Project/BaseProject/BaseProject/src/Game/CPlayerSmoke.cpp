#include "CPlayerSmoke.h"
#include "CSmoke.h"
#include "CInput.h"
#include "Maths.h"
#include "CPlayer.h"

// ���̔��ˊԊu����
#define THROW_INTERVAL 0.15f
// ���̔��˕����̃u����
#define FLAME_DIR_RAND 0.02f
// ���̈ړ����x
#define FLAME_MOVE_SPEED 75.0f
// ���̐F
#define FLAME_COLOR CColor(1.0f, 1.0f, 1.0f)

// �R���X�g���N�^
CPlayerSmoke::CPlayerSmoke(CObjectBase* owner, const CMatrix* attach,
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
CPlayerSmoke::~CPlayerSmoke()
{
	for (CSmoke* flame : mSmoke)
	{
		flame->Kill();
	}
}

// ���𔭎ˊJ�n
void CPlayerSmoke::Start()
{
	mIsThrowing = true;
	mElapsedTime = 0.0f;
}

// ���𔭎˒�~
void CPlayerSmoke::Stop()
{
	mIsThrowing = false;
}

// ���𔭎˂��Ă��邩�ǂ���
bool CPlayerSmoke::IsThrowing() const
{
	return mIsThrowing;
}

// ���ˎ��̃I�t�Z�b�g�ʒu��ݒ�
void CPlayerSmoke::SetThrowOffsetPos(const CVector& pos)
{
	mThrowOffsetPos = pos;
}

// ���ˎ��̃I�t�Z�b�g��]�l��ݒ�
void CPlayerSmoke::SetThrowOffsetRot(const CMatrix& rot)
{
	mThrowOffsetRot = rot;
}

// ���̔��ˈʒu���擾
CVector CPlayerSmoke::GetThrowPos() const
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
CVector CPlayerSmoke::GetThrowDir() const
{
	//// �A�^�b�`����s�񂪐ݒ肳��Ă���ꍇ�́A�s��̐��ʕ����x�N�g����Ԃ�
	//if (mpAttachMtx != nullptr)
	//{
	//	return mThrowOffsetRot * mpAttachMtx->VectorY();
	//}
	//// �����傪�ݒ肳��Ă���ꍇ�́A������̐��ʕ����x�N�g����Ԃ�
	//else if (mpOwner != nullptr)

	//{
	//	return mThrowOffsetRot * mpOwner->VectorY();
	//}

	return mThrowOffsetRot * CVector::zero;
}

// ���̃G�t�F�N�g���쐬
void CPlayerSmoke::CreateSmoke()
{
	// ���̃G�t�F�N�g���쐬
	CSmoke* smoke = new CSmoke(ETag::eSmoke);

	// ���ˈʒu���擾
	CVector pos = GetThrowPos(); // + CVector(0.0f, 10.0f, 0.0f);
	// ���˕������擾
	CVector dir = GetThrowDir(); // + CVector(0.0f, -1.0f, 0.0f);
	// ���˕����������_���Ńu����
	//dir.X(dir.X() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	//dir.Y(dir.Y() + Math::Rand(0.0f, 0.0f));
	//dir.Z(dir.Z() + Math::Rand(-FLAME_DIR_RAND, FLAME_DIR_RAND));
	dir.Normalize();
	// ���ˈʒu�A�����A�ړ����x��ݒ�
	smoke->Setup(pos, dir, FLAME_MOVE_SPEED);

	// ���̃J���[��ݒ�
	smoke->SetColor(FLAME_COLOR);
	// ���Z�u�����h�ɂ��āA�����������Ă���悤�Ɍ�����
	smoke->SetBlendType(EBlend::eAdd);

	// �쐬�������̃G�t�F�N�g�����X�g�ɒǉ�
	mSmoke.push_back(smoke);
}

// �X�V
void CPlayerSmoke::Update()
{
	// ���𔭎˂��Ă�����
	if (mIsThrowing)
	{
		// �o�ߎ��Ԃɉ����āA���̃G�t�F�N�g���쐬
		if (mElapsedTime >= THROW_INTERVAL)
		{
			CreateSmoke();
			mElapsedTime -= THROW_INTERVAL;
		}
		mElapsedTime += Time::DeltaTime();
	}

	// �����ς݂̉��̃G�t�F�N�g�̍폜����
	auto itr = mSmoke.begin();
	auto end = mSmoke.end();
	while (itr != end)
	{
		CSmoke* smoke = *itr;
		// �폜�t���O�������Ă�����A�폜
		if (smoke->IsDeath())
		{
			itr = mSmoke.erase(itr);
			smoke->Kill();
		}
		else
		{
			itr++;
		}
	}
}