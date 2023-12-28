#include "CGameScene.h"
#include "CSceneManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CCamera.h"
#include "CUIBase.h"
#include "CInput.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CPlayer.h"
#include "CSoldier.h"


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
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �t�B�[���h�֘A
	CResourceManager::Load<CModel>("Field",			"Field\\GameStage(1).obj");			// ��1��
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStageFloor(1).obj");	// ��1�ʂ̏�
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStageWall(1).obj");		// ��1�ʂ̕�
	CResourceManager::Load<CModel>("FieldCube",		"Field\\Object\\cube.obj");			// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCylinder", "Field\\Object\\cylinder.obj");		// �����̉�]����l�p���f��
	CResourceManager::Load<CModel>("GoalCube",		"Field\\Object\\GoalCube.obj");		// �S�[���̓y��
	CResourceManager::Load<CModel>("GoalPost",		"Field\\Object\\GoalPost.obj");		// �S�[���̃|�X�g
	CResourceManager::Load<CModel>("Stone1",		"Field\\Object\\Stone1.obj");		// ��1


	// �L�����N�^�[�֘A
	CResourceManager::Load<CModelX>("Player",	"Character\\Monster1\\Monster_1.x");						// �v���C���[
	CResourceManager::Load<CModelX>("Soldier",	"Character\\Gas mask soldier\\GasMask_Soldier_Model.x");	// �\���W���[
	//CResourceManager::Load<CModelX>("UnityChan", "Character\\UnityChan\\unitychan.x");					// ���j�e�B�����
	CResourceManager::Load<CModelX>("Yukari", "Character\\Yukari\\Yukari_Model.x");							// �䂩�肳��


	// �A�C�e���֘A
	CResourceManager::Load<CModel>("Bullet",	 "Item\\Bullet1\\Bullet.obj");				// �e
	CResourceManager::Load<CModel>("Gun_M1G",	 "Item\\Gun_M1Garand\\Gun_M1Garand.obj");	// M1�K�[�����h(�e)
	CResourceManager::Load<CModel>("MajicSword", "Item\\MajicSword\\MajicSword.obj");		// ���@��


	// UI�֘A
	CResourceManager::Load<CTexture>("PFrame",		"UI\\Image_Gauge_Frame.png");		// �v���C���[�̃t���[��
	CResourceManager::Load<CTexture>("PBarImage",	"UI\\WhiteUI.png");					// �v���C���[�̃o�[
	CResourceManager::Load<CTexture>("PStamina",	"UI\\Sutamina.png");				// �v���C���[�̃X�^�~�i
	CResourceManager::Load<CTexture>("SFrame",		"UI\\Image_Gauge_Frame.png");		// �\���W���[�̃t���[��
	CResourceManager::Load<CTexture>("SBar",		"UI\\Gauge.png");					// �\���W���[�̃o�[
	CResourceManager::Load<CTexture>("YFrame",		"UI\\Image_Gauge_Frame.png");		// �䂩�肳��̃t���[��
	CResourceManager::Load<CTexture>("YBar",		"UI\\Gauge.png");					// �䂩�肳��̃o�[

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// ���j�e�B�����
	//CUnityChan* unity = new CUnityChan();
	//unity->Scale(1.0f, 1.0f, 1.0f);
	//unity->Position(0.0f, 20.0f, 0.0f);


	// �t�B�[���h
	CField* field = new CField();

	// �����X�^�[(�v���C���[)
	CPlayer* player = new CPlayer();

	//CCamera* mainCamera = new CCamera
	//(
	//	CVector(0.0f, 80.0f, 45.0f),
	//	player->Position() + CVector(0.0f, 10.0f, 0.0f)
	//);
	//mainCamera->SetFollowTargetTf(player);
	//// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());


	CGameManager::GameStart();
}

//�V�[���̍X�V����
void CGameScene::Update()
{
	CDebugPrint::Print("enemy: %d\n", CSoldier::GetEnemyCount());
	//CDebugPrint::Print("enemy: %d\n", CSoldier::GetEnemyCount());
	//// hp�擾
	//int currentHP = CPlayer::Instance()->GetHp();
	//// �ő�hp�擾
	//int maxHP = CPlayer::Instance()->GetMaxHp();

	//int Enemy = CSoldier::GetEnemyCount();

	//if (Enemy <= 0)
	//{
	//	CSceneManager::Instance()->LoadScene(EScene::eClear);
	//}

	/*if (currentHP <= 0)
	{
		CSceneManager::Instance()->LoadScene(EScene::eOver);
	}*/

	//// hp��������؂��eOver�ɑJ�ڂ�����
	//if (currentHP <= 0) {
	//	CSceneManager::Instance()->LoadScene(EScene::eOver);
	//}
	/*else if (currentHP <= 5 && Clear)
	{
		if (Clear)
		{
			image->Load("UI\\Clear.jpeg");
			if (CInput::PushKey('C'))
			{
				CSceneManager::Instance()->LoadScene(EScene::eClear);
			}
		}
	}*/
}