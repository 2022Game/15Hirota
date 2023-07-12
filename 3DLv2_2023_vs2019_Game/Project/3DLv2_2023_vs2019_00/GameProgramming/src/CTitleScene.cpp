#include "CTitleScene.h"
#include "main.h"
#include "CSceneManager.h"

//�R���X�g���N�^
CTitleScene::CTitleScene()
	:CSceneBase(EScene::eTitle)
	,mBgImage(nullptr)
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
	//�t�F�[�h�w�i�p�̔��C���[�W��ǂݍ���
	mBgImage = new CImage("White.png");
	//�w�i�̐F�ݒ�
	mBgImage->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	mBgImage->SetPos(0.0f, 0.0f);
	mBgImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
}

//�V�[���̍X�V����
void CTitleScene::Update()
{
	if (mInput.PushKey('T'))
	{
		CSceneManager::Instance()->LoadScene(EScene::eGame);
	}
	else
	{
		if (mBgImage != nullptr)
		{
			mBgImage->Render();
		}
	}
}