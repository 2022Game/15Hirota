#include "CPlainsStageField.h"
#include "CCollisionManager.h"
#include "CCamera.h"

CPlainsStageField::CPlainsStageField()
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
	mpArrowSignModel = CResourceManager::Get<CModel>("Arrowsign");
	// �󓇂̃��f���f�[�^�擾
	mpSkyIsland = CResourceManager::Get<CModel>("SkyIsland");

	// �؂̃��f���f�[�^�擾
	/*mpTreeModel = CResourceManager::Get<CModel>("Tree");
	mpTreeCol = new CColliderMesh(this, ELayer::eFieldWall, mpTreeModel, true);*/
	// �؂芔�Ɩ؂̎}���f���f�[�^�擾
	mpBranchModel = CResourceManager::Get<CModel>("Branch");
	//mpBranchCol = new CColliderMesh(this, ELayer::eField, mpBranchModel, true);

	//// �L�m�R�̃��f���f�[�^�擾
	//CModel* mushroom = CResourceManager::Get<CModel>("Mushroom");
	//mpMushroomSphere = new CColliderSphere
	//(
	//	this, 
	//	ELayer::eFieldWall, 
	//	1.0f
	//);

	// ��ƒ�؃��f��
	/*mpRockShrubModel = CResourceManager::Get<CModel>("RockShrub");
	mpRockShrudCol = new CColliderMesh(this, ELayer::eFieldWall, mpRockShrubModel, true);*/

	// ���̃R���C�_�[
	CModel* floorCol = CResourceManager::Get<CModel>("FloorCol");
	mpFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �ǂ̃R���C�_�[
	CModel* wallCol = CResourceManager::Get<CModel>("WallCol");
	mpWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);
}

CPlainsStageField::~CPlainsStageField()
{
	// �R���C�_�[���폜
	SAFE_DELETE(mpFloorCol);
	SAFE_DELETE(mpWallCol);
	//SAFE_DELETE(mpTreeCol);
	//SAFE_DELETE(mpRockShrudCol);

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
CColliderMesh* CPlainsStageField::GetWallCol() const
{
	return mpWallCol;
}

void CPlainsStageField::Update()
{

}

void CPlainsStageField::Render()
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
	mpArrowSignModel->SetColor(mColor);
	mpArrowSignModel->Render(Matrix());
	mpSkyIsland->SetColor(mColor);
	mpSkyIsland->Render(Matrix());
	//mpTreeModel->SetColor(mColor);
	//mpTreeModel->Render(Matrix());
	mpBranchModel->SetColor(mColor);
	mpBranchModel->Render(Matrix());
	/*mpRockShrubModel->SetColor(mColor);
	mpRockShrubModel->Render(Matrix());*/
}