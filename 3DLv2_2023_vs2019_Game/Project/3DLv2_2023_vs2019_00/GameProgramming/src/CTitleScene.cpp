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
	//mBgImage = new CImage("White.png");
	////�w�i�̐F�ݒ�
	//mBgImage->SetColor(1.0f,0.0f, 0.0f, 1.0f);
	//mBgImage->SetPos(0.0f, 0.0f);
	//mBgImage->SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// �V�����摜��ǂݍ���
	mBgImage1 = new CImage("Title.png");	//��Ō��߂�
	// �摜�̐ݒ�i�ʒu��T�C�Y�Ȃǁj
	mBgImage1->SetPos(200.0f, 150.0f);
	mBgImage1->SetSize(400, 300);
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
		if (mBgImage1 != nullptr)
		{
			mBgImage1->Render();
		}
	}
}