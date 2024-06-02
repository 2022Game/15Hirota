#include "CBiribiri.h"

// �R���X�g���N�^
CBiribiri::CBiribiri(CObjectBase* owner, const CVector& pos, const CVector& dir,
	float speed, float dist)
	: CObjectBase(ETag::eSlash, ETaskPriority::eEffect, 0, ETaskPauseType::eGame)
	, mpOwner(owner)
	, mKillMoveDist(dist)
	, mMovedDist(0.0f)
	, mInitialRingSize(1.0f) // �����T�C�Y
	, mCurrentRingSize(1.0f) // ���݂̃T�C�Y
	, mMaxRingSize(20.0f)    // �ő�T�C�Y��ݒ�
{
	Position(pos);
	mMoveSpeed = dir.Normalized() * speed;
	Rotation(CQuaternion::LookRotation(mMoveSpeed, CVector::up));

	mpModel = CResourceManager::Get<CModel>("Biribiri");
	mpModel->SetupEffectSettings();
}

// �f�X�g���N�^
CBiribiri::~CBiribiri()
{
}

// �X�V
void CBiribiri::Update()
{
	// �����O�̃T�C�Y�𑬂����������邽�߂̌W��
	const float growthFactor = 8.0f;

	// ���݂̃����O�T�C�Y���X�V
    mCurrentRingSize += Time::DeltaTime() * growthFactor;

    // �����O�̃T�C�Y���ő�T�C�Y�𒴂����ꍇ�͏��ł�����
    if (mCurrentRingSize >= mMaxRingSize)
    {
        Kill();
        return;
    }

    // �ړ������͂����ōs���܂�

	// �����O�̃X�P�[����K�p����
	CVector scaleVector(mCurrentRingSize, 5.0f, mCurrentRingSize);
	Scale(scaleVector);
}

// �`��
void CBiribiri::Render()
{
	mpModel->SetColor(mColor);
	mpModel->Render(Matrix());
}