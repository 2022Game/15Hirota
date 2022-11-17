#include "BackGround.h"

#define TEXCOORD 0.0f,599.0f,349.0f,0.0f

CBackground::CBackground(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBACK;
}