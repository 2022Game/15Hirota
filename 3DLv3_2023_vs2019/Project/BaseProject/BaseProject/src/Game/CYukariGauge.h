#ifndef CYUKARIGAUGE_H
#define CYUKARIGAUGE_H
#include "CUIBase.h"
#include "CBillBoardImage.h"
#include "CObjectBase.h"
class CBillBoardImage;

class CYukariGauge :public CUIBase

{
private:
	CBillBoardImage* mpBarImage;	// �o�[�摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
public:
	// �R���X�g���N�^
	CYukariGauge();
	// �f�X�g���N�^
	~CYukariGauge();

	//void Setup(const CVector& pos, const CVector& dir);

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