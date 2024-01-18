#include "CStone1.h"

// �R���X�g���N�^
CStone1::CStone1(const CVector& pos, const CVector& scale, const CVector& rot)
{
	// ��1���f���擾
	mpModel = CResourceManager::Get<CModel>("Stone1");

	// ��1���f���R���C�_�[�쐬
	mpColliderSphere = new CColliderSphere
	(
		this, ELayer::eField,
		1.5f, true
	);
	mpColliderSphere->Position(0.0f, 1.0f, 0.0f);

	Position(pos);
	Scale(scale);
	Rotate(rot);
}

// �f�X�g���N�^
CStone1::~CStone1()
{
	SAFE_DELETE(mpColliderSphere);
}

// �X�V����
void CStone1::Update()
{

}

// �`�揈��
void CStone1::Render()
{
	mpModel->Render(Matrix());
}