#include "CNumberFloorBase.h"
#include "Maths.h"
#include "CPlayer.h"
#include "CStageManager.h"

// ������̂ɂ����鎞��
#define FADE_TIME 4.0f
// ��������̑҂�����
#define WAIT_TIME 4.0f

// �R���X�g���N�^
CNumberFloorBase::CNumberFloorBase(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eRideableObject, ETaskPriority::eNumberFalling)
	, mState(EState::Idle)
	, mpModel(nullptr)
	, mpCollider(nullptr)
	, mStateStep(0)
	, mSwitchCount(0)
	, mFallingSwitch(0)
	, mFadeTime(0.0f)
	, mWaitTime(0.0f)
	, mElapsedTime(0.0f)
	, mMoveSpeed(0.0f, 0.0f, 0.0f)
	, mStartPos(CVector::zero)
	, mIsCollision(false)
	, mCase0End(false)
	, mCase1End(false)
{
	Position(pos);
	Scale(scale);
	Rotate(rot);
}

CNumberFloorBase::~CNumberFloorBase()
{
	SAFE_DELETE(mpCollider);
}

// �Փˏ���
void CNumberFloorBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
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
		// ���݂��ҋ@��Ԃł���΁A�t�F�[�h��Ԃ֐؂�ւ���
		if (mState == EState::Idle)
		{
			ChangeState(EState::Waiting);
		}
		mIsCollision = true;
	}
}

// ��Ԃ�؂�ւ���
void CNumberFloorBase::ChangeState(EState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	//mFallingSwitch = 0;
}

// ���̈ʒu�ɖ߂�ۂ̃��f���p�X�ݒ�
void CNumberFloorBase::SetModelPath(const std::string& path)
{
	mModelPath = path;
}

// �ҋ@��Ԃ̏���
void CNumberFloorBase::UpdateIdle()
{

}

// �҂���Ԃ̏���
void CNumberFloorBase::UpdateWaiting()
{

}

// ������Ԃ̏���
void CNumberFloorBase::UpdateFalling()
{
	switch (mFallingSwitch)
	{
		// �ԐF�œ_�ł�����
	case 0:
	{
		static const float time = 2.0f;
		if (mElapsedTime < time)
		{
			mElapsedTime += Time::DeltaTime();
			float red = 0.5f + 0.5f * sin(2.0f * M_PI * mElapsedTime);
			CColor color = CColor(red, 0.0f, 0.0f, 1.0f);
			SetColor(color);
		}
		else
		{
			mSwitchCount++;
			mElapsedTime = 0.0f;
			if (mSwitchCount == 2)
			{
				mFallingSwitch++;
			}
		}
	}
	break;
	// ����������
	case 1:
	{
		static const float fall = 10.0f;
		mMoveSpeed = CVector(0.0f, -fall * Time::DeltaTime(), 0.0f);
		Position(Position() + mMoveSpeed);
		if (Position().Y() <= mStartPos.Y() - 40.0f)
		{
			mpCollider->SetEnable(false);
			SetColor(CColor(0.0f, 0.0f, 0.0f, 0.0f));
			mFallingSwitch++;
		}
	}
	break;
	// ���̏�Ԃɖ߂�
	case 2:
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime >= 5.0f)
		{
			mSwitchCount = 0;
			mElapsedTime = 0;
			mFallingSwitch = 0;
			mCase0End = false;
			mCase1End = false;
			Position(mStartPos);
			mpCollider->SetEnable(true);
			SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
			mpModel = CResourceManager::Get<CModel>(mModelPath);
			ChangeState(EState::Idle);
		}
	}
	break;
	}
}

// �X�V����
void CNumberFloorBase::Update()
{
	// ���̏�Ԃɍ��킹�ď�����؂�ւ�
	switch (mState)
	{
		// �ҋ@���
	case EState::Idle:
		UpdateIdle();
		break;
		// �҂����
	case EState::Waiting:
		UpdateWaiting();
		break;
		// �������
	case EState::Falling:
		UpdateFalling();
		break;
	}
	// �Փ˃t���O��������
	mIsCollision = false;
}

// �`�揈��
void CNumberFloorBase::Render()
{
	if (mpModel != nullptr)
	{
		mpModel->SetColor(mColor);
		mpModel->Render(Matrix());
	}
}