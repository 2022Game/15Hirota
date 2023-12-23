#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CTitleScene.h"
#include "CPlayer.h"

// �R���X�g���N�^
CClearScene::CClearScene()
	:CSceneBase(EScene::eClear)
	, mpClearImage(nullptr)
{

}

// �f�X�g���N�^
CClearScene::~CClearScene()
{
	if (mpClearImage != nullptr)
	{
		delete mpClearImage;
		mpClearImage = nullptr;
	}
}

// �ǂݍ���
void CClearScene::Load()
{
	// �\���摜�֘A
	CResourceManager::Load<CTexture>("ClearImage", "UI\\Clear.jpeg");


	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mpClearImage = new CImage("ClearImage");
	mpClearImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	//mpClearImage->SetUV(0, 1, 1, 0);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

// �X�V����
void CClearScene::Update()
{
	if (CInput::PushKey('C'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}