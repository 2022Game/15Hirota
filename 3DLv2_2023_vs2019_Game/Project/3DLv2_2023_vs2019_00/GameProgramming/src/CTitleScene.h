#ifndef CTITLESCENE_H
#define CTITLESCENE_H

#include "CSceneBase.h"
#include "CImage.h"
#include "CInput.h"

//タイトルシーン
class CTitleScene :public CSceneBase
{
public:
	//コンストラクタ
	CTitleScene();
	//デストラクタ
	~CTitleScene();

	//シーン読み込み
	void Load();
	//シーンの更新処理
	void Update();
private:
	CInput mInput;	//入力判定用
	CImage* mBgImage;//背景画像
	CImage* mBgImage1;
};
#endif
