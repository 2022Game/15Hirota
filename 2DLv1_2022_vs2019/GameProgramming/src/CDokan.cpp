#include "CDokan.h"

#define TEXCOORD 205.0f,816.0f,768.0f,0.0f

CDokan::CDokan(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EDOKAN;
}