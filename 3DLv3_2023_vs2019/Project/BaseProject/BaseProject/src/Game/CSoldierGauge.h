#ifndef CSOLDIERGAUGE_H
#define CSOLDIERGAUGE_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

class CSoldierGauge :public CUIBase
{
private:
	CImage* mpBarImage;			// �o�[�摜

	int mMaxValue;				// �ő�l
	int mValue;					// ���ݒl
	CVector2 mCenterRatio;		// ���S�ʒu�̊���
	float mScale;				// �Q�[�W�̃X�P�[���l
	bool mIsShow;				// �Q�[�W��\�����邩�ǂ���
public:
	// �R���X�g���N�^
	CSoldierGauge();
	// �f�X�g���N�^
	~CSoldierGauge();

	// �Q�[�W���폜
	void Kill() override;

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