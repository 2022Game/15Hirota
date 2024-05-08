#include "CGameManager.h"
#include "CStageManager.h"
#include "CSceneManager.h"
#include "CScore.h"
#include "CStageTime.h"
#include "CResult.h"
#include "CInput.h"
#include "CResultAnnouncement.h"

CGameManager* CGameManager::spInstance = nullptr;

// コンストラクタ
CGameManager::CGameManager()
	: mStageNo(0)
	, mState(EGameState::eRaady)
	, mStateStep(0)
	, mElapsedTime(0.0f)
	, mpResult(nullptr)
{
	mpResult = new CResultAnnouncement();
}

// デストラクタ
CGameManager::~CGameManager()
{
	mpResult->Kill();
}

// インスタンス取得
CGameManager* CGameManager::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CGameManager();
	}
	return spInstance;
}

// ゲーム開始
void CGameManager::GameStart()
{
	// 準備状態でなければ、ゲーム開始はしない
	if (GameState() != EGameState::eRaady) return;

	// 最初のステージを読み込み
	CStageManager::LoadStage(Instance()->mStageNo);

	// ゲーム開始
	Instance()->ChangeState(EGameState::eGame);
}

// ゲーム再開
void CGameManager::GameRestart()
{
	Instance()->ChangeState(EGameState::eRestart);
}

// ステージクリア
void CGameManager::StageClear()
{
	Instance()->ChangeState(EGameState::eStageClear);
}

// ステージ失敗
void CGameManager::StageOver()
{
	Instance()->ChangeState(EGameState::eStageOver);
}

// ゲームオーバー
void CGameManager::GameOver()
{
	Instance()->ChangeState(EGameState::eGameOver);
}

// リザルト
void CGameManager::Result()
{
	Instance()->ChangeState(EGameState::eResult);
}

// 現在のゲームの状態を取得
EGameState CGameManager::GameState()
{
	return Instance()->mState;
}

// 現在のステージ番号を取得
int CGameManager::StageNo()
{
	return Instance()->mStageNo;
}

// 現在のゲームの状態を切り替え
void CGameManager::ChangeState(EGameState state)
{
	if (mState == state) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// 準備状態の更新処理
void CGameManager::UpdateReady()
{

}

// ゲーム中の更新処理
void CGameManager::UpdateGame()
{
	
}

// ゲーム再開の更新処理
void CGameManager::UpdateRestart()
{
	ChangeState(EGameState::eGame);
}

// ステージクリア時の更新処理
void CGameManager::UpdateStageClear()
{
	// ステージをクリアしたら、次のステージを読み込み
	mStageNo = 0;
	//CSceneManager::Instance()->LoadScene(EScene::eClear);
	CStageManager::LoadStage(mStageNo);

	// ステージの読み込みが終われば、リザルトを表示
	ChangeState(EGameState::eResult);
}

// ステージ失敗
void CGameManager::UpdateStageOver()
{
	mStageNo = 0;
	CStageManager::LoadStage(mStageNo);

	ChangeState(EGameState::eGame);
}

// ゲームクリア時の更新処理
void CGameManager::UpdateGameClear()
{

}

// ゲームオーバー時の更新処理
void CGameManager::UpdateGameOver()
{

}

// リザルト時の更新処理
void CGameManager::UpdateResult()
{
	CResult::Instance()->SetTimeAndScore(CStageTime::Instance(), CScore::Instance());
	mpResult->Open();
}

// 更新
void CGameManager::Update()
{
	// 現在の状態に合わせた更新処理を行う
	switch (mState)
	{
		// 準備中
	case EGameState::eRaady:
		UpdateReady();
		break;
		// ゲーム中
	case EGameState::eGame:
		UpdateGame();
		break;
		// ゲーム再開
	case EGameState::eRestart:
		UpdateRestart();
		break;
		// ステージクリア
	case EGameState::eStageClear:
		UpdateStageClear();
		break;
		// ステージ失敗
	case EGameState::eStageOver:
		UpdateStageOver();
		break;
		// ゲームクリア
	case EGameState::eGameClear:
		UpdateGameClear();
		break;
		// ゲームオーバー
	case EGameState::eGameOver:
		UpdateGameOver();
		break;
		// リザルト
	case EGameState::eResult:
		UpdateResult();
		break;
	}
}