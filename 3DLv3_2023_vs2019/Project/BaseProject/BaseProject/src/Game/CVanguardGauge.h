#ifndef CVANGUARDGAUGE_H
#define CVANGUARDGAUGE_H
#include "CUIBase.h"
#include "CVector.h"
class CImage;
class CImage;

class CVanguardGauge :public CUIBase
{
private:
	CImage* mpFrameImage;		// �g�摜
	CImage* mpBarImage;			// �o�[�摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
	float mScale;				// �Q�[�W�̃X�P�[���l
public:
	// �R���X�g���N�^
	CVanguardGauge();
	// �f�X�g���N�^
	~CVanguardGauge();

	// �t���[�����폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

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