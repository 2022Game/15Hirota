#ifndef CTUTORIALUI_H
#define CTUTORIALUI_H

#include "CTask.h"
#include "CVector.h"

class CFont;
class CImage;

// �`���[�g���A��UI
class CTutorialUI : public CTask
{
public:
	// �R���X�g���N�^
	CTutorialUI();
	// �f�X�g���N�^
	~CTutorialUI();

	// �J��
	void Open();
	// ����
	void Close();
	// �J���Ă��邩�ǂ���
	bool IsOpened() const;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �ŏ��̉摜
	CImage* mpCurrentImage;
	// �`���[�g���A���摜
	std::vector<CImage*> mTutorialItems;
	// ���E�̉摜�̏����̔���
	bool mIsChangeImage;
	// �J���Ă��邩�ǂ����̃t���O
	bool mIsOpened;
	// �摜��ύX���Ă��邩�ǂ����̃t���O
	bool mIsTransitioning;
	// �؂�ւ��v������
	float mElapsedTime;
};
#endif