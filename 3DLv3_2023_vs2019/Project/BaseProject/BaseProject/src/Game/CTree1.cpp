#include "CTree1.h"

// �R���X�g���N�^
CTree1Obj::CTree1Obj(const CVector& pos, const CVector& scale, const CVector& rot)
{
	// ��1���f���擾
	mpModel = CResourceManager::Get<CModel>("Tree1");

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
CTree1Obj::~CTree1Obj()
{
	SAFE_DELETE(mpColliderSphere);
}

// �X�V����
void CTree1Obj::Update()
{

}

// �`�揈��
void CTree1Obj::Render()
{
	mpModel->Render(Matrix());
	mpModel->SetColor(mColor);
}