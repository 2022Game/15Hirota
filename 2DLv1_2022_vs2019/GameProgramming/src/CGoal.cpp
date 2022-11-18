#include "CGoal.h"
#include "CPlayer2.h"

#define TEXCOORD 279.0f,299.0f,204.0f,35.0f //テクスチャ座標

CGoal::CGoal(float x, float y, float w, float h, CTexture* pt)
{
	Set(x, y, w, h);
	Texture(pt, TEXCOORD);
	mTag = ETag::EGOAL;
}