#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"
#include "CStageButton.h"
#include "CNeedle.h"

// �R���X�g���N�^
CStageSelectionStage::CStageSelectionStage()
{
	mStageNo = 2;
}

// �f�X�g���N�^
CStageSelectionStage::~CStageSelectionStage()
{

}

// �X�e�[�W�ǂݍ���
void CStageSelectionStage::Load()
{
	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	AddTask(field);

	// �X�e�[�W�I�����f��
	CStageButton* button = new CStageButton(
		CVector(150.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(button);

	// �j���f��
	CNeedle* needle = new CNeedle(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlePos = CVector(100.0f, 11.0f, 0.0f);
	if (needle != nullptr)
	{
		needle->SetStartPosition(needlePos);
	}
	AddTask(needle);
	// �j���f���x�[�X
	CNeedleBase* needlebase = new CNeedleBase(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlebasePos = CVector(100.0f, 11.0f, 0.0f);
	if (needlebase != nullptr)
	{
		needlebase->SetStartPosition(needlebasePos);
	}
	AddTask(needlebase);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(-245.0f, 60.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}

	// �J�����̈ʒu�ƌ�����ݒ�
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(-245.0f, 80.0f, 55.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());
}

// �X�e�[�W�j��
void CStageSelectionStage::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}