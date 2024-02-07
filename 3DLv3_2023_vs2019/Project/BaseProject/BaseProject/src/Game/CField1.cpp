#include "CField1.h"
#include "CCollisionManager.h"
#include "CDamageObject.h"
#include "CRotateFloor.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CCamera.h"

CField1::CField1()
	: CObjectBase(ETag::eField, ETaskPriority::eBackground)
{
	// ���f���f�[�^�擾
	mpModel = CResourceManager::Get<CModel>("Field1");

	CModel* wallCol = CResourceManager::Get<CModel>("WallCol1");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);

	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol1");
	mpColliderMesh = new CColliderMesh(this, ELayer::eField, floorCol, true);

	/*CModel* enemywallCol = CResourceManager::Get<CModel>("EnemyWallCol1");
	mpEnemyWallCol = new CColliderMesh(this, ELayer::eFieldEnemyWall, enemywallCol, true);*/

	CreateFieldObjects();
}

CField1::~CField1()
{
	// �R���C�_�[��j��
	SAFE_DELETE(mpColliderMesh);

	if (mpWallCol != nullptr)
	{
		// ���C���J��������ǂ̃R���C�_�[�ւ̎Q�Ƃ���菜��
		CCamera* mainCamera = CCamera::MainCamera();
		if (mainCamera != nullptr)
		{
			mainCamera->RemoveCollider(mpWallCol);

		}
		delete mpWallCol;
		mpWallCol = nullptr;
	}
}

// �ǂ̃R���C�_�[�擾
CColliderMesh* CField1::GetWallCol() const
{
	return mpWallCol;
}

void CField1::CreateFieldObjects()
{

}

void CField1::Update()
{
}

void CField1::Render()
{
	mpModel->Render(Matrix());
	mpModel->SetColor(mColor);
}