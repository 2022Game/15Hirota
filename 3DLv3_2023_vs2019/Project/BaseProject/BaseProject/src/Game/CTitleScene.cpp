#include "CTitleScene.h"
#include "CTitleMenu.h"
#include "CSceneManager.h"
#include "CGameManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CTitleUI.h"
#include "CTitleStage.h"
#include "CStageSky.h"
#include "CTitlePlayer.h"
#include "CStageManager.h"
#include "CGameCamera.h"

#define TITLE_IMAGE "UI\\Title.png"

//�R���X�g���N�^
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	/*, mTitle(nullptr)
	, mpTitleMenu(nullptr)*/
{
}

//�f�X�g���N�^
CTitleScene::~CTitleScene()
{
	//CStageManager::UnloadStage();
}

//�V�[���ǂݍ���
void CTitleScene::Load()
{
	// �v���C���[
	CResourceManager::Load<CModelX>("Player", "Character\\Monster1\\Monster_1.x");

	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("TitleStage", "Field\\TitleStage\\TitleStage.obj");
	// ���R���C�_�[
	CResourceManager::Load<CModel>("TitleCol","Field\\TitleStage\\FloorCol.obj");
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");

	// �^�C�g�����j���[���쐬
	//mpTitleMenu = new CTitleMenu();
	// �^�C�g����ʂ̓J�[�\���\��
	CInput::ShowCursor(true);
	// �w�i�F�ݒ�
	System::SetClearColor(0.2f, 0.2f, 0.2f, 0.9f);

	CTitleStage* stage = new CTitleStage();
	stage->Scale(1.0f, 1.0f, 1.0f);
	AddTask(stage);

	mpStageSky = new CStageSky();
	mpStageSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpStageSky);

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	// �����X�^�[(�v���C���[)
	CTitlePlayer* player = new CTitlePlayer();
	player->Position(CVector(106.0f, 48.0f, -231.0f));
	player->Scale(0.8f, 0.8f, 0.8f);
	player->Rotation(0.0f, 10.0f, 0.0f);
	AddTask(player);

	new CGameCamera
	(
		CVector(122.0f, 71.0f, -274.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);

	/*CCamera* mainCamera = new CCamera
	(
		CVector(122.0f, 71.0f, -274.0f),
		CVector::zero
	);*/

	mpTitleUI = new CTitleUI();
	AddTask(mpTitleUI);
}

//�V�[���̍X�V����
void CTitleScene::Update()
{
	//mpTitleMenu->Open();

	// �^�C�g����ʂ�
	if (mpTitleUI->IsEnd())
	{
		// �Q�[���J�n�Ȃ�΁A�Q�[���V�[����ǂݍ���
		if (mpTitleUI->IsStartGame())
		{
			CSceneManager::Instance()->LoadScene(EScene::eGame);
		}
		// �Q�[���I���Ȃ�΁A�A�v�������
		else if (mpTitleUI->IsExitGame())
		{
			System::ExitGame();
		}
	}
}
