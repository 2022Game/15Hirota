#include "COneShotFloorField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

COneShotFloorField::COneShotFloorField()
	: CObjectBase(ETag::eFall,ETaskPriority::eFall)
{
	// ��������p�̃R���C�_�[
	mpStageModel = CResourceManager::Get<CModel>("NumberFallCol");

	// ��������p�̃R���C�_�[�쐬
	mpFallCol = new CColliderMesh(this, ELayer::eFall, mpStageModel, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::ePlayer });
}

COneShotFloorField::~COneShotFloorField()
{
	SAFE_DELETE(mpFallCol);
}

// �ǂ̃R���C�_�[���K�v�ł���Ύ���
//CColliderMesh* COneShotFloorField::GetWallCol() const
//{
//	
//}

void COneShotFloorField::Update()
{

}

void COneShotFloorField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}