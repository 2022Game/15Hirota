#include "CSavePoint2.h"
#include "CPlayer.h"
#include "CModel.h"
#include "CStageManager.h"

// �R�X�g���N�^
CSavePoint2::CSavePoint2(const CVector& pos, const CVector& scale, const CVector& rot)
	: CObjectBase(ETag::eSavePoint2, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{
	// �Z�[�u�|�C���g���f���擾
	mpSavePointModel = CResourceManager::Get<CModel>("SavePoint");

	// �Z�[�u�|�C���g�̃R���C�_�[�쐬
	mpSaveColLine = new CColliderLine
	(
		this, ELayer::eSavePoint2,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	mpSaveColLine->SetCollisionLayers({ ELayer::ePlayer });
	mpSaveColLine->SetCollisionTags({ ETag::ePlayer });

	SetColor(CColor(1.0f, 0.8f, 0.5f, 1.0f));

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CSavePoint2::~CSavePoint2()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpSaveColLine);
}

// �X�V����
void CSavePoint2::Update()
{

}

// �`�揈��
void CSavePoint2::Render()
{
	mpSavePointModel->SetColor(mColor);
	mpSavePointModel->Render(Matrix());
}