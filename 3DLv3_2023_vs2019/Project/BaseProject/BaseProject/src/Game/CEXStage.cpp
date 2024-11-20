#include "CEXStage.h"
#include "CEXStageField.h"
#include "CBGMManager.h"
#include "CInput.h"
#include "CPlayer.h"
#include "CStageSky.h"
#include "CEnemyManager.h"
#include "CPicoChan.h"
#include "CSoldier.h"

CEXStage::CEXStage()
	: mElapsedTime(0.0f)
{
	mStageNo = 5;
}

CEXStage::~CEXStage()
{
}

void CEXStage::Load()
{
	// �X�e�[�W�֘A
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("StageModel", "Field\\EXStage\\EXStage.obj");
	// ���̃R���C�_�[
	CResourceManager::Load<CModel>("FloorCol", "Field\\EXStage\\EXStage(FloorCol).obj");
	// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol", "Field\\EXStage\\EXStage(WallCol).obj");

	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	//// �t�B�[���h�֘A ////

	// �t�B�[���h
	mpStage = new CEXStageField();
	mpStage->Scale(2.0f, 2.0f, 2.0f);
	AddTask(mpStage);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	// BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eStage3);

	CInput::ShowCursor(false);

	//// �L�����N�^�[�֘A ////

	CEnemyManager* enemyManager = CEnemyManager::Instance();
	if (enemyManager == nullptr) return;
	// �L�����N�^�[

	// �s�R�����
	CPicoChan* pico = new CPicoChan();
	pico->Position(0.0f, 8.0f, 50.0f);
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->SetCenterPoint(CVector(0.0f, 8.0f, 50.0f), 30.0f);
	enemyManager->AddEnemy(pico);
	AddTask(pico);

	// �s�R�����1
	CPicoChan* pico1 = new CPicoChan();
	pico1->Position(50.0f, 8.0f, 50.0f);
	pico1->Scale(15.5f, 15.5f, 15.5f);
	pico1->SetCenterPoint(CVector(50.0f, 8.0f, 50.0f), 30.0f);
	enemyManager->AddEnemy(pico1);
	AddTask(pico1);

	// �\���W���[
	CSoldier* sol = new CSoldier();
	sol->Position(-50.0f, 8.0f, 40.0f);
	sol->Scale(1.2f, 1.2f, 1.2f);
	sol->SetCenterPoint(CVector(-50.0f, 8.0f, 40.0f), 30.0f);
	enemyManager->AddEnemy(sol);
	AddTask(sol);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// �����l�_ : 0.0f, 10.0f, 0.0f
	CVector playerPos = CVector(0.0f, 10.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);
	}
	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 14.0f, -60.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt
	(
		camPos,
		playerPos,
		CVector::up
	);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(mpStage->GetWallCol());
}

void CEXStage::Update()
{
	CheckNumberEnemies();
}

void CEXStage::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpStage->GetWallCol());

	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}