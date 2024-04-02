#pragma once
#include "CSceneBase.h"
class CGameMenu;
class CInventoryMenu;
class CSound;
class CPlayer;
class CSoldier;
class CStageTime;

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

	CStageTime* mpTime;
	int mTime;
};
