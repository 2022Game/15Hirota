#include "CGameManager.h"
#include "CStageManager.h"

CGameManager* CGameManager::spInstance = nullptr;

// �R���X�g���N�^
CGameManager::CGameManager()
	: mStageNo(0)
	, mState(EGameState::eRaady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
{

}

// �f�X�g���N�^
CGameManager::~CGameManager()
{

}

// �C���X�^���X�擾
CGameManager* CGameManager::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CGameManager();
	}
	return spInstance;
}

// �Q�[���J�n
void CGameManager::GameStart()
{
	// ������ԂłȂ���΁A�Q�[���J�n�͂��Ȃ�
	if (GameState() != EGameState::eRaady) return;

	// �ŏ��̃X�e�[�W��ǂݍ���
	CStageManager::LoadStage(Instance()->mStageNo);

	// �Q�[���J�n
	Instance()->ChangeState(EGameState::eGame);
}

// �X�e�[�W�N���A
void CGameManager::StageClear()
{
	Instance()->ChangeState(EGameState::eStageClear);
}

// �Q�[���I�[�o�[
void CGameManager::GameOver()
{
	Instance()->ChangeState(EGameState::eGameOver);
}

// ���݂̃Q�[���̏�Ԃ��擾
EGameState CGameManager::GameState()
{
	return Instance()->mState;
}

// ���݂̃X�e�[�W�ԍ����擾
int CGameManager::StageNo()
{
	return Instance()->mStageNo;
}

// ���݂̃Q�[���̏�Ԃ�؂�ւ�
void CGameManager::ChangeState(EGameState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// ������Ԃ̍X�V����
void CGameManager::UpdateReady()
{

}

// �Q�[�����̍X�V����
void CGameManager::UpdateGame()
{

}

// �X�e�[�W�N���A���̍X�V����
void CGameManager::UpdateStageClear()
{
	// �X�e�[�W���N���A������A���̃X�e�[�W��ǂݍ���
	mStageNo++;
	CStageManager::LoadStage(mStageNo);

	// �X�e�[�W�̓ǂݍ��݂��I���΁A�Q�[�����J�n
	ChangeState(EGameState::eGame);
}

// �Q�[���N���A���̍X�V����
void CGameManager::UpdateGameClear()
{

}

// �Q�[���I�[�o�[���̍X�V����
void CGameManager::UpdateGameOver()
{

}

// �X�V
void CGameManager::Update()
{
	// ���݂̏�Ԃɍ��킹���X�V�������s��
	switch (mState)
	{
		// ������
	case EGameState::eRaady:
		UpdateReady();
		break;
		// �Q�[����
	case EGameState::eGame:
		UpdateGame();
		break;
		// �X�e�[�W�N���A
	case EGameState::eStageClear:
		UpdateStageClear();
		break;
		// �Q�[���N���A
	case EGameState::eGameClear:
		UpdateGameClear();
		break;
		// �Q�[���I�[�o�[
	case EGameState::eGameOver:
		UpdateGameOver();
		break;
	}
}