#include "CGameScene.h"
#include "CSceneManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CCamera.h"
#include "CUIBase.h"
#include "CInput.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CSignboard.h"
#include "CGameCamera.h"
#include "CGameMenu.h"
#include "CEnemyManager.h"
#include "CRisingObject.h"
#include "CStage1.h"
#include "CSound.h"

//�R���X�g���N�^
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
{
}


//�f�X�g���N�^
CGameScene::~CGameScene()
{
}


//�V�[���ǂݍ���
void CGameScene::Load()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �t�B�[���h�֘A
	CResourceManager::Load<CModel>("Field",				"Field\\GameStage(1).obj");					// ��1��
	CResourceManager::Load<CModel>("FloorCol",			"Field\\GameStageFloor(1).obj");			// ��1�ʂ̏�
	CResourceManager::Load<CModel>("WallCol",			"Field\\GameStageWall(1).obj");				// ��1�ʂ̕�
	CResourceManager::Load<CModel>("FieldCube",			"Field\\Object\\cube.obj");					// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCylinder",		"Field\\Object\\cylinder.obj");				// �����̉�]����l�p���f��
	CResourceManager::Load<CModel>("GoalCube",			"Field\\Object\\GoalCube.obj");				// �S�[���̓y��
	CResourceManager::Load<CModel>("GoalPost",			"Field\\Object\\GoalPost.obj");				// �S�[���̃|�X�g
	CResourceManager::Load<CModel>("Stone1",			"Field\\Object\\Stone1.obj");				// ��1
	CResourceManager::Load<CModel>("Signboard",			"Field\\Object\\signboard.obj");			// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("HatenaBlock",		"Field\\Object\\hatena.obj");				// �n�e�i�u���b�N(�A�C�e���ۗL)
	CResourceManager::Load<CModel>("HatenaBlockAfter",	"Field\\Object\\UsedHatenaBlock.obj");		// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	CResourceManager::Load<CModel>("RengaBlock",		"Field\\Object\\RengaBlock.obj");			// �����K�u���b�N


	// �L�����N�^�[�֘A
	CResourceManager::Load<CModelX>("Player",			"Character\\Monster1\\Monster_1.x");						// �v���C���[
	CResourceManager::Load<CModelX>("Soldier",			"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// �\���W���[
	//CResourceManager::Load<CModelX>("UnityChan",		"Character\\UnityChan\\unitychan.x");						// ���j�e�B�����
	CResourceManager::Load<CModelX>("Yukari",			"Character\\Yukari\\Yukari_Model.x");						// �䂩�肳��


	// �A�C�e���֘A
	CResourceManager::Load<CModel>("Bullet",			"Item\\Bullet1\\Bullet.obj");				// �e
	CResourceManager::Load<CModel>("Gun_M1G",			"Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1�K�[�����h(�e)
	CResourceManager::Load<CModel>("MajicSword",		"Item\\MajicSword\\MajicSword.obj");		// ���@��
	CResourceManager::Load<CModel>("Heart",				"Item\\StatusItem\\Heart.obj");				// �񕜃I�u�W�F�N�g
	CResourceManager::Load<CModel>("Star",				"Item\\StatusItem\\Star.obj");				// ���G�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Medal",				"Item\\StatusItem\\Medal.obj");				// ���_�I�u�W�F�N�g


	// UI�֘A
	CResourceManager::Load<CTexture>("PFrame",			"UI\\Image_Gauge_Frame.png");		// �v���C���[�̃t���[��
	CResourceManager::Load<CTexture>("PBarImage",		"UI\\WhiteUI.png");					// �v���C���[�̃o�[
	CResourceManager::Load<CTexture>("PStamina",		"UI\\Sutamina.png");				// �v���C���[�̃X�^�~�i
	CResourceManager::Load<CTexture>("SFrame",			"UI\\Image_Gauge_Frame.png");		// �\���W���[�̃t���[��
	CResourceManager::Load<CTexture>("SBar",			"UI\\Gauge.png");					// �\���W���[�̃o�[
	CResourceManager::Load<CTexture>("YFrame",			"UI\\Image_Gauge_Frame.png");		// �䂩�肳��̃t���[��
	CResourceManager::Load<CTexture>("YBar",			"UI\\Gauge.png");					// �䂩�肳��̃o�[
	CResourceManager::Load<CTexture>("CSignboardUI",	"UI\\Ukye_1.png");					// U�L�[�̉摜


	// �G�t�F�N�g�֘A
	CResourceManager::Load<CTexture>("Laser",			"Effect\\laser.png");			// �e�̃G�t�F�N�g


	// BGM�֘A
	CResourceManager::Load<CSound>("SlashSound", "SE\\slash.wav");

	// �Q�[��BGM��ǂݍ���
	mpGameBGM = CResourceManager::Load<CSound>("GameBGM", "BGM\\game.wav");
	// �Q�[��BGM�̃��[�v�͈͂�ݒ�
	mpGameBGM->SetLoopRange(0, 2801203);
	// �Q�[��BGM�����[�v�Đ��J�n
	mpGameBGM->PlayLoop();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	// �t�B�[���h
	CField* field = new CField();

	// �����X�^�[(�v���C���[)
	CPlayer* player = new CPlayer();


	//CCamera* mainCamera = new CCamera
	//(
	//	CVector(0.0f, 80.0f, 45.0f),
	//	player->Position() + CVector(0.0f, 10.0f, 0.0f)
	//);
	//mainCamera->SetFollowTargetTf(player);
	//// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());

	// �Q�[�����j���[���쐬
	mpGameMenu = new CGameMenu();


	CGameManager::GameStart();
}

//�V�[���̍X�V����
void CGameScene::Update()
{
	if (CInput::PushKey('H'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}


	// �Q�[�����j���[���J���ĂȂ���΁A[�l]�L�[�Ń��j���[���J��
	if (!mpGameMenu->IsOpened())
	{
		if (CInput::PushKey('M'))
		{
			mpGameMenu->Open();
		}
	}

	// [CStage1] �̏��� /////////////////////////////////////////////////////////////

	int enemyCount = CEnemyManager::GetEnemyCount();	// �\���W���[�̐�

	static bool Rising = false;

	if (enemyCount <= 0 && !Rising)	// �X�e�[�W�ԍ�
	{
		int currentStage = CGameManager::StageNo();
		if (currentStage == 0)
		{
			// �㏸����I�u�W�F�N�g
			CRisingObject* rising = new CRisingObject
			(
				CVector(-30.0f, 3.0f, -450.0f),
				CVector(0.5f, 0.5f, 0.5f),
				ETag::ePlayer, ELayer::ePlayer
			);
			CVector risingPos = CVector(-30.0f, 3.0f, -450.0f);
			if (rising != nullptr)
			{
				rising->SetStartPosition(risingPos);
			}
			AddTask(rising);

			// ��x�ڈȍ~�̓I�u�W�F�N�g���쐬����Ȃ��悤�ɂ���
			Rising = true;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////

	// �X�e�[�W�ԍ��̊m�F
	CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
	// �\���W���[�̐��̊m�F
	CDebugPrint::Print("count:%d\n", CEnemyManager::GetEnemyCount());
}