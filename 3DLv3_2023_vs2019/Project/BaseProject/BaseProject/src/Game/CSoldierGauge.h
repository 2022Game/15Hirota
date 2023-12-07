#ifndef CSOLDIERGAUGE_H
#define CSOLDIERGAUGE_H
class CImage;

#include "CUIBase.h"

class CSoldierGauge :public CUIBase
{
private:
	CImage* mpBarImage;			// �o�[�摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
public:
	// �R���X�g���N�^
	CSoldierGauge();
	// �f�X�g���N�^
	~CSoldierGauge();

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