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
#include "CStage3MenuObject.h"
#include "CStage1Button.h"
#include "CStage3Button.h"
#include "CGameManager.h"
#include "CInput.h"

// �X�e�[�W�̃f�[�^�̃e�[�u��
const CStageSelectionStage::StageData CStageSelectionStage::STAGE_DATA[]
{
	{0,CVector(65.0f, 3.5f,   36.0f),	-1, 1},
	{1,CVector(65.0f, 3.5f,  -72.0f),	 0, 3},
	{2,CVector( 0.0f, 0.0f,    0.0f),	-1,-1},
	{3,CVector(65.0f, 3.5f, -180.0f),	 1,-1},
};

// �R���X�g���N�^
CStageSelectionStage::CStageSelectionStage()
	: mSelectStageNo(0)
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
		// �X�e�[�W���N���A���Ă��邩�ǂ������`�F�b�N
		bool playerStage = player->IsStageClear();

		// �v���C���[�̏����ʒu��ݒ�
		if (playerStage)
		{
			// �X�e�[�W���N���A���Ă���ꍇ�̏����ʒu
			playerPos = CVector(65.0f, 30.5f, 60.0f);
			mSelectStageNo = 0;
		}
		else
		{
			// �X�e�[�W���N���A���Ă��Ȃ��ꍇ�̏����ʒu
			playerPos = CVector(65.0f, 3.5f, 36.0f);
			mSelectStageNo = 0;
		}
	}

	return playerPos;
}

// �X�e�[�W�ǂݍ���
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelect", "Field\\StageSelect\\StageSelect.obj");
	CResourceManager::Load<CModel>("StageSelectFloor", "Field\\StageSelect\\StageSelectFloorCol.obj");

	//CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// �X�e�[�W�Z���N�g�X�e�[�W
	//CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// �X�e�[�W�Z���N�g�X�e�[�W(��)
	//CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// �X�e�[�W�Z���N�g�X�e�[�W(��)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// �X�e�[�W�{�^��
	CResourceManager::Load<CModel>("SkyIslandMenu",		"Field\\Object\\Skyisland.obj");	// �󓇃��f��
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");					// �O�Ԗڂ̏��u���b�N

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);


	// �X�e�[�W1�I�����f��
	CStage1Button* stage1button = new CStage1Button(
		STAGE_DATA[1].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage1button);

	// �X�e�[�W3�I�����f��
	CStage3Button* stage3button = new CStage3Button(
		STAGE_DATA[3].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(stage3button);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W1)
	CStage1MenuObject* menuobj1 = new CStage1MenuObject(
		CVector(6.0f, 10.0f, -72.0f),
		CVector(2.5f, 2.5f, 2.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol);
	AddTask(menuobj1);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W3)
	CStage3MenuObject* menuobj3 = new CStage3MenuObject(
		CVector(6.0f, 30.0f, -180.0f),
		CVector(1.0f, 1.0f, 1.0f),
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
		player->Rotation(0.0f, 180.0f, 0.0f);
	}

	// �X�e�[�W�I����ʂ́A�X�e�[�W�I����ʗp�̃J�������g�p���邽�߁A
	// �Q�[���̃J�������폜����
	CCamera* camera = CCamera::MainCamera();
	if (camera != nullptr)
	{
		camera->Kill();
	}

	// �J�����̈ʒu���v���C���[������ʗ��ꂽ�ʒu�ɐݒ�
	CVector camPos = playerPos + CVector(100.0f, 70.0f, 0.0f);
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

// �X�V
void CStageSelectionStage::Update()
{
	// �v���C���[�����݂��Ȃ���΁A�������Ȃ�
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return;

	// ���ݑI�𒆂̃X�e�[�W�f�[�^���擾
	StageData data = STAGE_DATA[mSelectStageNo];

	// �v���C���[���ړ����ł����
	if (player->CanMoveTo())
	{
		//[A]��������[��]����������A�O�̃X�e�[�W�ֈړ�
		if (CInput::PushKey('A') || CInput::PushKey(VK_LEFT))
		{
			// �O�̃X�e�[�W�����݂��邩
			if (data.prevStageNo >= 0)
			{
				// �O�̃X�e�[�W�ֈړ�
				mSelectStageNo = data.prevStageNo;
				// �O�̃X�e�[�W�̃{�^���̈ʒu�Ƀv���C���[���ړ�
				player->MoveTo(STAGE_DATA[mSelectStageNo].btnPos);
			}
		}
		// [D]��������[��]����������A���̃X�e�[�W�ֈړ�
		else if (CInput::PushKey('D') || CInput::PushKey(VK_RIGHT))
		{
			// ���̃X�e�[�W�����݂��邩
			if (data.nextStageNo >= 0)
			{
				// ���̃X�e�[�W�ֈړ�
				mSelectStageNo = data.nextStageNo;
				// ���̃X�e�[�W�̃{�^���̈ʒu�Ƀv���C���[���ړ��J�n
				player->MoveTo(STAGE_DATA[mSelectStageNo].btnPos);
			}
		}
		// [Enter]����������A�X�e�[�W������
		else if (CInput::PushKey(VK_RETURN))
		{
			// �X�e�[�W�I���X�e�[�W�ȊO���I������Ă�����
			if (mSelectStageNo > 0)
			{
				// �v���C���[�ɃX�e�[�W�J�n��`����
				player->StartStage(mSelectStageNo);
			}
		}
	}
}