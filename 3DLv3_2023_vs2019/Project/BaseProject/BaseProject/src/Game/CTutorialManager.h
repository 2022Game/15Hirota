#ifndef CTUTORIALMANAGER_H
#define CTUTORIALMANAGER_H

#include "CTask.h"
#include <list>

class CTutorialUI;

// �摜�̕\�������߂�N���X
class CTutorialManager : public CTask
{
public:
	// �C���X�^���X���擾
	static CTutorialManager* Instance();

	// �摜��\�����������ǂ���������
	bool IsEndImage();

	// �R���X�g���N�^
	CTutorialManager();
	// �f�X�g���N�^
	~CTutorialManager();

private:
	// �C���X�^���X
	static CTutorialManager* mpInstance;

	// �S�Ċl��������C�x���g���������郊�X�g
	std::list<CTutorialUI*> mBlueMedals;

	// �\���t���O
	bool mIsEnd;
};
#endif