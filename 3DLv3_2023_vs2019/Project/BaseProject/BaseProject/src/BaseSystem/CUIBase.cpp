#include "CUIBase.h"
#include "CImage.h"

CUIBase::CUIBase()
	: CTask(ETaskPriority::eUI)
	, mPosition(0.0f, 0.0f)
	, mSize(100.0f, 100.0f)
	, mColor(1.0, 1.0f, 1.0f)
{
}

CUIBase::~CUIBase()
{
}


//�\�����W��ݒ�iCVector2�Łj
void CUIBase::SetPos(const CVector2& pos)
{
	mPosition = pos;
}

//�\�����W��ݒ�
void CUIBase::SetPos(const float& x, const float& y)
{
	SetPos(CVector2(x, y));
}

//�\�����W���擾
const CVector2& CUIBase::GetPos() const
{
	return mPosition;
}

//�\���T�C�Y��ݒ�iCVector2�Łj
void CUIBase::SetSize(const CVector2& size)
{
	mSize = size;
}

//�\���T�C�Y��ݒ�
void CUIBase::SetSize(const float& x, const float& y)
{
	SetSize(CVector2(x, y));
}

//�\���T�C�Y���擾
const CVector2& CUIBase::GetSize() const
{
	return mSize;
}

void CUIBase::SetColor(const CColor& color)
{
	mColor = color;
}

//�\���J���[��ݒ�i�A���t�@�l�L��Łj
void CUIBase::SetColor(const float& r, const float& g, const float& b, const float& a)
{
	mColor.Set(r, g, b, a);
}

//�\���J���[��ݒ�
void CUIBase::SetColor(const float& r, const float& g, const float& b)
{
	mColor.Set(r, g, b);
}

//�\���J���[���擾
const CColor& CUIBase::GetColor() const
{
	return mColor;
}

//�A���t�@�l��ݒ�
void CUIBase::SetAlpha(const float& alpha)
{
	mColor.A(alpha);
}

//�A���t�@�l���擾
const float& CUIBase::GetAlpha() const
{
	return mColor.A();
}
