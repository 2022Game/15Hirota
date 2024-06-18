#include "CStageSky.h"

CStageSky::CStageSky()
	: CObjectBase(ETag::eSlash, ETaskPriority::eBackground)
{
	// ��I�u�W�F�N�g�ݒ�
	mpStageSky = CResourceManager::Get<CModel>("StageSky");
}

CStageSky::~CStageSky()
{

}

void CStageSky::Update()
{
	// ��]
	float rot = 0.01f;
	Rotate(0.0f, rot, 0.0f);
}

void CStageSky::Render()
{
	mpStageSky->SetColor(mColor);
	mpStageSky->Render(Matrix());
}