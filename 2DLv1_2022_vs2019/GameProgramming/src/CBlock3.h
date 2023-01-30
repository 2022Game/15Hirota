#pragma once
#include "CCharacter.h"
#include "CApplication.h"
/*
* CBlock
* ブロッククラス
* マップのブロックに使用する
*/
class CBlock3 : public CCharacter
{
public:
	//CBlock(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CBlock3(float x, float y, float w, float h, CTexture* pt);
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
public:
	bool flag_B;

	//Updateでは何もしない
	void Update() {}
};
