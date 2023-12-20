#include "CGameScene.h"
#include "CSceneManager.h"
#include "CGameOverScene.h"
#include "CClearScene.h"
#include "CField.h"
#include "CPlayer.h"
#include "CEnemy.h"
#include "Csoldier.h"
#include "CCamera.h"
#include "CUnityChan.h"
#include "CYukari.h"
#include "CUIBase.h"
#include "CImage.h"
#include "CInput.h"
#include "CStone1.h"

//�R���X�g���N�^
CGameScene::CGameScene()
	: CSceneBase(EScene::eGame)
	,image(nullptr)
	,Clear(false)
{
	//image = new CImage("UI\\Clear.jpeg"); // CLEAR_IMAGE_PATH �̓N���A�摜�̃t�@�C���p�X
	//image->SetSize(700, 500);
	//image->SetPos(CVector2(300.0f, 200.0f)); // �摜�̕\���ʒu��ݒ�
	//image->SetUV(0, 1, 1, 0);
}

//�f�X�g���N�^
CGameScene::~CGameScene()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}

//�V�[���ǂݍ���
void CGameScene::Load()
{
	//�����ŃQ�[�����ɕK�v��
	//���\�[�X�̓ǂݍ��݂�N���X�̐������s��

	// �t�B�[���h�֘A
	CResourceManager::Load<CModel>("Field","Field\\GameStage(1).obj");					// ��1��
	CResourceManager::Load<CModel>("FloorCol", "Field\\GameStageFloor(1).obj");
	CResourceManager::Load<CModel>("WallCol", "Field\\GameStageWall(1).obj");			// ��1�ʂ̕�
	CResourceManager::Load<CModel>("FieldCube", "Field\\Object\\cube.obj");				// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCylinder", "Field\\Object\\cylinder.obj");		// �����̉�]����l�p���f��
	CResourceManager::Load<CModel>("GoalCube", "Field\\Object\\GoalCube.obj");			// �S�[���̓y��
	CResourceManager::Load<CModel>("GoalPost", "Field\\Object\\GoalPost.obj");			// �S�[���̃|�X�g
	CResourceManager::Load<CModel>("Stone1", "Field\\Object\\Stone1.obj");				// ��1

	// �L�����N�^�[�֘A
	CResourceManager::Load<CModelX>("Player", "Character\\Monster1\\Monster_1.x");
	CResourceManager::Load<CModelX>("Soldier", "Character\\Gas mask soldier\\GasMask_Soldier_Model.x");
	//CResourceManager::Load<CModelX>("UnityChan", "Character\\UnityChan\\unitychan.x");
	//CResourceManager::Load<CModelX>("Yukari", "Character\\Yukari\\Yukari_Model.x");


	// �A�C�e���֘A
	CResourceManager::Load<CModel>("Bullet", "Item\\Bullet1\\Bullet.obj");
	CResourceManager::Load<CModel>("Gun_M1G", "Item\\Gun_M1Garand\\Gun_M1Garand.obj");
	CResourceManager::Load<CModel>("MajicSword", "Item\\MajicSword\\MajicSword.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CField* field = new CField();

	// �����X�^�[(�v���C���[)
	CPlayer* player = new CPlayer();
	player->Scale(1.0f, 1.0f, 1.0f);
	player->Position(0.0f, 60.0f, -30.0f);
	
	//// ���j�e�B�����
	//CUnityChan* unity = new CUnityChan();
	//unity->Scale(1.0f, 1.0f, 1.0f);
	//unity->Position(0.0f, 20.0f, 0.0f);

	//// �䂩�肳��
	//CYukari* yukari = new CYukari();
	//yukari->Scale(1.0f, 1.0f, 1.0f);
	//yukari->Position(-100.0f, 200.0f, -100.0f);

	// �K�X�}�X�N���m
	CSoldier* sol = new CSoldier();
	sol->Scale(1.0f, 1.0f, 1.0f);
	sol->Position(-100.0f, 150.0f, -100.0f);

	CSoldier* sol2 = new CSoldier();
	sol2->Scale(1.0f, 1.0f, 1.0f);
	sol2->Position(-50.0f, 150.0f, -100.0f);


	CCamera* mainCamera = new CCamera
	(
		//CVector(5.0f, -15.0f, 180.0f),
		CVector(0.0f, 90.0f, 75.0f),
		player->Position() + CVector(0.0f, 10.0f, 0.0f)
	);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(field->GetWallCol());


	//// �N���A�摜�̃��\�[�X�����[�h
	//CImage* clearImage = new CImage("UI\\Clear.jpeg"); // CLEAR_IMAGE_PATH �̓N���A�摜�̃t�@�C���p�X
	//clearImage->SetSize(800, 500);
	//clearImage->SetPos(CVector2(300.0f, 300.0f)); // �摜�̕\���ʒu��ݒ�
	//clearImage->SetUV(0, 1, 1, 0);
	// �N���A�摜�̃��\�[�X�����[�h
}

//�V�[���̍X�V����
void CGameScene::Update()
{
	// hp�擾
	int currentHP = CPlayer::Instance()->GetHp();
	// �ő�hp�擾
	int maxHP = CPlayer::Instance()->GetMaxHp();

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