#include "CStuffedRollScene.h"
#include "CTitleMenu.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CStuffedRoll.h"

#define TITLE_IMAGE "UI\\Title.png"

//�R���X�g���N�^
CStuffedRollScene::CStuffedRollScene()
	: CSceneBase(EScene::eStuffedRoll)
{
}

//�f�X�g���N�^
CStuffedRollScene::~CStuffedRollScene()
{
}

//�V�[���ǂݍ���
void CStuffedRollScene::Load()
{
	CInput::ShowCursor(false);
	// �w�i�F�ݒ�
	System::SetClearColor(0.5f, 0.5f, 0.5f, 0.9f);

	// �^�C�g��BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eTitle);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpStuffedRoll = new CStuffedRoll();
	AddTask(mpStuffedRoll);
}

//�V�[���̍X�V����
void CStuffedRollScene::Update()
{
	if (CInput::PushKey(VK_RETURN))
	{
		CSceneManager::Instance()->LoadScene(EScene::eTitle);
	}
}