#ifndef CTITLEMENU_H
#define CTITLEMENU_H

#include "CTask.h"
#include <vector>
class CImage;

// �^�C�g����ʑI�����j���[
class CTitleMenu : public CTask
{
public:
	// �R���X�g���N�^
	CTitleMenu();
	// �f�X�g���N�^
	~CTitleMenu();

	// �J��
	void Open();
	// ����
	void Close();

	void HandleMouseInput();

	bool IsOpened() const;
	
	// �ǂ̃��j���[�ɂ��邩
	void Decide(int select);

	void Update() override;
	void Render() override;

private:
	CImage* mpTitleMenu;
	std::vector<CImage*> mTitleMenuItems;
	CImage* mpTitleMenuFrame;
	int mSelectIndex;
	bool mIsOpened;
};
#endif