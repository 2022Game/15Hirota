#include "CObjectBase.h"
#include "CCollider.h"
#include "Maths.h"

// �R���X�g���N�^
CObjectBase::CObjectBase(ETag tag, ETaskPriority prio, int sortOrder, ETaskPauseType pause)
	: CTask(prio, sortOrder, pause)
	, mTag(tag)
	, mIsEnableCol(true)
	, mColor(CColor::white)
{
}

// �f�X�g���N�^
CObjectBase::~CObjectBase()
{
}

// �I�u�W�F�N�g�^�O���擾
ETag CObjectBase::Tag() const
{
	return mTag;
}

// �Փ˔�����s�����ݒ�
void CObjectBase::SetEnableCol(bool isEnable)
{
	mIsEnableCol = isEnable;
}

// �Փ˔�����s�����ǂ���
bool CObjectBase::IsEnableCol() const
{
	return mIsEnableCol && IsEnable();
}

// �J���[��ݒ�
void CObjectBase::SetColor(const CColor& color)
{
	mColor = color;
}

// �J���[���擾
const CColor& CObjectBase::GetColor() const
{
	return mColor;
}

// �A���t�@�l�ݒ�
void CObjectBase::SetAlpha(float alpha)
{
	mColor.A(Math::Clamp01(alpha));
}

// �A���t�@�l�擾
float CObjectBase::GetAlpha() const
{
	return mColor.A();
}

// �Փˏ���
void CObjectBase::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
{
}