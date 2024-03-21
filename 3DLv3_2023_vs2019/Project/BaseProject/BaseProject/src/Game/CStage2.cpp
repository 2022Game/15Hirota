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
#include "CRotateFloorTimeGimmick.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"
#include "CClimbWall.h"

// �R���X�g���N�^
CStage2::CStage2()
{
	mStageNo = 2;
}

// �f�X�g���N�^
CStage2::~CStage2()
{

}

// �X�e�[�W�ǂݍ���
void CStage2::Load()
{
	CResourceManager::Load<CModel>("Field1",			"Field\\Stage2.obj");								// ��2��
	CResourceManager::Load<CModel>("FloorCol1",			"Field\\Stage2Floor.obj");							// ��2�ʏ�
	CResourceManager::Load<CModel>("WallCol1",			"Field\\Stage2Wall.obj");							// ��2�ʕ�
	CResourceManager::Load<CModel>("Field1",			"Field\\Stage2.obj");								// ��2�ʓG�̕�
	CResourceManager::Load<CModel>("Stage2Tree",		"Field\\Stage2(tree).obj");							// ��2�ʂ̖�
	CResourceManager::Load<CModel>("Stage2Climb",		"Field\\PlayerGimmick\\Stage2(Climb).obj");			// ��2�ʂ̓o����
	CResourceManager::Load<CModel>("Stage2ClimbedTop",	"Field\\PlayerGimmick\\Stage2(ClimbedTop).obj");	// ��2�ʂ̓o���ǂ̒���R���C�_�[
	CResourceManager::Load<CModel>("RotateFloor",		"Field\\Gimmick\\RotateFloor.obj");					// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloorFrame",	"Field\\Gimmick\\RotateFloorFrame.obj");			// ��]���鏰�g
	CResourceManager::Load<CModel>("Tree1",				"Field\\Object\\Tree1.obj");						// ��1

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// �t�B�[���h
	CField1* field = new CField1();
	field->Scale(10.0f, 10.0f, 10.0f);
	AddTask(field);

	// �o���ǂ��쐬
	CClimbWall* climbWall = new CClimbWall
	(
		"Stage2Climb", "Stage2ClimbedTop",
		CVector(0.0f,20.0f,0.0f),	// ������̈ړ�
		CVector(0.0f, 10.0f, 20.0f)	// ���ʕ����̈ړ�
	);
	climbWall->Scale(10.0f, 10.0f, 10.0f);
	AddTask(climbWall);


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

	// �n�e�i�u���b�N
	CHatenaBlock* hatena = new CHatenaBlock
	(
		CVector(-900.0f, 8.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos = CVector(-900.0f, 8.0f, -888.0f);
	if (hatena != nullptr)
	{
		hatena->SetStartPosition(hatenaPos);
	}
	AddTask(hatena);

	// �����K�u���b�N
	CRengaBlock* renga = new CRengaBlock
	(
		CVector(-850.0f, 8.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rengaPos = CVector(-850.0f, 8.0f, -888.0f);
	if (renga != nullptr)
	{
		renga->SetStartPosition(rengaPos);
	}
	AddTask(renga);


	// ��]���鏰�M�~�b�N(�v���C���[�ɔ���)
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

	// ��]���鏰�M�~�b�N(���)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(-740.0f, 7.0f, -888.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotatetimegimmickPos = CVector(-740.0f, 7.0f, -888.0f);
	if (rotatetimegimmick != nullptr)
	{
		rotatetimegimmick->SetStartPosition(rotatetimegimmickPos);
	}
	AddTask(rotatetimegimmick);

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