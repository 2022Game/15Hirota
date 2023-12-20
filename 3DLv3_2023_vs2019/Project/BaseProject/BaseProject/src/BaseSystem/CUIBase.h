#pragma once
#include "CTask.h"
#include "CVector.h"
#include "CColor.h"

class CUIBase : public CTask
{
public:
	CUIBase(ETaskPriority prio = ETaskPriority::eUI, int sortOrder = 0,
		ETaskPauseType pause = ETaskPauseType::eGame,
		bool dontDelete = false, bool addTaskList = true);
	virtual ~CUIBase();	

	//�\�����W��ݒ�iCVector2�Łj
	virtual void SetPos(const CVector2& pos);
	//�\�����W��ݒ�
	virtual void SetPos(const float& x, const float& y);
	//�\�����W���擾
	const CVector2& GetPos() const;

	//�\���T�C�Y��ݒ�iCVector2�Łj
	virtual void SetSize(const CVector2& size);
	//�\���T�C�Y��ݒ�
	virtual void SetSize(const float& x, const float& y);
	//�\���T�C�Y���擾
	const CVector2& GetSize() const;

	//���S�ʒu��ݒ�iCVector2�Łj
	virtual void SetCenter(const CVector2& center);
	//���S�ʒu��ݒ�
	virtual void SetCenter(const float x, const float y);
	//���S�ʒu���擾
	const CVector2& GetCenter() const;


	//�\���J���[��ݒ�iCColor�Łj
	virtual void SetColor(const CColor& color);
	//�\���J���[��ݒ�i�A���t�@�l�L��Łj
	virtual void SetColor(const float& r, const float& g, const float& b, const float& a);
	//�\���J���[��ݒ�
	virtual void SetColor(const float& r, const float& g, const float& b);
	//�\���J���[���擾
	const CColor& GetColor() const;

	//�A���t�@�l��ݒ�
	virtual void SetAlpha(const float& alpha);
	//�A���t�@�l���擾
	float GetAlpha() const;

protected:
	CVector2 mPosition;	// �\���ʒu
	CVector2 mSize;		// �\���T�C�Y
	CVector2 mCenter;	// ���S�ʒu
	CColor mColor;		// �\���J���[
private:
};