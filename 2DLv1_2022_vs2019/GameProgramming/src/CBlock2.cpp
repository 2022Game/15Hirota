#include "CBlock2.h"

#define TEXCOORD 0.0f,160.0f,361.0f,199.0f //テクスチャ座標

CBlock2::CBlock2(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK2;
}