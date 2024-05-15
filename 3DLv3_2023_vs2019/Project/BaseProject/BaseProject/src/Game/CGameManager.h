#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include "CTask.h"
class CResultAnnouncement;
class CResult;

//	ゲームの状態
enum class EGameState
{
	eRaady,			// 準備中
	eGame,			// ゲーム実行中
	eRestart,		// ゲーム再開
	eStageClear,	// ステージクリア
	eStageOver,		// ステージ失敗
	eResult,		// リザルト
	eGameClear,		// ゲームクリア
	eGameOver,		// ゲームオーバー

	eStage1,
	eStage2,
	eStage3,
};

//ゲームクラスを管理するクラス
class CGameManager : public CTask
{
public:
	// ゲーム開始
	static void GameStart();
	// ゲーム再開
	static void GameRestart();
	// ステージクリア
	static void StageClear();
	// ステージ失敗
	static void StageOver();
	// ゲームオーバー
	static void GameOver();
	// リザルト
	static void Result();

	static void Stage1();
	static void Stage2();
	static void Stage3();

	// 現在のゲームの状態を取得
	static EGameState GameState();
	// 現在のステージ番号
	static int StageNo();
	// ステージ番号の設定
	static void SetStageNo(int stageNo) {
		Instance()->mStageNo = stageNo;
	}
	
	// 更新処理
	void Update();

private:

	static CGameManager* Instance();
	// 現在のゲームの状態を切り替え
	void ChangeState(EGameState state);

	// コンストラクタ
	CGameManager();
	// デストラクタ
	~CGameManager();

	// 準備状態の更新処理
	void UpdateReady();
	// ゲーム中の更新処理
	void UpdateGame();
	// ゲーム再開更新処理
	void UpdateRestart();
	// ステージクリア時の更新処理
	void UpdateStageClear();
	// ステージ失敗
	void UpdateStageOver();
	// ゲームクリア時の更新処理
	void UpdateGameClear();
	// ゲームオーバー時の更新処理
	void UpdateGameOver();
	// リザルト時の更新処理
	void UpdateResult();

	void UpdateStage1();
	void UpdateStage2();
	void UpdateStage3();


	static CGameManager* spInstance;
	int mStageNo;		// 現在のステージ番号
	EGameState mState;	// 現在のゲームの状態
	int mStateStep;		// 状態内でのステップ
	float mElapsedTime;	// 経過時間計測用

	bool mResultSetUp;

	CResultAnnouncement* mpResult;
};
#endif