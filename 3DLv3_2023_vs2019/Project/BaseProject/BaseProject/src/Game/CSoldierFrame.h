#ifndef CSOLDIERFRAME_H
#define CSOLDIERFRAME_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

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

	// ���S�ʒu�̊�����ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldPos);

	// �X�V����
	void Update();

};

#endif