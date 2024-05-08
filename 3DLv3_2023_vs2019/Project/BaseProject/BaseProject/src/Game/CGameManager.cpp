#include "CGameManager.h"
#include "CStageManager.h"
#include "CSceneManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CResult.h"
#include "CInput.h"
#include "CResultAnnouncement.h"

CGameManager* CGameManager::spInstance = nullptr;

// �R���X�g���N�^
CGameManager::CGameManager()
	: mStageNo(0)
	, mState(EGameState::eRaady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mpResult(nullptr)
{
	mpResult = new CResultAnnouncement();
}

// �f�X�g���N�^
CGameManager::~CGameManager()
{
	mpResult->Kill();
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

// �Q�[���ĊJ
void CGameManager::GameRestart()
{
	Instance()->ChangeState(EGameState::eRestart);
}

// �X�e�[�W�N���A
void CGameManager::StageClear()
{
	Instance()->ChangeState(EGameState::eStageClear);
}

// �X�e�[�W���s
void CGameManager::StageOver()
{
	Instance()->ChangeState(EGameState::eStageOver);
}

// �Q�[���I�[�o�[
void CGameManager::GameOver()
{
	Instance()->ChangeState(EGameState::eGameOver);
}

// ���U���g
void CGameManager::Result()
{
	Instance()->ChangeState(EGameState::eResult);
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

// �Q�[���ĊJ�̍X�V����
void CGameManager::UpdateRestart()
{
	ChangeState(EGameState::eGame);
}

// �X�e�[�W�N���A���̍X�V����
void CGameManager::UpdateStageClear()
{
	// �X�e�[�W���N���A������A���̃X�e�[�W��ǂݍ���
	mStageNo = 0;
	//CSceneManager::Instance()->LoadScene(EScene::eClear);
	CStageManager::LoadStage(mStageNo);

	// �X�e�[�W�̓ǂݍ��݂��I���΁A���U���g��\��
	ChangeState(EGameState::eResult);
}

// �X�e�[�W���s
void CGameManager::UpdateStageOver()
{
	mStageNo = 0;
	CStageManager::LoadStage(mStageNo);

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

// ���U���g���̍X�V����
void CGameManager::UpdateResult()
{
	CResult::Instance()->SetTimeAndScore(CStageTime::Instance(), CScore::Instance());
	mpResult->Open();
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
		// �Q�[���ĊJ
	case EGameState::eRestart:
		UpdateRestart();
		break;
		// �X�e�[�W�N���A
	case EGameState::eStageClear:
		UpdateStageClear();
		break;
		// �X�e�[�W���s
	case EGameState::eStageOver:
		UpdateStageOver();
		break;
		// �Q�[���N���A
	case EGameState::eGameClear:
		UpdateGameClear();
		break;
		// �Q�[���I�[�o�[
	case EGameState::eGameOver:
		UpdateGameOver();
		break;
		// ���U���g
	case EGameState::eResult:
		UpdateResult();
		break;
	}
}