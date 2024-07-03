#include "CBiribiri.h"
#include "Maths.h"
#include "Easing.h"
#include "CStageManager.h"

#define SCALE_Y 3.0f

// �R���X�g���N�^
CBiribiri::CBiribiri(CObjectBase* owner, const CVector& pos)
	: CObjectBase(ETag::eBiribiri, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mMovedDist(0.0f)
	, mInitialRingSize(1.0f) // �����T�C�Y
	, mCurrentRingSize(1.0f) // ���݂̃T�C�Y
	, mMaxRingSize(100.0f)    // �ő�T�C�Y��ݒ�
	, mElapsedTime(0.0f)
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
	CStageManager::RemoveTask(this);
	SAFE_DELETE(mpMesh);
}

// �X�V
void CBiribiri::Update()
{
	// �����O�̃T�C�Y�𑬂����������邽�߂̌W��
	const float growthFactor = 70.0f;

    // �����O�̃T�C�Y���ő�T�C�Y�𒴂����ꍇ�͏��ł�����
    if (mCurrentRingSize >= mMaxRingSize)
    {
        Kill();
        return;
    }

	/*if (mElapsedTime < 5.0f)
	{
		float per = Easing::BounceInOut
		(
			mElapsedTime,
			5.0f,
			0.0f,
			1.0f
		);
	}*/

	// �����O�̃X�P�[����K�p����
	CVector scaleVector(mCurrentRingSize, 100.0f, mCurrentRingSize);
	Scale(scaleVector);

	// ���݂̃����O�T�C�Y���X�V
	mCurrentRingSize += Time::DeltaTime() * growthFactor;
}

// �`��
void CBiribiri::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}