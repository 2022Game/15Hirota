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

public:
	// �R���X�g���N�^
	CSoldierFrame();
	// �f�X�g���N�^
	~CSoldierFrame();

	// �t���[�����폜
	void Kill() override;

	// ���S�ʒu�̊�����ݒ�
	void SetCenterRatio(const CVector2& ratio);

	// �X�V����
	void Update();

};

#endif