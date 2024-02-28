#include "CStage2.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CTree1.h"
#include "CField1.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CAppearFloor.h"
#include "CGameCamera.h"
#include "CRotateFloorGimmick.h"

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
	CVector playerPos = CVector(-757.0f, 60.0f, -858.0f);//-757,858-1109.0f, 60.0f, 1133.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 225.0f, 0.0f);//0.0f, 225.0f, 0.0f
	}

	// �J�����̈ʒu�ƌ�����ݒ� -1109.0f, 90.0f, 1200.0f
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			CVector(-757.0f, 90.0f, -958.0f),
			player->Position() + CVector(0.0f, 0.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(field->GetWallCol());


	// ��]���鏰�M�~�b�N
	CRotateFloorGimmick* rotategimmick = new CRotateFloorGimmick(
		CVector(-770.0f, 7.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotategimmickPos = CVector(-770.0f, 7.0f, -888.0f);
	if (rotategimmick != nullptr)
	{
		rotategimmick->SetStartPosition(rotategimmickPos);
	}
	AddTask(rotategimmick);

	//// ��1 //////////////////////////////////////////////

	// ��1
	CTree1Obj* tree1 = new CTree1Obj(
		CVector(-1100.0f, 0.0f, 1100.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree1);

	// ��2
	CTree1Obj* tree2 = new CTree1Obj(
		CVector(-1000.0f, 0.0f, 1000.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(tree2);


	///////////////////////////////////////////////////////
}

// �X�e�[�W�j��
void CStage2::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}