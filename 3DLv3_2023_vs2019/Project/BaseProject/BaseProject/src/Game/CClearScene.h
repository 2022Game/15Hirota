#ifndef CCLEARSCENE_H
#define CCLEARSCENE_H
#include "CSceneBase.h"
#include "CInput.h"
#include "CImage.h"

class CClearScene :public CSceneBase
{
public:
	// コンストラクタ
	CClearScene();
	// デストラクタ
	~CClearScene();

	// 読み込み
	void Load();

	// 更新処理
	void Update();
};
#endif