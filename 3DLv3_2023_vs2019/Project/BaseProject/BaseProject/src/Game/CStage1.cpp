#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CWireMeshClimbWall.h"


// �R���X�g���N�^
CStage1::CStage1()
{
	mStageNo = 1;
}

// �f�X�g���N�^
CStage1::~CStage1()
{
	
}

// �X�e�[�W�ǂݍ���
void CStage1::Load()
{
	// �X�e�[�W�֘A
	CResourceManager::Load<CModel>("Stage",			"Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");				// �X�e�[�W���f��
	CResourceManager::Load<CModel>("StageSky",		"Field\\GameStage(Worlds_1)\\GameStage_1(StageSky).obj");			// �X�e�[�W�󃂃f��
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");			// ���̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");			// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("FallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");			// ��������R���C�_�[
	CResourceManager::Load<CModel>("WireMesh",		"Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Stop).obj");		// ���ԃ��f��
	CResourceManager::Load<CModel>("WireMeshCol",	"Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopCol).obj");	// ���ԃR���C�_�[
	CResourceManager::Load<CModel>("WireMeshTopCol","Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopTopCol).obj");// ���Ԓ���R���C�_�[
	CResourceManager::Load<CModel>("Load",			"Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");				// �����f��
	CResourceManager::Load<CModel>("Cloud",			"Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");				// �_���f��
	CResourceManager::Load<CModel>("Fance",			"Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");				// �t�F���X���f��
	CResourceManager::Load<CModel>("Flowers",		"Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");			// �ԃ��f��
	CResourceManager::Load<CModel>("GoalPost",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");			// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalBlock",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");			// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("Grass",			"Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");				// �����f��
	CResourceManager::Load<CModel>("Mushroom",		"Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");			// �L�m�R���f��
	CResourceManager::Load<CModel>("RockShrub",		"Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");			// ��ƒ�؃��f��
	CResourceManager::Load<CModel>("SkyIsland",		"Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");			// �󓇃��f��
	CResourceManager::Load<CModel>("Tree",			"Field\\GameStage(Worlds_1)\\GameStage_1(Tree).obj");				// �؃��f��
	CResourceManager::Load<CModel>("Branch",		"Field\\GameStage(Worlds_1)\\GameStage_1(Branch).obj");				// �؂芔�Ɩ؂̎}���f��
	CResourceManager::Load<CModel>("Arrowsign",		"Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");			// ���Ŕ��f��

	CResourceManager::Load<CModel>("Signboard",		"Field\\Object\\signboard.obj");									// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("Number0",		"Field\\Object\\number0.obj");										// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number1",		"Field\\Object\\number1.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2",		"Field\\Object\\number2.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3",		"Field\\Object\\number3.obj");										// �O�Ԗڂ̏��u���b�N

	CResourceManager::Load<CModel>("RotateFloor",			"Field\\Gimmick\\RotateFloor.obj");							// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloorFrontCol",	"Field\\Gimmick\\RotateFloorFrontCol.obj");					// ��]���鏰�̑O�R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorBackCol",	"Field\\Gimmick\\RotateFloorBackCol.obj");					// ��]���鏰�̌��R���C�_�[

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);


	// �t�B�[���h
	mpField_Worlds_1 = new CField_Worlds_1();
	mpField_Worlds_1->Scale(8.0f, 8.f, 8.f);
	AddTask(mpField_Worlds_1);

	// �o�����Ԃ��쐬
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 10.0f)	// ���ʕ����̈ړ�
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// ��]���鏰�M�~�b�N(���)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(216.0f, 112.0f, -18.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);


	/////////////////////////////////////////////////////////////////////////////////////
	
	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(-150.0f, 136.0f, -5.3f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}
	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
	//  + CVector(0.0f, 10.0f, 0.0f)
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());
}


// �X�e�[�W�j��
void CStage1::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}
