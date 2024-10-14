#include "CFinalStageField.h"
#include "CCollisionManager.h"
#include "CStageManager.h"

// �R���X�g���N�^
CFinalStageField::CFinalStageField()
	: CObjectBase(ETag::eField, ETaskPriority::eDefault)
{
	// �X�e�[�W�̃��f���擾
	mpStageModel = CResourceManager::Get<CModel>("Stage3Base");

	// ���C���̃��f���擾
	mpLineModel = CResourceManager::Get<CModel>("Stage3Line");

	// �X�e�[�W�̏��R���C�_�[�擾
	CModel* floorCol = CResourceManager::Get<CModel>("Stage3FloorCol");
	mpStageFloorCol = new CColliderMesh(this, ELayer::eField, floorCol, true);

	// �X�e�[�W�̕ǃR���C�_�[�擾
	CModel* wallCol = CResourceManager::Get<CModel>("Stage3WallCol");
	mpStageWallCol = new CColliderMesh(this, ELayer::eFieldWall, wallCol, true);
}

// �f�X�g���N�^
CFinalStageField::~CFinalStageField()
{
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpStageFloorCol);
	SAFE_DELETE(mpStageWallCol);
}

// �X�V����
void CFinalStageField::Update()
{

}

// �`�揈��
void CFinalStageField::Render()
{
	mpStageModel->SetColor(mColor);
	mpStageModel->Render(Matrix());
	mpLineModel->SetColor(mColor);
	mpLineModel->Render(Matrix());
}