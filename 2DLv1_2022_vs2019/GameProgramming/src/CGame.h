#pragma once
#include "CUi.h"
#include "CPlayer2.h"
#include <Windows.h>

//定数の定義

#define TEXTURE "image.png" //テクスチャのファイル名
#define TIPSIZE 40.0f //マップ要素のサイズ

#define TEXTURE_E1 "pngaaa.com-3726776.png"
#define TIPSIZE_E1 35.0f

#define TEXTURE_D "Dokan.png"
#define TIPSIZE_D 130.0f

#define TEXTURE_B1 "kindpng_2063012.png"
#define TIPSIZE_B1 40.0f

#define TEXTURE_B2 "kindpng_2063012.png"
#define TIPSIZE_B2 35.0f

#define TEXTURE_B3 "kindpng_2063012.png"
#define TIPSIZE_B3 35.0f

#define TEXTURE_B4 "pngaaa.com-3726776.png"
#define TIPSIZE_B4 40.0f

//#define TEXCOORD_NO_ITEM "pngaaa.com-3726776.png"
//#define TIPSIZE_B4 35.0f

#define TEXTURE_BACK "pixel-background-png-4.png"
#define TIPSIZE_BACK 40.0f

#define TEXTURE_GOAL "pngaaa.com-3726776.png"
#define TIPSIZE_GOAL 500.0f

#define TEXTURE_KINOKO "pngaaa.com-3726776.png"
#define TIPSIZE_KINOKO 40.0f

#define TEXTURE_MoveBlock "pngaaa.com-3726776.png"
#define TIPSIZE_MoveBlock 20.0f

#define TEXTURE_MoveBlock2 "pngaaa.com-3726776.png"
#define TIPSIZE_MoveBlock2 20.0f

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
	int mScore;	//スコア
	CUi* mpUi; //UIクラスのポインタ
};
