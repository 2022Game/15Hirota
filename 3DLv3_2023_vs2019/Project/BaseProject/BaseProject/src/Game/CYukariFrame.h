#ifndef CYUKARIFRAME_H
#define CYUKARIFRAME_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

class CYukariFrame : public CUIBase
{
private:
	CImage* mpFrameImage;
	CVector2 mCenterRatio;
	float mScale;
	bool mIsShow;

public:
	// �R���X�g���N�^
	CYukariFrame();
	// �f�X�g���N�^
	~CYukariFrame();

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