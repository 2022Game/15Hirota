#ifndef CUIGAUGE_H
#define CUIGAUGE_H
#include "CUIBase.h"
class CImage;

class CUIGauge :public CUIBase
{
private:
	CImage* mpFrameImage;		// �g�摜
	CImage* mpBarImage;			// �o�[�摜
	CImage* mpDecreaseBarImage;	// �����摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
	int mPreviousValue;
	float mElapsedTime;
	bool mGauge;
	bool mDamaged;
	bool mStartDamaged;
	
public:
	// �R���X�g���N�^
	CUIGauge();
	// �f�X�g���N�^
	~CUIGauge();

	// �t���[�����폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// �ő�l��ݒ�
	void SetMaxValue(int value);
	// ���ݒn��ݒ�
	void SetValue(int value);

	// �o�[�̕\���ʒu�̊�����ݒ�
	// (HP�ł���΁A�c��HP���ő�HP�Ɣ�ׂĉ��p�[�Z���g�c���Ă��邩��ݒ�)
	void SetPor(float per);

	// �X�V����
	void Update();

};
#endif