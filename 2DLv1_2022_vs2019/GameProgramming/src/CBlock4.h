#pragma once
#include "CCharacter.h"
#include "CApplication.h"
/*
* CBlock
* ブロッククラス
* マップのブロックに使用する
*/
class CBlock4 : public CCharacter
{
public:
	//CBlock(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CBlock4(float x, float y, float w, float h, CTexture* pt);
	//敵のスコアを設定
	static void Score(int score);
	//敵のスコアを取得
	static int Score();
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	void Update();
private:
	static int sScore;	//スコア
};