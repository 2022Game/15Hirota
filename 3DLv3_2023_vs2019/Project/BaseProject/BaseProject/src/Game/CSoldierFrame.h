#ifndef CSOLDIERFRAME_H
#define CSOLDIERFRAME_H

#include "CUIBase.h"
#include "CVector.h"
class CImage;

class CSoldierFrame :public CUIBase
{
private:
	CImage* mpFrameImage;		// �g�摜
	CVector2 mCenterRatio;		// ���S�ʒu�̊���
	float mScale;				// �Q�[�W�̃X�P�[���l
	bool mIsShow;				// �Q�[�W��\�����邩�ǂ���

public:
	// �R���X�g���N�^
	CSoldierFrame();
	// �f�X�g���N�^
	~CSoldierFrame();

	// �t���[�����폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// ���S�ʒu�̊�����ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();

};

#endif