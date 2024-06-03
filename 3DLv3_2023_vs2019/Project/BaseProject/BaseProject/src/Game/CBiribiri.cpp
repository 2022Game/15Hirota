#include "CBiribiri.h"
#include "Maths.h"

#define SCALE_Y 3.0f

// �R���X�g���N�^
CBiribiri::CBiribiri(CObjectBase* owner, const CVector& pos)
	: CObjectBase(ETag::eBiribiri, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mMovedDist(0.0f)
	, mInitialRingSize(1.0f) // �����T�C�Y
	, mCurrentRingSize(1.0f) // ���݂̃T�C�Y
	, mMaxRingSize(100.0f)    // �ő�T�C�Y��ݒ�
{
	Position(pos);

	mpModel = CResourceManager::Get<CModel>("Biribiri");
	mpModel->SetupEffectSettings();

	CModel* col = CResourceManager::Get<CModel>("BiribiriCol");
	mpMesh = new CColliderMesh(this, ELayer::eBiribiri, col, true);
	mpMesh->SetCollisionLayers({ ELayer::eDamageCol });
	mpMesh->SetCollisionTags({ ETag::ePlayer });
}

// �f�X�g���N�^
CBiribiri::~CBiribiri()
{
	SAFE_DELETE(mpMesh);
}

// �X�V
void CBiribiri::Update()
{
	// �����O�̃T�C�Y�𑬂����������邽�߂̌W��
	const float growthFactor = 50.0f;

	// ���݂̃����O�T�C�Y���X�V
    mCurrentRingSize += Time::DeltaTime() * growthFactor;

    // �����O�̃T�C�Y���ő�T�C�Y�𒴂����ꍇ�͏��ł�����
    if (mCurrentRingSize >= mMaxRingSize)
    {
        Kill();
        return;
    }

	// �����O�̃X�P�[����K�p����
	CVector scaleVector(mCurrentRingSize, mCurrentRingSize, mCurrentRingSize);
	Scale(scaleVector);
}

// �`��
void CBiribiri::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}