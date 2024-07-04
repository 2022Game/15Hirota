#ifndef CBUTTON1UI_H
#define CBUTTON1UI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

class CButton1UI : public CUIBase
{
public:
	// �R���X�g���N�^
	CButton1UI();
	// �f�X�g���N�^
	~CButton1UI();

	void Kill() override;

	void SetCenterRatio(const CVector2& ratio);

	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();

private:
	CImage* mpUI;			// UI�摜
	CVector2 mCenterRatio;	// ���S�ʒu�̊���
	float mScale;			// �摜�̃X�P�[���l
};
#endif