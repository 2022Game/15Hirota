#include "CStageSky.h"

CStageSky::CStageSky()
	: CObjectBase(ETag::eSlash, ETaskPriority::eBackground)
{
	// 空オブジェクト設定
	mpStageSky = CResourceManager::Get<CModel>("StageSky");
}

CStageSky::~CStageSky()
{

}

void CStageSky::Update()
{
	// 回転
	float rot = 0.01f;
	Rotate(0.0f, rot, 0.0f);
}

void CStageSky::Render()
{
	mpStageSky->SetColor(mColor);
	mpStageSky->Render(Matrix());
}