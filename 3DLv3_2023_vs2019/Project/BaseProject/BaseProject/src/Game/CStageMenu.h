#ifndef CSTAGEMENU_H
#define CSTAGEMENU_H

#include "CTask.h"
#include <vector>
class CImage;

// �X�e�[�W�I�����j���[
class CStageMenu : public CTask
{
public:
	// �R���X�g���N�^
	CStageMenu();
	// �f�X�g���N�^
	~CStageMenu();

	// �J��
	void Open();
	// ����
	void Close();
	// �J���Ă��邩�ǂ���
	bool IsOpened() const;

	// �ǂ̃��j���[�ɂ��邩
	void Decide(int select);

	void Update() override;
	void Render() override;

private:
	CImage* mpStageMenu;
	std::vector<CImage*> mStageMenuItems;
	CImage* mpStageMenuFrame;
	int mSelectIndex;
	bool mIsOpened;
};
#endif