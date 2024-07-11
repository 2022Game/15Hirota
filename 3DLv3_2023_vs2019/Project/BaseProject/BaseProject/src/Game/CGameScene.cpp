#include "CGameScene.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CStageSelection.h"
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
#include "CBGMManager.h"
#include "CJumpingObject.h"
#include "CInventoryMenu.h"
#include "CStageTime.h"
#include "CScore.h"
#include "CVanguard.h"
#include "CBlueMedal.h"
#include "CScreenItem.h"
#include "CResult.h"
#include "CResultAnnouncement.h"
#include "CMeat1.h"

//�R���X�g���N�^
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	, mpGameMenu(nullptr)
	, mpTime(nullptr)
	, mpScore(nullptr)
	, mpResultUI(nullptr)
	//, mpInventoryMenu(nullptr)
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
	//CResourceManager::Load<CModel>("FieldCylinder",			 "Field\\Object\\cylinder.obj");					// �����̉�]����l�p���f��
	//CResourceManager::Load<CModel>("HatenaBlock",			 "Field\\Object\\hatena.obj");						// �n�e�i�u���b�N(�A�C�e���ۗL)
	//CResourceManager::Load<CModel>("HatenaBlockAfter",		 "Field\\Object\\UsedHatenaBlock.obj");				// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	//CResourceManager::Load<CModel>("RengaBlock",			 "Field\\Object\\RengaBlock.obj");					// �����K�u���b�N


	// �L�����N�^�[�֘A
	CResourceManager::Load<CModelX>("Player",				"Character\\Monster1\\Monster_1.x");						// �v���C���[
	//CResourceManager::Load<CModelX>("Soldier",				"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// �\���W���[
	////CResourceManager::Load<CModelX>("UnityChan",			"Character\\UnityChan\\unitychan.x");						// ���j�e�B�����
	////CResourceManager::Load<CModelX>("Yukari",				"Character\\Yukari\\Yukari_Model.x");						// �䂩�肳��


	// �A�C�e���֘A
	//CResourceManager::Load<CModel>("Bullet",				"Item\\Bullet1\\Bullet.obj");				// �e
	//CResourceManager::Load<CModel>("Gun_M1G",				"Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1�K�[�����h(�e)
	CResourceManager::Load<CModel>("MajicSword",			"Item\\MajicSword\\MajicSword.obj");		// ���@��
	CResourceManager::Load<CModel>("MajicSwordVan",			"Item\\MajicSword\\MajicSword(Van).obj");	// ���@�����@���K�[�h
	//CResourceManager::Load<CModel>("Heart",					"Item\\StatusItem\\Heart.obj");				// �񕜃I�u�W�F�N�g
	//CResourceManager::Load<CModel>("Star",					"Item\\StatusItem\\Star.obj");				// ���G�I�u�W�F�N�g
	//CResourceManager::Load<CModel>("Medal",					"Item\\StatusItem\\Medal.obj");				// ���_�I�u�W�F�N�g
	//CResourceManager::Load<CModel>("Healing",				"Item\\StatusItem\\HealingItem.obj");		// �񕜖�I�u�W�F�N�g


	// UI�֘A
	CResourceManager::Load<CTexture>("PFrame",				"UI\\Image_Gauge_Frame.png");		// �v���C���[�̃t���[��
	CResourceManager::Load<CTexture>("PBarImage",			"UI\\WhiteUI.png");					// �v���C���[�̃o�[
	CResourceManager::Load<CTexture>("PStamina",			"UI\\Sutamina.png");				// �v���C���[�̃X�^�~�i
	CResourceManager::Load<CTexture>("SFrame",				"UI\\Image_Gauge_Frame.png");		// �\���W���[�̃t���[��
	CResourceManager::Load<CTexture>("SBar",				"UI\\Gauge.png");					// �\���W���[�̃o�[
	CResourceManager::Load<CTexture>("YFrame",				"UI\\Image_Gauge_Frame.png");		// �䂩�肳��̃t���[��
	CResourceManager::Load<CTexture>("YBar",				"UI\\Gauge.png");					// �䂩�肳��̃o�[
	CResourceManager::Load<CTexture>("SignboardUI",			"UI\\Ukye_1.png");					// U�L�[�̉摜
	CResourceManager::Load<CTexture>("ExclamationMark",		"UI\\bikkurimark.png");				// �r�b�N���}�[�N�摜
	CResourceManager::Load<CTexture>("Timer",				"UI\\StageUI\\Timer.png");			// �^�C�}�[�摜
	// E�L�[�̉摜
	CResourceManager::Load<CTexture>("EUI", "UI\\GimmickUI\\E.png");

	// �A�C�e��UI�֘A
	//CResourceManager::Load<CTexture>("InvincibleUI",		"UI\\Item\\Invincible Item.png");			// ���G�A�C�e���p��UI
	//CResourceManager::Load<CTexture>("AttackUpUI",			"UI\\Item\\Increase Attack Power.png");		// �U���̓A�b�v�A�C�e���p��UI
	//CResourceManager::Load<CTexture>("HealthUI",			"UI\\Item\\Health Recovery Items.png");		// �h��̓A�b�v�A�C�e���p��UI
	//CResourceManager::Load<CTexture>("No ItemUI",			"UI\\Item\\NoItemUI.png");					// �A�C�e�������p��UI

	// BGM�ESE�֘A
	// ���@�X���b�V��
	CResourceManager::Load<CSound>("SlashSound", "Sound\\SE\\slash.wav");
	// 8bit�̉񕜉�
	CResourceManager::Load<CSound>("8bitKaifuku", "Sound\\SE\\8bitkaifuku.wav");
	// 8bit�̏e�̉�(�u���b�N�p�Ɏg��)
	CResourceManager::Load<CSound>("8bitShot", "Sound\\SE\\8bitshot.wav");
	// 8bit�̉񕜉�(���G�p�Ɏg��)
	CResourceManager::Load<CSound>("8bitMutekiTime", "Sound\\SE\\8bitMuteki.wav");
	// �N���[�`���[�̚X�萺1
	CResourceManager::Load<CSound>("CreatureGrowl1", "Sound\\VOICE\\CreatureStereo5.wav");

	// �Q�[������BGM
	CBGMManager::Instance()->Play(EBGMType::eGame);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	//// �t�B�[���h
	//CStageSelection* field = new CStageSelection();

	// �����X�^�[(�v���C���[)
	CPlayer* player = new CPlayer();

	new CGameCamera
	(
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

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
	// ����
	mpTime = new CStageTime();
	// �X�R�A
	mpScore = new CScore();

	mpResultUI = new CResultAnnouncement();

	// ���U���g
	/*mpResult = new CResult();
	mpResult->SetTimeAndScore(mpTime, mpScore);*/

	// �C���x���g�����쐬
	//mpInventoryMenu = new CInventoryMenu();
	//mpInventoryMenu->SetPlayer(player);
	
	CGameManager::GameStart();
}

//�V�[���̍X�V����
void CGameScene::Update()
{
	/*CResultAnnouncement* resut = CResultAnnouncement::Instance();
	bool resultend = resut->IsResultOpened();
	bool opened = resut->IsOpened();
	CDebugPrint::Print("result:%s\n", resultend ? "true" : "false");
	CDebugPrint::Print("opned:%s\n", opened ? "true" : "false");*/

	/*CResult* result = CResult::Instance();
	int score = result->GetTotalScore();
	CDebugPrint::Print("total: %d\n", score);*/

	// �Q�[����ʂ̓J�[�\����\��
	CInput::ShowCursor(false);
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

	// �Q�[���̃X�e�[�^�X��eResult��������
	// ���U���g�\��
	// (���ɂ��������邩��)
	if (CGameManager::GameState() == EGameState::eResult)
	{
		// �J�[�\�����I���ɂ���
		CInput::ShowCursor(true);
		// ���U���g���j���[���J���Ă��Ȃ�������
		if (!mpResultUI->IsOpened())
		{
			// �J��
			mpResultUI->Open();
			mpResultUI->Update();
		}
		// ���U���g���j���[���J���Ă�����
		else
		{
			// ���U���g��ʏI���t���O���I����������
			if (mpResultUI->IsEnd())
			{
				// �Q�[���J�n�Ȃ�΁A�Q�[���V�[����ǂݍ���
				if (mpResultUI->IsStartGame())
				{
					// ���j���[�����
					mpResultUI->Close();
					CGameManager::GameRestart();
				}
				// �Q�[���I���Ȃ�΁A�A�v�������
				else if (mpResultUI->IsExitGame())
				{
					System::ExitGame();
				}
			}
		}
	}
	// �X�V
	mpResultUI->Update();

	////////////////////////////////////////////////////////////////////////////////////

	// �X�e�[�W�̍X�V
	CStageManager::Update();

	if (CInput::PushKey('L'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eStuffedRoll);
	}

	int stage = CGameManager::StageNo();
	printf("StageNo:%d\n", stage);

	// �X�e�[�W�ԍ��̊Ď�
	//CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
}