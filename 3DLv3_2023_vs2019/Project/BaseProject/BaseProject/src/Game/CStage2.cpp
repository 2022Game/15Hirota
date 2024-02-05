#include "CStage2.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField1.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAppearFloor.h"
#include "CGameCamera.h"

// �R���X�g���N�^
CStage2::CStage2()
{
	mStageNo = 0;
}

// �f�X�g���N�^
CStage2::~CStage2()
{

}

// �X�e�[�W�ǂݍ���
void CStage2::Load()
{
	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// �t�B�[���h
	CField1* field = new CField1();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);


	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(1000.0f, 30.0f, 260.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
	}

	// �J�����̈ʒu�ƌ�����ݒ�
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(1000.0f, 50.0f, 310.0f),
			player->Position() + CVector(0.0f, 10.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());

	//// �J�����̈ʒu�ƌ�����ݒ�
	//CCamera* mainCamera = CCamera::MainCamera();
	//if (mainCamera != nullptr)
	//{
	//	CVector eye = CVector(0.0f, 80.0f, 45.0f);
	//	CVector at = playerPos + CVector(0.0f, 0.0f, 0.0f);
	//	mainCamera->LookAt(eye, at, CVector::up);
	//}
	//mainCamera->SetFollowTargetTf(player);
	//// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());
}

// �X�e�[�W�j��
void CStage2::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}