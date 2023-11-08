#include "CClearScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CTitleScene.h"
#include "CPlayer.h"

#define CLEAER "UI\\Clear.jpeg"

// �R���X�g���N�^
CClearScene::CClearScene()
	:CSceneBase(EScene::eClear)
{
}

// �f�X�g���N�^
CClearScene::~CClearScene()
{
}

// �ǂݍ���
void CClearScene::Load()
{
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