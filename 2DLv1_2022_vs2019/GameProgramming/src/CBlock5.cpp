#include "CBlock5.h"

#define TEXCOORD 366.0f,383.0f,148.0f,131.0f //テクスチャ座標

CBlock5::CBlock5(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK5;
}