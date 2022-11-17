#pragma once
#include "CCharacter.h"
/*
* CDokan
*背景クラス
*背景に使う
*/
class CBackground : public CCharacter
{
public:
	//CBackground(X座標,Y座標,幅,高さ,テクスチャのポインタ)
	CBackground(float x, float y, float w, float h, CTexture* pt);
	//Updateでは何もしない
	void Update() {}
};