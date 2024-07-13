#include "CHopsAndHoopsFallCol.h"
#include "CCollisionManager.h"
#include "CCamera.h"
#include "CStageManager.h"

CHopsAndHoopsFallCol::CHopsAndHoopsFallCol()
	: CObjectBase(ETag::eFall, ETaskPriority::eFall)
{
	// 落下判定用のコライダー
	CModel* fallCol = CResourceManager::Get<CModel>("HopsAndHoops(FallCol)");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::ePlayer });
}

CHopsAndHoopsFallCol::~CHopsAndHoopsFallCol()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpFallCol);
}

void CHopsAndHoopsFallCol::Update()
{

}

void CHopsAndHoopsFallCol::Render()
{

}