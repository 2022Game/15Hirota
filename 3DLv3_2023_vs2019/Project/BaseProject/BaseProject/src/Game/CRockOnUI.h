#ifndef CROCKONUI_H
#define CROCKONUI_H

class CImage;

#include "CUIBase.h"
#include "CVector.h"

// ���b�N�I���摜�N���X
class CRockOnUI : public CUIBase
{
public:
	// �R���X�g���N�^
	CRockOnUI(std::string path);
	// �f�X�g���N�^
	~CRockOnUI();

	// ���b�N�I���摜�폜
	void Kill() override;

	// �\�����邩�ǂ�����ݒ�
	void SetShow(bool isShow) override;

	// ���S�ʒu��ݒ�
	void SetCeneterRatio(const CVector2& ratio);

	// ���[���h���W��ݒ�
	void SetWorldPos(const CVector& worldpos);

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// ���b�N�I���\�摜&���b�N�I���摜
	CImage* mpCanRockOn;
	// ���S�ʒu�̊���
	CVector2 mCenterRatio;
};
#endif