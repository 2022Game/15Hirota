#ifndef CGAMESCENE_H
#define CGAMESCENE_H

#include "CSceneBase.h"

//ゲームシーン
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
};
#endif