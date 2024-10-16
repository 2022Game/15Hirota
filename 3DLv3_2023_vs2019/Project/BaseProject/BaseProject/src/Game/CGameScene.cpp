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
	CStageManager::UnloadStage();
}

//�V�[���ǂݍ���
void CGameScene::Load()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �L�����N�^�[�֘A
	CResourceManager::Load<CModelX>("Player",				"Character\\Monster1\\Monster_1.x");						// �v���C���[
	// �s�R�����
	CResourceManager::Load<CModelX>("Pico", "Character\\PicoChan\\PicoChan.x");
	// �\���W���[
	CResourceManager::Load<CModelX>("Soldier", "Character\\Gas mask soldier\\GasMask_Soldier_Model.x");
	// ���@���K�[�h
	CResourceManager::Load<CModelX>("Vanguard", "Character\\Vanguard\\VanguardModel.x");

	
	// �A�C�e���֘A
	// ���@��
	CResourceManager::Load<CModel>("MajicSword",			"Item\\MajicSword\\MajicSword.obj");
	// ���@�����@���K�[�h
	CResourceManager::Load<CModel>("MajicSwordVan",			"Item\\MajicSword\\MajicSword(Van).obj");
	// ���@�����@���K�[�h
	CResourceManager::Load<CModel>("MajicSwordPico", "Item\\MajicSword\\MajicSword(Pico).obj");
	// �Ƃ��Ƃ��{�[��
	CResourceManager::Load<CModel>("SpikyBall", "Item\\AttackItem\\SpikyBall.obj");

	// �G�t�F�N�g�֘A
	// �e�̃G�t�F�N�g
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	// �X���b�V���G�t�F�N�g
	CResourceManager::Load<CModel>("Slash", "Effect\\slash.obj");
	// �L�����N�^�[�G�t�F�N�g
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// �L�����N�^�[�G�t�F�N�g(���C��)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");
	// �G�t�F�N�g
	CResourceManager::Load<CModel>("CircleEffect1", "Effect\\CharacterEffect\\CharaEffectCircle.obj");
	CResourceManager::Load<CModel>("CircleEffect2", "Effect\\CharacterEffect\\CharaEffectCircle(Widthver).obj");
	// �L�����N�^�[�G�t�F�N�g
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// �L�����N�^�[�G�t�F�N�g(���C��)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");



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
	// �s�R�����UI(�t���[��)
	CResourceManager::Load<CTexture>("PicoFrame", "UI\\PicoChan\\PicoChanFrame.png");
	// �s�R�����UI(�t���[��)
	CResourceManager::Load<CTexture>("PicoGauge", "UI\\PicoChan\\PicoChanGauge.png");
	// E�L�[�̉摜
	CResourceManager::Load<CTexture>("EUI", "UI\\GimmickUI\\E.png");
	// �L�[�̃t���[���摜
	CResourceManager::Load<CTexture>("Frame", "UI\\GimmickUI\\framework.png");

	
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
	//CBGMManager::Instance()->Play(EBGMType::eGame);


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �Q�[�����̓J�[�\�����I�t
	CInput::ShowCursor(false);

	//// �t�B�[���h
	//CStageSelection* field = new CStageSelection();

	//�����X�^�[(�v���C���[)
	CPlayer* player = new CPlayer();

	/*new CGameCamera
	(
		CVector(0.0f, 0.0f, 0.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);*/

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
	AddTask(mpGameMenu);
	// ����
	mpTime = new CStageTime();
	AddTask(mpTime);
	// �X�R�A
	mpScore = new CScore();
	AddTask(mpScore);
	// ���U���g
	mpResultUI = new CResultAnnouncement();
	AddTask(mpResultUI);

	CGameManager::GameStart();
}

//�V�[���̍X�V����
void CGameScene::Update()
{
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
			// BGM���Đ�
			CBGMManager::Instance()->Play(EBGMType::eEnding);
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
					// �Q�[�����̓J�[�\�����I�t
					CInput::ShowCursor(false);
					// ���j���[�����
					mpResultUI->Close();
					// BGM���Đ�
					CBGMManager::Instance()->Play(EBGMType::eMap);
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

	/*int stage = CGameManager::StageNo();
	printf("StageNo:%d\n", stage);*/

	// �X�e�[�W�ԍ��̊Ď�
	//CDebugPrint::Print("StageNo:%d\n", CGameManager::StageNo());
}