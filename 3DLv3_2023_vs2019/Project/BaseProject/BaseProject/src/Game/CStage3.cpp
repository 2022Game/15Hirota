#include "CStage3.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CCamera.h"
#include "CStageTime.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CInput.h"
#include "CFinalStageField.h"
#include "CFinalStageFallCol.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"

// �R���X�g���N�^
CStage3::CStage3()
{
	mStageNo = 3;
}

// �f�X�g���N�^
CStage3::~CStage3()
{

}

// �X�e�[�W�ǂݍ���
void CStage3::Load()
{
	// �X�e�[�W�֘A
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky",						"Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("Stage3Base",							"Field\\GameStage(Worlds_3)\\GameStage_1(Stage).obj");
	// �X�e�[�W�󃂃f��
	CResourceManager::Load<CModel>("StageSky",						"Field\\GameStage(Worlds_3)\\GameStage_1(StageSky).obj");
	// ���̃R���C�_�[
	CResourceManager::Load<CModel>("Stage3FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(floorCol).obj");
	// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// ��������R���C�_�[
	CResourceManager::Load<CModel>("FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(FallCol).obj");
	
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	//// �t�B�[���h�֘A /////////////////////////////////////////////////////////////////

	// �t�B�[���h
	mpFinalStage = new CFinalStageField();
	mpFinalStage->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStage);
	// �����R���C�_�[
	mpFinalStageFallCol = new CFinalStageFallCol();
	mpFinalStageFallCol->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStageFallCol);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	
	// �X�R�A�A�C�e��

	//// �u���[���_��1
	//CBlueMedal* blueMedal1 = new CBlueMedal
	//(
	//	CVector(317.0f, 126.0f, -18.0f) ,
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal1);
	//// �u���[���_��2
	//CBlueMedal* blueMedal2 = new CBlueMedal
	//(
	//	CVector(330.0f, 126.0f, -83.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal2);
	//// �u���[���_��3
	//CBlueMedal* blueMedal3 = new CBlueMedal
	//(
	//	CVector(401.0f, 140.0f, -436.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(blueMedal3);

	//// ���I�u�W�F�N�g /////////////////////////////////////////////////////////////////

	CMeat1* meat1 = new CMeat1
	(
		CVector(0.0f, 430.0f, -1950.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat1->SetMeatNumber(1);
	AddTask(meat1);

	CMeat2* meat2 = new CMeat2
	(
		CVector(0.0f, 430.0f, -2000.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(0.0f, 430.0f, -2050.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);

	/////////////////////////////////////////////////////////////////////////////////////

	//// �L�����N�^�[�֘A ///////////////////////////////////////////////////////////////

	// �L�����N�^�[
	
	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// �����l�_ : 190.0f, 130.0f.0f, 269.0f
	// ���Ԓn�_ : 0.0f, 320.0f, -1050.0f
	// �{�X�O	: 0.0f, 430.0f, -1890.0f
	// �S�[���t��:	-367.0f, 395.0f, -2040.0f
	// �Ή����ˊ�̑O : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(0.0f, 10.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 20.0f, 0.0f);
	}
	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 20.0f, -80.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(mpPlainsStageField->GetWallCol());

}

// �X�e�[�W�j��
void CStage3::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpPlainsStageField->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}