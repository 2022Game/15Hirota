#include "CStuffedRollScene.h"
#include "CTitleMenu.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSound.h"
#include "CBGMManager.h"
#include "CStuffedRoll.h"
#include "CStageManager.h"

//�R���X�g���N�^
CStuffedRollScene::CStuffedRollScene()
	: CSceneBase(EScene::eStuffedRoll)
{

}

//�f�X�g���N�^
CStuffedRollScene::~CStuffedRollScene()
{
	//CStageManager::UnloadStage();
}

//�V�[���ǂݍ���
void CStuffedRollScene::Load()
{
	CInput::ShowCursor(false);
	// BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eEnding);
	// �w�i�F�ݒ�
	System::SetClearColor(0.0f, 0.0f, 0.0f, 0.7f);

	// BGM���Đ�
	//CBGMManager::Instance()->Play(EBGMType::eTitle);

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