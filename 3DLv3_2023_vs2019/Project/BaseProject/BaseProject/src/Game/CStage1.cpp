#include "CStage1.h"
#include "CMoveFloor.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"

// �R���X�g���N�^
CStage1::CStage1()
{
	mStageNo = 0;
}

// �f�X�g���N�^
CStage1::~CStage1()
{
	
}

// �X�e�[�W�ǂݍ���
void CStage1::Load()
{
	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// �t�B�[���h
	CField* field = new CField();
	AddTask(field);


	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 60.0f, -20.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
	}

	// �J�����̈ʒu�ƌ�����ݒ�
	CCamera* mainCamera = new CCamera
	(
		CVector(0.0f, 80.0f, 45.0f),
		player->Position() + CVector(0.0f, 10.0f, 0.0f)
	);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(field->GetWallCol());

	//// �J�����̈ʒu�ƌ�����ݒ�
	//CCamera* mainCamera = CCamera::MainCamera();
	//if (mainCamera != nullptr)
	//{
	//	CVector eye = CVector(0.0f, 80.0f, 75.0f);
	//	CVector at = player->Position() + CVector(0.0f,10.0f,0.0f);
	//	CVector forward = (at - eye).Normalized();
	//	CVector side = CVector::Cross(forward, CVector::up);
	//	CVector up = CVector::Cross(side, forward);
	//	mainCamera->LookAt(eye, at, up);
	//	mainCamera->SetFollowTargetTf(player);
	//	// �X�t�B�A�����b�V�����炢
	//	mainCamera->AddCollider(field->GetWallCol());
	//}

	// �l�p���f��
	CMoveFloor* floor = new CMoveFloor( 
		CVector(-20.0f, -20.0f, -340.0f), 
		CVector(5.5f, 1.0f, 3.25f), 
		CVector(0.0f, 0.0f, 0.0f), 
		5.0f);
	AddTask(floor);

	// �S�[���I�u�W�F�N�g
	CGoalObject* goal = new CGoalObject(
		CVector(0.0f, 0.0f, -100.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f));
	AddTask(goal);

	// ��1
	CStone1* stone1 = new CStone1(
		CVector(-80.0f, 0.0f, -200.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(stone1);

	// �G(�K�X�}�X�N���m) ///////////////////////////
	CSoldier* sol1 = new CSoldier();
	sol1->Scale(1.0f, 1.0f, 1.0f);
	sol1->Position(-100.0f, 150, -100);
	AddTask(sol1);
	

	CSoldier* sol2 = new CSoldier();
	sol2->Scale(1.0f, 1.0f, 1.0f);
	sol2->Position(-50.0f, 150.0f, -100.0f);
	AddTask(sol2);

	CSoldier* sol3 = new CSoldier();
	sol3->Scale(1.0f, 1.0f, 1.0f);
	sol3->Position(50.0f, 150.0f, -150.0f);
	AddTask(sol3);

	/////////////////////////////////////////////////
}

// �X�e�[�W�j��
void CStage1::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}