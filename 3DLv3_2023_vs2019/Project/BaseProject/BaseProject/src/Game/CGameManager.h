#ifndef CGAMEMANAGER_H
#define CGAMEMANAGER_H
#include "CTask.h"

//	ゲームの状態
enum class EGameState
{
	eRaady,			// 準備中
	eGame,			// ゲーム実行中
	eStageClear,	// ステージクリア
	eGameClear,		// ゲームクリア
	eGameOver,		// ゲームオーバー
};

//ゲームクラスを管理するクラス
class CGameManager : public CTask
{
public:
	// ゲーム開始
	static void GameStart();
	// ステージクリア
	static void StageClear();
	// ゲームオーバー
	static void GameOver();
	// 現在のゲームの状態を取得
	static EGameState GameState();
	// 現在のステージ番号
	static int StageNo();

	// 更新処理
	void Update();

private:
	// コンストラクタ
	CGameManager();
	// デストラクタ
	~CGameManager();

	static CGameManager* Instance();

	// 現在のゲームの状態を切り替え
	void ChangeState(EGameState state);

	// 準備状態の更新処理
	void UpdateReady();
	// ゲーム中の更新処理
	void UpdateGame();
	// ステージクリア時の更新処理
	void UpdateStageClear();
	// ゲームクリア時の更新処理
	void UpdateGameClear();
	// ゲームオーバー時の更新処理
	void UpdateGameOver();

	static CGameManager* spInstance;
	int mStageNo;		// 現在のステージ番号
	EGameState mState;	// 現在のゲームの状態
	int mStateStep;		// 状態内でのステップ
	float mElapsedTime;	// 経過時間計測用
};
#endif