#include "CTitleScene.h"
#include "CTitleMenu.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"

#define TITLE_IMAGE "UI\\Title.png"

//�R���X�g���N�^
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	, mTitle(nullptr)
	, mpTitleMenu(nullptr)
{
}

//�f�X�g���N�^
CTitleScene::~CTitleScene()
{
	mpTitleMenu->Kill();
}

//�V�[���ǂݍ���
void CTitleScene::Load()
{
	// �^�C�g�����j���[���쐬
	mpTitleMenu = new CTitleMenu();
	// �w�i�F�ݒ�
	System::SetClearColor(0.2f, 0.2f, 0.2f, 0.9f);

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

//�V�[���̍X�V����
void CTitleScene::Update()
{
	mpTitleMenu->Open();
}
