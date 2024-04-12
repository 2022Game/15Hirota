#include "CSavePoint.h"
#include "CPlayer.h"

// �R�X�g���N�^
CSavePoint::CSavePoint(const CVector& pos, const CVector& scale, const CVector& rot)
{
	// �Z�[�u�|�C���g���f���擾
	mpSavePointModel = CResourceManager::Get<CModel>("SavePoint");

	// �Z�[�u�|�C���g�̃R���C�_�[�쐬
	mpSaveColLine = new CColliderLine
	(
		this, ELayer::eSavePoint,
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	mpSaveColLine->SetCollisionLayers({ ELayer::ePlayer });
	mpSaveColLine->SetCollisionTags({ ETag::ePlayer });

	Position(pos);
	Scale(scale);
	Rotation(rot);
}

// �f�X�g���N�^
CSavePoint::~CSavePoint()
{
	SAFE_DELETE(mpSaveColLine);
}

// �X�V����
void CSavePoint::Update()
{

}

// �`�揈��
void CSavePoint::Render()
{
	mpSavePointModel->SetColor(mColor);
	mpSavePointModel->Render(Matrix());
}