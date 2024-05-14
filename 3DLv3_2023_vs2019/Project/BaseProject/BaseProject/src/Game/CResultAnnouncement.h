#ifndef CRESULTANNOUNCEMENT_H
#define CRESULTANNOUNCEMENT_H

#include "CTask.h"
#include <vector>
class CImage;

// ���U���g��ʕ\��
// ���U���g��ʑI�����j���[
class CResultAnnouncement : public CTask
{
public:
	// �R���X�g���N�^
	CResultAnnouncement();
	// �f�X�g���N�^
	~CResultAnnouncement();

	//�C���X�^���X�̃|�C���^�̎擾
	static CResultAnnouncement* Instance();

	// �J��
	void Open();
	// ����
	void Close();

	// �}�E�X�J�[�\�������m����
	void HandleMouseInput();

	bool IsOpened() const;
	bool IsResultOpened() const;

	// �ǂ̃��j���[�ɂ��邩
	void Decide(int select);

	void Update() override;
	void Render() override;

private:
	static CResultAnnouncement* spInstance;
	// ���U���g�̉摜
	CImage* mpResultsMenu;
	std::vector<CImage*> mResultsMenuItems;

	enum Result
	{
		A,
		B,
		C,
	};
	std::vector<std::pair<Result, CImage*>> mABCItems;
	int mSelectIndex;
	bool mIsOpened;
	bool mResultOpened;
	float mElapsedTime;
	float mAlpha;
};
#endif