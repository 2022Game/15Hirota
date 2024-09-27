#include "COneShotFallCol.h"
#include "CCollisionManager.h"
#include "CStageManager.h"

// �R���X�g���N�^
COneShotFallCol::COneShotFallCol()
	: CObjectBase(ETag::eFall, ETaskPriority::eFall)
{
	// �����R���C�_�[
	CModel* fallCol = CResourceManager::Get<CModel>("Stage1FallCol");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::ePlayer });
}

// �f�X�g���N�^
COneShotFallCol::~COneShotFallCol()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpFallCol);
}

// �X�V����
void COneShotFallCol::Update()
{

}

// �`�揈��
void COneShotFallCol::Render()
{

}