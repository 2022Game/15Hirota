#include "CTutorialManager.h"

// �C���X�^���X
CTutorialManager* CTutorialManager::mpInstance = nullptr;

CTutorialManager* CTutorialManager::Instance()
{
	// �C���X�^���X��������΁A�V������������
	if (mpInstance == nullptr)
	{
		mpInstance = new CTutorialManager();
	}
	return mpInstance;
}

// �R���X�g���N�^
CTutorialManager::CTutorialManager()
	: CTask(ETaskPriority::eEvent, 0, ETaskPauseType::eGame, false, true)
	, mIsEnd(false)
{
}

// �f�X�g���N�^
CTutorialManager::~CTutorialManager()
{
	//SAFE_DELETE(mpInstance);
	SAFE_DELETE_ARRAY(mpInstance);
}

bool CTutorialManager::IsEndImage()
{
	return mIsEnd;
}