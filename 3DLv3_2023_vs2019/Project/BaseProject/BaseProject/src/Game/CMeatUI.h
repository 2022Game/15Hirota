#ifndef CMEATUI_H
#define CMEATUI_H

#include "CTask.h"
#include <vector>

class CPlayer;
class CImage;

// �X�e�[�W�̓�UI�N���X
class CMeatUI : public CTask
{
public:
	CMeatUI();
	~CMeatUI();

	void Open();
	void Close();

	bool IsOpened() const;

	void Update() override;
	void Render() override;

private:
	// ���擾���̓��̉摜
	std::vector<CImage*> mUnacquired;
	// �擾���̓��̉摜
	std::vector<CImage*> mAcquisition;
	bool mIsOpened;
};
#endif