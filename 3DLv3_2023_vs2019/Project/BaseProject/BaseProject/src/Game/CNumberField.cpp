#include "CNumberField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CNumberField::CNumberField()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// ステージの背景などを追加


	// ステージのコライダーなどを追加
}

CNumberField::~CNumberField()
{

}

// 壁のコライダーが必要であれば実装
//CColliderMesh* CNumberField::GetWallCol() const
//{
//	
//}

void CNumberField::Update()
{

}

void CNumberField::Render()
{

}