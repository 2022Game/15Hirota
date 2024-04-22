#include "CNumberField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CNumberField::CNumberField()
	: CObjectBase(ETag::eFall,ETaskPriority::eFall)
{
	// ��������p�̃R���C�_�[
	mpStageModel = CResourceManager::Get<CModel>("NumberFallCol");

	// 1��ŏ��ł��鏰�̃R���C�_�[�쐬
	mpFallCol = new CColliderMesh(this, ELayer::eFall, mpStageModel, true);
	mpFallCol->SetCollisionTags({ ETag::ePlayer });
	mpFallCol->SetCollisionLayers({ ELayer::eDamageCol });
}

CNumberField::~CNumberField()
{
	SAFE_DELETE(mpFallCol);
}

// �ǂ̃R���C�_�[���K�v�ł���Ύ���
//CColliderMesh* CNumberField::GetWallCol() const
//{
//	
//}

void CNumberField::Update()
{

}

void CNumberField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
}