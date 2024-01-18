#include "CDamageObject.h"
#include "CCollisionManager.h"
#include "CCharaBase.h"
#include "Maths.h"

// �R���X�g���N�^
CDamageObject::CDamageObject(const CVector& pos, const CVector& scale, const CVector& move, float moveTime)
	: mDefaultPos(pos)
	, mMoveVec(move)
	, mMoveTime(moveTime)
	, mElapsedTime(0.0f)
{
	// �_���[�W��^����I�u�W�F���f���擾
	mpModel = CResourceManager::Get<CModel>("FieldCube");
	// �_���[�W��^����I�u�W�F���f���R���C�_�[�쐬
	mpColliderMesh = new CColliderMesh(this, ELayer::eDamageObject, mpModel, true);
	mpColliderMesh->SetCollisionTags({ ETag::ePlayer });

	Position(mDefaultPos);
	Scale(scale);
}

// �f�X�g���N�^
CDamageObject::~CDamageObject()
{
	SAFE_DELETE(mpColliderMesh);
}

// �X�V����
void CDamageObject::Update()
{
	/*float per = mElapsedTime / mMoveTime;
	Position(mDefaultPos + mMoveVec * sinf(M_PI * 2.0f * per));

	mElapsedTime += 1.0f / 60.0f;
	if (mElapsedTime >= mMoveTime)
	{
		mElapsedTime -= mMoveTime;
	}*/
}

// �`�揈��
void CDamageObject::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}