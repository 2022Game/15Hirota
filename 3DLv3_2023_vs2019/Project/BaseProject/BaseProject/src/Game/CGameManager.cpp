#include "CGameManager.h"
#include "CStageManager.h"
#include "CSceneManager.h"
#include "CFade.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CResult.h"
#include "CInput.h"
#include "CPlayer.h"
#include "CVanguard.h"
#include "CBlueMedal.h"
#include "CResultAnnouncement.h"

CGameManager* CGameManager::spInstance = nullptr;

// �R���X�g���N�^
CGameManager::CGameManager()
	: mStageNo(0)
	, mState(EGameState::eRaady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedStageTime(0.0f)
	, mResultSetUp(false)
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

// �X�e�[�W1
void CGameManager::Stage1()
{
	Instance()->ChangeState(EGameState::eStage1);
}

// �X�e�[�W2
void CGameManager::Stage2()
{
	Instance()->ChangeState(EGameState::eStage2);
}

// �X�e�[�W3
void CGameManager::Stage3()
{
	Instance()->ChangeState(EGameState::eStage3);
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
	CPlayer* player = CPlayer::Instance();

	if (player->IsStage1Clear() && !mResultSetUp)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 1.5f)
		{
			mElapsedTime = 0.0f;
			mResultSetUp = true;
			Instance()->ChangeState(EGameState::eResult);
		}
	}
	else if (player->IsStage2Clear() && !mResultSetUp)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 1.5f) 
		{
			mElapsedTime = 0.0f;
			mResultSetUp = true;
			Instance()->ChangeState(EGameState::eResult);
		}
	}
	else if (player->IsStage3Clear() && !mResultSetUp)
	{
		mElapsedTime += Time::DeltaTime();
		if (mElapsedTime > 1.5f)
		{
			mElapsedTime = 0.0f;
			mResultSetUp = true;
			Instance()->ChangeState(EGameState::eResult);
		}
	}
	//CDebugPrint::Print("mEleapsedTime:%f\n", mElapsedTime);
	CResult::Instance()->Update();
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
	mResultSetUp = false;
	//CSceneManager::Instance()->LoadScene(EScene::eClear);
	CStageManager::LoadStage(mStageNo);

	// �X�e�[�W�̓ǂݍ��݂��I���΁A���U���g��\��
	ChangeState(EGameState::eGame);
}

// �X�e�[�W1�̍X�V����
void CGameManager::UpdateStage1()
{
	mStageNo = 1;
	CVanguard::SetScore(0);
	CBlueMedal::SetScore(0);
	CStageManager::LoadStage(mStageNo);

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 1.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W2�̍X�V����
void CGameManager::UpdateStage2()
{
	mStageNo = 2;
	CVanguard::SetScore(0);
	CBlueMedal::SetScore(0);
	CStageManager::LoadStage(mStageNo);

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 4.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W3�̍X�V����
void CGameManager::UpdateStage3()
{
	mStageNo = 3;
	CVanguard::SetScore(0);
	CBlueMedal::SetScore(0);
	CStageManager::LoadStage(mStageNo);
	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 13.5f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W���s
void CGameManager::UpdateStageOver()
{
	mStageNo = 0;
	CVanguard::SetScore(0);
	CBlueMedal::SetScore(0);
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
	// �Q�[���V�[�����Ń��U���g�������s��
}

// �X�V
void CGameManager::Update()
{
	//CDebugPrint::Print("mResultSetUp:%s\n", mResultSetUp ? "true" : "false");
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
		// �X�e�[�W1
	case EGameState::eStage1:
		UpdateStage1();
		break;
		// �X�e�[�W2
	case EGameState::eStage2:
		UpdateStage2();
		break;
		// �X�e�[�W3
	case EGameState::eStage3:
		UpdateStage3();
		break;
	}
}