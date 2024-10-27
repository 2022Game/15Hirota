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
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CSoldier.h"

CGameManager* CGameManager::spInstance = nullptr;

// �R���X�g���N�^
CGameManager::CGameManager()
	: mStageNo(0)
	, mState(EGameState::eReady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mElapsedStageTime(0.0f)
	, mResultSetUp(false)
{
}

// �f�X�g���N�^
CGameManager::~CGameManager()
{
	spInstance = nullptr;
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

// ���Z�b�g
void CGameManager::Reset()
{
	Instance()->ChangeState(EGameState::eReset);
}
//
//// �^�C�g���J�n
//void CGameManager::TitleStart()
//{
//	//// ������ԂłȂ���΁A�Q�[���J�n�͂��Ȃ�
//	if (GameState() != EGameState::eReady) return;
//	
//	// �^�C�g���J�n
//	Instance()->ChangeState(EGameState::eTitle);
//}

// �Q�[���J�n
void CGameManager::GameStart()
{
	// ������ԂłȂ���΁A�Q�[���J�n�͂��Ȃ�
	//if (GameState() != EGameState::eTitle) return;
	if (GameState() != EGameState::eReady) return;

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

// �Q�[���N���A
void CGameManager::GameClear()
{
	Instance()->ChangeState(EGameState::eGameClear);
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

// �X�e�[�W4
void CGameManager::Stage4()
{
	Instance()->ChangeState(EGameState::eStage4);
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
//
//void CGameManager::UpdateTitle()
//{
//
//}

// �Q�[�����̍X�V����
void CGameManager::UpdateGame()
{
	CPlayer* player = CPlayer::Instance();

	if (player != nullptr)
	{
		if (player->IsStage1Clear() && !mResultSetUp)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime > 1.5f)
			{
				mElapsedTime = 0.0f;
				mResultSetUp = true;
				ChangeState(EGameState::eResult);
			}
		}
		else if (player->IsStage2Clear() && !mResultSetUp)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime > 1.5f)
			{
				mElapsedTime = 0.0f;
				mResultSetUp = true;
				ChangeState(EGameState::eResult);
			}
		}
		/*else if (player->IsStage3Clear() && !mResultSetUp)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime > 1.5f)
			{
				mElapsedTime = 0.0f;
				mResultSetUp = true;
				ChangeState(EGameState::eResult);
			}
		}*/
		else if (player->IsDeath() && !mResultSetUp)
		{
			mElapsedTime += Time::DeltaTime();
			if (mElapsedTime > 1.5f)
			{
				mElapsedTime = 0.0f;
				mResultSetUp = true;
				ChangeState(EGameState::eResult);
			}
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
	// �X�e�[�W���N���A������A�X�e�[�W�I���X�e�[�W�Ɉڍs
	int stageNo = 0;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	mResultSetUp = false;

	// �X�e�[�W�̓ǂݍ��݂��I���΁A���U���g��\��
	ChangeState(EGameState::eGame);
}

// �X�e�[�W1�̍X�V����
void CGameManager::UpdateStage1()
{
	int stageNo = 1;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	ScoreReset();
	CStageManager::LoadStage(mStageNo);

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 2.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W2�̍X�V����
void CGameManager::UpdateStage2()
{
	int stageNo = 2;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	ScoreReset();

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 7.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W3�̍X�V����
void CGameManager::UpdateStage3()
{
	int stageNo = 3;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	ScoreReset();

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 14.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W4�̍X�V����
void CGameManager::UpdateStage4()
{
	int stageNo = 4;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	ScoreReset();

	mElapsedStageTime += Time::DeltaTime();
	if (mElapsedStageTime > 15.0f)
	{
		ChangeState(EGameState::eGame);
	}
}

// �X�e�[�W���s
void CGameManager::UpdateStageOver()
{
	int stageNo = 0;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	mResultSetUp = false;
	ScoreReset();

	ChangeState(EGameState::eGame);
}

// �Q�[���N���A���̍X�V����
void CGameManager::UpdateGameClear()
{
	CSceneManager::Instance()->LoadScene(EScene::eStuffedRoll);
}

// �Q�[���I�[�o�[���̍X�V����
void CGameManager::UpdateGameOver()
{
	int stageNo = 0;
	if (mStageNo != stageNo)
	{
		CStageManager::LoadStage(stageNo);
		mStageNo = stageNo;
	}

	mResultSetUp = false;
	ScoreReset();
	ChangeState(EGameState::eGame);
}

// ���U���g���̍X�V����
void CGameManager::UpdateResult()
{
	// �Q�[���V�[�����Ń��U���g�������s��
}

// CGameManager�Ƀ��Z�b�g
void CGameManager::UpdateReset()
{
	mStageNo = 0;
	mStateStep = 0;
	mElapsedTime = 0.0f;
	mElapsedStageTime = 0.0f;
	mResultSetUp = false;
}

// �X�R�A����������
void CGameManager::ScoreReset()
{
	//CSoldier
	CVanguard::SetScore(0);
	CBlueMedal::SetScore(0);
	CMeat1::SetScore(0);
	CMeat2::SetScore(0);
	CMeat3::SetScore(0);
}

// �X�V
void CGameManager::Update()
{
	// ���݂̏�Ԃɍ��킹���X�V�������s��
	switch (mState)
	{
		// ������
	case EGameState::eReady:
		UpdateReady();
		break;
		// ���Z�b�g
	case EGameState::eReset:
		UpdateReset();
		break;
	//	// �^�C�g����
	//case EGameState::eTitle:
	//	UpdateTitle();
	//	break;
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
		// �X�e�[�W4
	case EGameState::eStage4:
		UpdateStage4();
		break;
	}
}