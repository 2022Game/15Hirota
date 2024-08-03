#ifndef CPICOCHANUI_H
#define CPICOCHANUI_H

#include "CUIBase.h"
#include "CVector.h"

class CImage;

class CPicoChanUI : public CUIBase
{
public:
	CPicoChanUI();
	~CPicoChanUI();

	// UI���폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// �ő�l��ݒ�
	void SetMaxValue(int value);
	// ���ݒn��ݒ�
	void SetValue(int value);

	// ���S�ʒu�̊�����ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();

private:
	CImage* mpFrameImage;		// �g�摜
	CImage* mpBarImage;			// �o�[�摜
	CImage* mpDecreaseBarImage;	// �����摜
	CVector2 mCenterRatio;		// ���S�ʒu�̊���
	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
	float mScale;				// �Q�[�W�̃X�P�[���l
	float mElapsedTime;
	bool mIsShow;				// �Q�[�W��\�����邩�ǂ���
	bool mGauge;
};
#endif