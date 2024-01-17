#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"

#define TITLE_IMAGE "UI\\Title.png"

//�R���X�g���N�^
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	, mpTitle(nullptr)
{
}

//�f�X�g���N�^
CTitleScene::~CTitleScene()
{
	if (mpTitle != nullptr)
	{
		delete mpTitle;
		mpTitle = nullptr;
	}
}

//�V�[���ǂݍ���
void CTitleScene::Load()
{
	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	// �^�C�g��BGM��ǂݍ���
	mpTitleBGM = CResourceManager::Load<CSound>("TitleBGM", "BGM\\title.wav");
	// �^�C�g��BGM�����[�v�Đ��J�n
	mpTitleBGM->PlayLoop();

	mpTitle = new CImage(TITLE_IMAGE);
	mpTitle->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

//�V�[���̍X�V����
void CTitleScene::Update()
{
	if (CInput::PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame);
	}
}
