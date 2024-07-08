#ifndef CCLIMBUI_H
#define CCLIMBUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

class CClimbUI : public CUIBase
{
public:
	// �R���X�g���N�^
	CClimbUI();
	// �f�X�g���N�^
	~CClimbUI();

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