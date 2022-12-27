#pragma once
#include "CCharacter.h"
#include "CPlayer2.h"
/*
* CMoveBlock
* 移動ブロッククラス
* マップのブロックに使用する
*/
class CMoveBlock : public CCharacter
{
public:
	//衝突処理2
	void Collision();
	//衝突処理4
	void Collision(CCharacter* m, CCharacter* o);
	//CMoveBlock(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CMoveBlock(float x, float y, float w, float h, CTexture* pt);
	//Updateでは何もしない
	void Update();
	static CMoveBlock* Instance();
private:
	static CMoveBlock* spInstance;
};
