#include "CBlock3.h"

#define TEXCOORD 210.0f,369.0f,160.0f,0.0f //�e�N�X�`�����W

CBlock3::CBlock3(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EBLOCK3;
}