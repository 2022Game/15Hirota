#ifndef CSTAMINAGAUGE_H
#define CSTAMINAGAUGE_H
#include "CUIBase.h"
class CImage;

class CStaminaGauge :public CUIBase
{
private:
	CImage* mpStaminaImage;		// �X�^�~�i�摜

	int mMaxSutaminaValue;		// �X�^�~�i�ő�l
	int mSutaminaValue;			// �X�^�~�i���ݒl
public:
	CStaminaGauge();
	~CStaminaGauge();

	// �t���[�����폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// �ő�l��ݒ�(�X�^�~�i)
	void SetSutaminaMaxValue(int value_st);
	// ���ݒn��ݒ�(�X�^�~�i)
	void SetSutaminaValue(int value_st);

	// �o�[�̕\���ʒu�̊�����ݒ�
	// (HP�ł���΁A�c��HP���ő�HP�Ɣ�ׂĉ��p�[�Z���g�c���Ă��邩��ݒ�)
	void SetPor(float per);

	void Update();
};
#endif