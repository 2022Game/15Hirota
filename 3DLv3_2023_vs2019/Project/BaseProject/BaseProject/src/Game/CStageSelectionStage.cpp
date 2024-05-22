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
#include "CStageSelectCamera.h"
#include "CStage1MenuObject.h"
#include "CStage1Button.h"
#include "CStage3MenuObject.h"
#include "CStage3Button.h"

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
			playerPos = CVector(-180, 30.0f, 0.0f);
		}
		else
		{
			// �X�e�[�W3���N���A���Ă��Ȃ��ꍇ�̏����ʒu
			playerPos = CVector(-160.0f, 20.0f, 0.0f);
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
	CResourceManager::Load<CModel>("SkyIslandMenu",		"Field\\Object\\Skyisland.obj");	// �󓇃��f��
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");					// �O�Ԗڂ̏��u���b�N

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	AddTask(field);


	// �X�e�[�W1�I�����f��
	CStage1Button* stage1button = new CStage1Button(
		CVector(-60.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage1button);

	// �X�e�[�W3�I�����f��
	CStage3Button* stage3button = new CStage3Button(
		CVector(-160.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage3button);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W1)
	CStageMenuObject* menuobj1 = new CStageMenuObject(
		CVector(-60.0f, 12.0f, -55.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol);
	AddTask(menuobj1);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W3)
	CStage3MenuObject* menuobj3 = new CStage3MenuObject(
		CVector(-160.0f, 12.0f, -55.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol);
	AddTask(menuobj3);



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

	// �X�e�[�W�I����ʂ́A�X�e�[�W�I����ʗp�̃J�������g�p���邽�߁A
	// �Q�[���̃J�������폜����
	CCamera* camera = CCamera::MainCamera();
	if (camera != nullptr)
	{
		camera->Kill();
	}

	// �J�����̈ʒu���v���C���[������ʗ��ꂽ�ʒu�ɐݒ�
	CVector camPos = playerPos + CVector(0.0f, 70.0f, 100.0f);
	// �X�e�[�W�I���J�����𐶐�
	camera = new CStageSelectCamera
	(
		camPos,
		playerPos,	// �J�����̒����_�̓v���C���[�̍��W
		true
	);
	// �J�������v���C���[�ɒǏ]������
	camera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());
}

// �X�e�[�W�j��
void CStageSelectionStage::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();

	// �X�e�[�W�I����ʂ̃J�������폜
	CCamera* camera = CCamera::MainCamera();
	if (camera != nullptr)
	{
		camera->Kill();
	}
	// �X�e�[�W���̃J�����𐶐�
	new CGameCamera
	(
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

}