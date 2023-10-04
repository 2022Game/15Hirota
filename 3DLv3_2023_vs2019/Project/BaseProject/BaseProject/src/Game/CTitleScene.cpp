#include "CTitleScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"

//�R���X�g���N�^
CTitleScene::CTitleScene()
	: CSceneBase(EScene::eTitle)
	, mBgImage(nullptr)
{
}

//�f�X�g���N�^
CTitleScene::~CTitleScene()
{
}

//�V�[���ǂݍ���
void CTitleScene::Load()
{
	//�����Ń^�C�g����ʂɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��
	//mBgImage = new CImage("white.png");
	//mBgImage->SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	//mBgImage->SetPos(0.0f, 0.0f);
	//mBgImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);
}

//�V�[���̍X�V����
void CTitleScene::Update()
{
	if (CInput::PushKey(VK_SPACE))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame);
	}
}
