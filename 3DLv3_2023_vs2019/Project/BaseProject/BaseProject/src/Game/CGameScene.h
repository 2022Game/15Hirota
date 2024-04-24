#pragma once
#include "CSceneBase.h"
class CGameMenu;
class CInventoryMenu;
class CScreenItem;
class CSound;
class CPlayer;
class CSoldier;
class CStageTime;
class CScore;

// ゲームシーン
class CGameScene :public CSceneBase
{
public:
	//コンストラクタ
	CGameScene();
	//デストラクタ
	~CGameScene();
	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();

private:
	CGameMenu* mpGameMenu;
	CInventoryMenu* mpInventoryMenu;
	CScreenItem* mpScreenItem;

	CStageTime* mpTime;
	int mTime;
	bool mIsStage1;
	bool mIsStage2;
	bool mIsStage3;

	CScore* mpScore;
	int mScore;
};
