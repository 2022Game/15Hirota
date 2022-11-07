#pragma once
#include "CUi.h"
#include "CPlayer2.h"

//定数の定義

#define TEXTURE "image.png" //テクスチャのファイル名
#define TIPSIZE 40.0f //マップ要素のサイズ

#define TEXTURE_E1 "pngaaa.com-3726776.png"
#define TIPSIZE_E1 35.0f

#define TEXTURE_D "Dokan.png"
#define TIPSIZE_D 70.0f

#define TEXTURE_B "kindpng_2063012.png"
#define TIPSIZE_B1 40.0f

#define TEXTURE_B2 "kindpng_2063012.png"
#define TIPSIZE_B2 35.0f

#define TEXTURE_B3 "kindpng_2063012.png"
#define TIPSIZE_B3 35.0f

/*
* CGameクラス
* ゲームクラス
* ゲームのマップを作成し、
* キャラクタを配置する
*/
class CGame
{
public:
	//デストラクタ
	~CGame();
	//ゲームクリア判定
	bool IsClear();
	//ゲームクリア処理
	void Clear();
	//ゲームオーバー判定
	bool IsOver();
	//ゲームオーバー処理
	void Over();
	//スタート処理
	void Start();
	CGame(); //デフォルトコンストラクタ（初期処理）
	void Update(); //更新処理
private:
	int mCdx, mCdy; //カメラとプレイヤーの座標の差分
	void CameraSet(); //カメラ設定
	CPlayer2* mpPlayer; //プレイヤーのポインタ
	int mTime; //経過時間
	CUi* mpUi; //UIクラスのポインタ
};
