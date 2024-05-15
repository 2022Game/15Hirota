#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"
#include "CStageButton.h"
#include "CNeedle.h"
#include "CVanguard.h"
#include "CFixedFlamethrower.h"
#include "CTreasureChest.h"

// �R���X�g���N�^
CStageSelectionStage::CStageSelectionStage()
{
	mStageNo = 0;
}

// �f�X�g���N�^
CStageSelectionStage::~CStageSelectionStage()
{

}

CVector CStageSelectionStage::GetPlayerStartPosition()
{
	CVector playerPos;

	// �v���C���[���擾
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		// �X�e�[�W3���N���A���Ă��邩�ǂ������`�F�b�N(��)
		bool playerStage3 = player->IsStageClear();

		// �v���C���[�̏����ʒu��ݒ�
		if (playerStage3)
		{
			// �X�e�[�W3���N���A���Ă���ꍇ�̏����ʒu
			playerPos = CVector(-160, 50.0f, 0.0f);
		}
		else
		{
			// �X�e�[�W3���N���A���Ă��Ȃ��ꍇ�̏����ʒu
			playerPos = CVector(-235.0f, 20.0f, 0.0f);
		}
	}

	return playerPos;
}

// �X�e�[�W�ǂݍ���
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// �X�e�[�W�Z���N�g�X�e�[�W
	CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// �X�e�[�W�Z���N�g�X�e�[�W(��)
	CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// �X�e�[�W�Z���N�g�X�e�[�W(��)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// �X�e�[�W�{�^��

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	AddTask(field);

	// �X�e�[�W�I�����f��
	CStageButton* button = new CStageButton(
		CVector(-160.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(button);


	//// �j���f��
	//CNeedle* needle = new CNeedle(
	//	CVector(100.0f, 11.0f, 0.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//CVector needlePos = CVector(100.0f, 11.0f, 0.0f);
	//if (needle != nullptr)
	//{
	//	needle->SetStartPosition(needlePos);
	//}
	//AddTask(needle);
	//// �j���f���x�[�X
	//CNeedleBase* needlebase = new CNeedleBase(
	//	CVector(100.0f, 11.0f, 0.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//CVector needlebasePos = CVector(100.0f, 11.0f, 0.0f);
	//if (needlebase != nullptr)
	//{
	//	needlebase->SetStartPosition(needlebasePos);
	//}
	//AddTask(needlebase);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	bool playerStage3 = player->IsStage3Clear();
	// �v���C���[�̏����ʒu���擾
	CVector playerPos = GetPlayerStartPosition();
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}

	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(camPos, playerPos, CVector::up);
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