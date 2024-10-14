#include "CFinalStageFallCol.h"
#include "CCollisionManager.h"
#include "CStageManager.h"

// �R���X�g���N�^
CFinalStageFallCol::CFinalStageFallCol()
	: CObjectBase(ETag::eFall, ETaskPriority::eFall)
{
	// �����R���C�_�[
	CModel* fallCol = CResourceManager::Get<CModel>("Stage3FallCol");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::ePlayer });
}

// �f�X�g���N�^
CFinalStageFallCol::~CFinalStageFallCol()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpFallCol);
}

// �X�V����
void CFinalStageFallCol::Update()
{

}

// �`�揈��
void CFinalStageFallCol::Render()
{

}