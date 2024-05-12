#include "CResultScene.h"
#include "CSceneManager.h"
#include "CGameScene.h"
#include "CCamera.h"
#include "CTitleScene.h"
#include "CPlayer.h"
#include "CBGMManager.h"
#include "CResultAnnouncement.h"
#include "CStageManager.h"

// �R���X�g���N�^
CResultScene::CResultScene()
	: CSceneBase(EScene::eResult)
{

}

// �f�X�g���N�^
CResultScene::~CResultScene()
{

}

// �ǂݍ���
void CResultScene::Load()
{
	// �J�[�\���\��
	CInput::ShowCursor(true);
	// �w�i�F�ݒ�
	System::SetClearColor(0.2f, 0.2f, 0.2f, 0.9f);

	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 50.0f, 75.0f),
		CVector::zero
	);

	mpResult = new CResultAnnouncement();
	AddTask(mpResult);
}

// �X�V����
void CResultScene::Update()
{
	
}