#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CTitleScene.h"
#include "CPlayer.h"
#include "CBGMManager.h"

// �R���X�g���N�^
CClearScene::CClearScene()
	:CSceneBase(EScene::eClear)
	, mpClearImage(nullptr)
{

}

// �f�X�g���N�^
CClearScene::~CClearScene()
{
}

// �ǂݍ���
void CClearScene::Load()
{
	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 0.0f, 1.0f);

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eClear);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
	//// �\���摜�֘A
	//CResourceManager::Load<CTexture>("ClearImage", "UI\\Clear.jpeg");


	//// �w�i�F�ݒ�
	//System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//mpClearImage = new CImage("ClearImage");
	//mpClearImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	////mpClearImage->SetUV(0, 1, 1, 0);

	//CCamera* mainCamera = new CCamera
	//(
	//	CVector(0.0f, 50.0f, 75.0f),
	//	CVector::zero
	//);
}

// �X�V����
void CClearScene::Update()
{
	if (CInput::PushKey('C'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}