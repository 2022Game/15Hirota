#include "CBlock4.h"

#define TEXCOORD 0.0f,161.0f,560.0f,400.0f //テクスチャ座標

CBlock4::CBlock4(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK4;
}