#ifndef CYUKARIGAUGE_H
#define CYUKARIGAUGE_H

#include "CUIBase.h"
#include "CVector.h"
class CImage;

class CYukariGauge :public CUIBase

{
private:
	CImage* mpBarImage;			// �o�[�摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
	CVector2 mCenterRatio;		// ���S�ʒu�̊���
	float mScale;				// �Q�[�W�̃X�P�[���l
public:
	// �R���X�g���N�^
	CYukariGauge();
	// �f�X�g���N�^
	~CYukariGauge();

	// �Q�[�W���폜
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

	// ���S�ʒu�̊�����ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();
};
#endif