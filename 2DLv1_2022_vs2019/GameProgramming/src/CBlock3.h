#pragma once
#include "CCharacter.h"
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

public:
	bool flag_B;

	//Updateでは何もしない
	void Update() {}
};
