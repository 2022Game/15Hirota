#include "CGameScene.h"
#include "CSceneManager.h"
#include "CField.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "CCamera.h"
#include "CUnityChan.h"
#include "CFutao.h"

//�R���X�g���N�^
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
{
}

//�f�X�g���N�^
CGameScene::~CGameScene()
{
}

//�V�[���ǂݍ���
void CGameScene::Load()
{
	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	new CField();

	// �v���C���[
	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	
	// ���j�e�B�����
	CUnityChan* unity = new CUnityChan();
	unity->Scale(1.0f, 1.0f, 1.0f);
	unity->Position(0.0f, 20.0f, 0.0f);

	// �ӓ�
	CFutao* futao = new CFutao();
	futao->Scale(1.0f, 1.0f, 1.0f);
	futao->Position(20.0f, 20.0f, 0.0f);

	CCamera* mainCamera = new CCamera
	(
		//CVector(5.0f, -15.0f, 180.0f),
		CVector(0.0f, 50.0f, 75.0f),
		player->Position()
	);
	mainCamera->SetFollowTargetTf(player);
}

//�V�[���̍X�V����
void CGameScene::Update()
{
}
