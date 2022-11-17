#pragma once
#include "CCharacter.h"
/*
* CDokan
*土管のクラス
*マップのブロックに使う
*/
class CDokan : public CCharacter
{
public:
	//CDokan(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CDokan(float x, float y, float w, float h, CTexture* pt);
	//Updateでは何もしない
	void Update() {}
};
