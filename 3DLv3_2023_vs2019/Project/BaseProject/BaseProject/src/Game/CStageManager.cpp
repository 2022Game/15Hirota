#include "CStageManager.h"
#include "CStageBase.h"
#include "CStage1.h"
#include "CStage2.h"

CStageManager* CStageManager::spInstance = nullptr;
CStageBase* CStageManager::spCurrentStage = nullptr;

// �R���X�g���N�^
CStageManager::CStageManager()
{
	spInstance = this;
}

// �f�X�g���N�^
CStageManager::~CStageManager()
{
	spInstance = nullptr;

	// �X�e�[�W���ǂݍ��܂�Ă�����
	UnloadStage();
}

// �X�e�[�W�ǂݍ���
void CStageManager::LoadStage(int no)
{
	// ���łɃX�e�[�W���ǂݍ��܂�Ă�����A�j��
	UnloadStage();

	// �X�e�[�W�ԍ��ɍ��킹�ăX�e�[�W��ǂݍ���
	switch (no)
	{
	case 0: spCurrentStage = new CStage1(); break;
	case 1: spCurrentStage = new CStage2(); break;
	default:spCurrentStage = new CStage1(); break;
	}
	// �X�e�[�W���쐬�o������A�X�e�[�W�ǂݍ���
	if (spCurrentStage != nullptr)
	{
		spCurrentStage->Load();
	}
}

// ���݂̃X�e�[�W�j��
void CStageManager::UnloadStage()
{
	if (spCurrentStage == nullptr) return;
	spCurrentStage->Unload();
	SAFE_DELETE(spCurrentStage);
}

// �쐬�����^�X�N�����X�g�ɒǉ�
void CStageManager::AddTask(CTask* task)
{
	if (spCurrentStage == nullptr) return;
	spCurrentStage->AddTask(task);
}

// �쐬�����^�X�N�����X�g�����菜��
void CStageManager::RemoveTask(CTask* task)
{
	if (spCurrentStage == nullptr) return;
	spCurrentStage->RemoveTask(task);
}