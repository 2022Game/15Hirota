#include "CField_Worlds_1.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CField_Worlds_1::CField_Worlds_1()
	: CObjectBase(ETag::eField,ETaskPriority::eBackground)
{
	// �X�e�[�W�̃��f���f�[�^�擾
	mpStageModel = CResourceManager::Get<CModel>("Stage");
	// ���̃��f���f�[�^�擾
	mpLoadModel = CResourceManager::Get<CModel>("Load");
	// �_�̃��f���f�[�^�擾
	mpCloudModel = CResourceManager::Get<CModel>("Cloud");
	// �t�F���X�̃��f���f�[�^�擾
	mpFanceModel = CResourceManager::Get<CModel>("Fance");
	// �Ԃ̃��f���f�[�^�擾
	mpFlowersModel = CResourceManager::Get<CModel>("Flowers");
	// ���̃��f���f�[�^�擾
	mpGrassModel = CResourceManager::Get<CModel>("Grass");
	// ���Ŕ̃��f���f�[�^�擾
	//mpArrowSignModel = CResourceManager::Get<CModel>("Arrow sign");

	//// �L�m�R�̃��f���f�[�^�擾
	//CModel* mushroom = CResourceManager::Get<CModel>("Mushroom");
	//mpMushroomSphere = new CColliderSphere
	//(
	//	this, 
	//	ELayer::eFieldWall, 
	//	1.0f
	//);

	//// ��ƒ�؃��f��
	//CModel* rock_shrub = CResourceManager::Get<CModel>("Rock & Shrub");
	//mpRock_Shrud = new CColliderSphere
	//(
	//	this, ELayer::eField,
	//	1.0f
	//);

	//// �؂Ɛ؂芔�Ɩ؂̎}�̃��f���f�[�^�擾
	//CModel* tree_branch = CResourceManager::Get<CModel>("Tree & Branch");
	//mpTree_BranchCol = new CColliderMesh(this, ELayer::eField, tree_branch, true);

	// ���̃R���C�_�[
	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �ǂ̃R���C�_�[
	CModel* wallCol = CResourceManager::Get<CModel>("WallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);

	// ��������p�̃R���C�_�[
	CModel* fallCol = CResourceManager::Get<CModel>("FallCol");
	mpFallCol = new CColliderMesh(this, ELayer::eFall, fallCol, true);
}

CField_Worlds_1::~CField_Worlds_1()
{
	// �R���C�_�[���폜
	SAFE_DELETE(mpFloorCol);
	SAFE_DELETE(mpWallCol);
	SAFE_DELETE(mpFallCol);

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
CColliderMesh* CField_Worlds_1::GetWallCol() const
{
	return mpWallCol;
}

void CField_Worlds_1::Update()
{

}

void CField_Worlds_1::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
	mpLoadModel->SetColor(mColor);
	mpLoadModel->Render(Matrix());
	mpCloudModel->SetColor(mColor);
	mpCloudModel->Render(Matrix());
	mpFanceModel->SetColor(mColor);
	mpFanceModel->Render(Matrix());
	mpFlowersModel->SetColor(mColor);
	mpFlowersModel->Render(Matrix());
	mpGrassModel->SetColor(mColor);
	mpGrassModel->Render(Matrix());
	/*mpArrowSignModel->SetColor(mColor);
	mpArrowSignModel->Render(Matrix());*/
}