#ifndef CSIGNBOARDUI_H
#define CSIGNBOARDUI_H

#include "CUIBase.h"
#include "CVector.h"
class CImage;

class CSignboardUI : public CUIBase
{
public:
	// �R���X�g���N�^
	CSignboardUI();
	// �f�X�g���N�^
	~CSignboardUI();

	void Kill() override;

	void SetCenterRatio(const CVector2& ratio);

	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();

private:
	CImage* mpCSiUI;	// U�L�[�q���g�摜
	CVector2 mCenterRatio;	// ���S�ʒu�̊���
	float mScale;	// �摜�̃X�P�[���l
};
#endif