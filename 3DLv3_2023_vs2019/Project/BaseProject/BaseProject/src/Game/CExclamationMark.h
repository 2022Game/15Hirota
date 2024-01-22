#ifndef CEXCLAMATIONMARK_H
#define CEXCLAMATIONMARK_H
class CImage;

#include "CUIBase.h"
#include "CVector.h"

// �r�b�N���}�[�N�N���X
class CExclamationMark : public CUIBase
{
public:
	CExclamationMark();
	~CExclamationMark();

	// �r�b�N���}�[�N���폜
	void Kill() override;

	// �\�����邩�ǂ����ݒ�
	void SetShow(bool isShow) override;

	// ���S�ʒu��ݒ�
	void SetCeneterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldpos);

	// �X�V����
	void Update();

private:
	// �r�b�N���}�[�N�摜
	CImage* mpExclamationMark;
	// ���S�ʒu�̊���
	CVector2 mCenterRatio;
	// �r�b�N���}�[�N�̃X�P�[���l
	float mScale;
};
#endif