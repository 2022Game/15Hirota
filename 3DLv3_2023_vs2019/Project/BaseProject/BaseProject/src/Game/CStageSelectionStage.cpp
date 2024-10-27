#include "CStageSelectionStage.h"
#include "CStageSelectCamera.h"
#include "CGameManager.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CInput.h"
#include "CFixedFlamethrower.h"
#include "CStage1MenuObject.h"
#include "CStage2MenuObject.h"
#include "CStage3MenuObject.h"
#include "CStage4MenuObject.h"
#include "CStageSelection.h"
#include "CTreasureChest.h"
#include "CStageButton.h"
#include "CStage1Button.h"
#include "CStage2Button.h"
#include "CStage3Button.h"
#include "CStage4Button.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CBGMManager.h"
#include "CTutorialUI.h"

// �X�e�[�W�̃f�[�^�̃e�[�u��
CStageSelectionStage::StageData CStageSelectionStage::STAGE_DATA[] = 
{
	{0, CVector(65.0f, 4.5f, 36.0f), -1, 1, true},
	{1, CVector(65.0f, 3.5f, -72.0f), 0, 2, true},
	{2, CVector(65.0f, 3.5f, -185.0f), 1, 3, false},	// �����l��false
	{3, CVector(65.0f, 3.5f, -298.0f), 2, 4, false},	// �����l��false
	{4, CVector(65.0f, 3.5f, -615.0f), 3, -1, false},	// �����l��false
};

// �X�e�[�W���ړ��ł��邩�ǂ���
void CStageSelectionStage::UpdateStageMovement()
{
	CPlayer* player = CPlayer::Instance();
	if (player == nullptr) return;

	// �X�e�[�W2�Ɉڍs�\���ǂ���
	if (player->IsStartStage2()) 
	{
		STAGE_DATA[2].canMove = true;
	}
	else
	{
		STAGE_DATA[2].canMove = false;
	}

	// �X�e�[�W3�Ɉڍs�\���ǂ���
	if (player->IsStartStage3()) 
	{
		STAGE_DATA[3].canMove = true;
	}
	else
	{
		STAGE_DATA[3].canMove = false;
	}

	// �X�e�[�W4�Ɉڍs�\���ǂ���
	if (player->IsStartStage4())
	{
		STAGE_DATA[4].canMove = true;
	}
	else
	{
		STAGE_DATA[4].canMove = false;
	}
}


// �R���X�g���N�^
CStageSelectionStage::CStageSelectionStage()
	: mSelectStageNo(0)
	, IsTutorial(false)
{
	mStageNo = 0;
}

// �f�X�g���N�^
CStageSelectionStage::~CStageSelectionStage()
{
}

// �v���C���[��|�W�V�����ݒ�
CVector CStageSelectionStage::GetPlayerStartPosition()
{
	// �v���C���[�̃|�W�V������Ԃ�
	CVector playerPos;

	// �v���C���[���擾
	CPlayer* player = CPlayer::Instance();
	// �v���C���[��nul����Ȃ�������
	if (player != nullptr)
	{
		// �X�e�[�W���N���A���Ă��邩�ǂ������`�F�b�N
		bool playerStage = player->IsStageClear();
		// �v���C���[������ł�����
		bool playerDeath = player->IsMDeath();

		// �v���C���[�̏����ʒu��ݒ�
		if (playerStage || playerDeath)
		{
			// �X�e�[�W���N���A���Ă���ꍇ�̏����ʒu
			playerPos = CVector(65.0f, 30.5f, 60.0f);
			mSelectStageNo = 0;
		}
		else
		{
			// �X�e�[�W���N���A���Ă��Ȃ��ꍇ�̏����ʒu
			// pc�̕s�����ǂ���������Ȃ����A�{����4.0f�ő��v
			playerPos = CVector(65.0f, 20.0f, 36.0f);
			mSelectStageNo = 0;
		}
	}

	return playerPos;
}

// �X�e�[�W�ǂݍ���
void CStageSelectionStage::Load()
{
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W�̃I�u�W�F�N�g
	CResourceManager::Load<CModel>("StageSelect", "Field\\StageSelect\\StageSelect.obj");
	// �X�e�[�W�̏��R���C�_�[
	CResourceManager::Load<CModel>("StageSelectFloor", "Field\\StageSelect\\StageSelectFloorCol.obj");
	// �X�e�[�W�{�^�����f��
	CResourceManager::Load<CModel>("StageButton", "GameGimmick\\Gimmick\\StageButton\\StageBotan.obj");
	// �󓇃��f��
	CResourceManager::Load<CModel>("SkyIslandMenu", "GameGimmick\\Object\\Skyisland.obj");
	// �i���o�[���f��
	CResourceManager::Load<CModel>("Number3", "GameGimmick\\Gimmick\\NumberFloor\\number3.obj");
	// ���˂�L�m�R���f��
	CResourceManager::Load<CModel>("JumpingKinoko", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// ���˂�L�m�R�R���C�_�[
	CResourceManager::Load<CModel>("JumpingKinokoCol", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("SeesawModel", "GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel.obj");
	// ENTER�L�[�̉摜
	CResourceManager::Load<CTexture>("EnterUI", "UI\\GimmickUI\\ENTER.png");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eMap);

	// �Q�[�����̓J�[�\�����I�t
	CInput::ShowCursor(false);

	//// �t�B�[���h�֘A /////////////////////////////////////////////////////////////////
	
	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	/////////////////////////////////////////////////////////////////////////////////////

	//// �X�e�[�W�I�u�W�F�N�g�֘A ///////////////////////////////////////////////////////

	// �X�e�[�W1�I���{�^��
	CStage1Button* stage1button = new CStage1Button
	(
		STAGE_DATA[1].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(stage1button);

	// �X�e�[�W2�I���{�^��
	CStage2Button* stage2button = new CStage2Button
	(
		STAGE_DATA[2].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(stage2button);

	// �X�e�[�W3�I���{�^��
	CStage3Button* stage3button = new CStage3Button
	(
		STAGE_DATA[3].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(stage3button);

	// �X�e�[�W4�I���{�^��
	CStage4Button* stage4button = new CStage4Button
	(
		STAGE_DATA[4].btnPos,
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(stage4button);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W1)
	CStage1MenuObject* menuobj1 = new CStage1MenuObject
	(
		CVector(6.0f, 10.0f, -72.0f),
		CVector(2.5f, 2.5f, 2.5f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol
	);
	AddTask(menuobj1);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W2)
	CStage2MenuObject* menuobj2 = new CStage2MenuObject
	(
		CVector(6.0f, 15.0f, -185.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol
	);
	AddTask(menuobj2);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W3)
	CStage3MenuObject* menuobj3 = new CStage3MenuObject
	(
		CVector(6.0f, 30.0f, -298.0f),
		CVector(1.2f, 1.2f, 1.2f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol
	);
	AddTask(menuobj3);

	// �X�e�[�W���j���[�I�u�W�F�N�g(�X�e�[�W4)
	CStage4MenuObject* menuobj4 = new CStage4MenuObject
	(
		CVector(6.0f, 30.0f, -615.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 40.0f, 0.0f),
		ETag::ePlayer, ELayer::eDamageCol
	);
	AddTask(menuobj4);

	/////////////////////////////////////////////////////////////////////////////////////
	
	//// �v���C���[�֘A /////////////////////////////////////////////////////////////////

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
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
	
	/////////////////////////////////////////////////////////////////////////////////////

	mpTutorial = new CTutorialUI();
	AddTask(mpTutorial);
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

	// �X�e�[�W�̈ړ��\�����X�V
	UpdateStageMovement();

	// �v���C���[���ړ����ł����
	if (player->CanMoveTo())
	{
		if (!IsTutorial)
		{
			if (!mpTutorial->IsOpened())
			{
				mpTutorial->Open();
				IsTutorial = true;
			}
		}

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
			if (data.nextStageNo >= 0 && STAGE_DATA[data.nextStageNo].canMove)
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