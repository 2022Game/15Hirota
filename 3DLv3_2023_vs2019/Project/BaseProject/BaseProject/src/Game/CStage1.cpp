#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"


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
	CResourceManager::Load<CModel>("Stage",			"Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");			// �X�e�[�W���f��
	CResourceManager::Load<CModel>("FloorCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");		// ���̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");		// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("FallCol",		"Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");		// ��������R���C�_�[
	CResourceManager::Load<CModel>("ClimbWall_1",	"Field\\GameStage(Worlds_1)\\GameStage_1(ClimbWall(1)).obj");	// �o����΂߂Ɉړ������
	CResourceManager::Load<CModel>("ClimbWall_2",	"Field\\GameStage(Worlds_1)\\GameStage_1(ClimbWall(2)).obj");	// �o����^���Ɉړ������
	CResourceManager::Load<CModel>("Load",			"Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");			// �����f��
	CResourceManager::Load<CModel>("Cloud",			"Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");			// �_���f��
	CResourceManager::Load<CModel>("Fance",			"Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");			// �t�F���X���f��
	CResourceManager::Load<CModel>("Flowers",		"Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");		// �ԃ��f��
	CResourceManager::Load<CModel>("GoalPost",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");		// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalBlock",		"Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");		// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("Grass",			"Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");			// �����f��
	CResourceManager::Load<CModel>("Mushroom",		"Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");		// �L�m�R���f��
	CResourceManager::Load<CModel>("RockShrub",		"Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");		// ��ƒ�؃��f��
	CResourceManager::Load<CModel>("SkyIsland",		"Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");		// �󓇃��f��
	CResourceManager::Load<CModel>("TreeBranch",	"Field\\GameStage(Worlds_1)\\GameStage_1(Tree&Branch).obj");	// �؂Ɛ؂芔�Ɩ؂̎}���f��
	CResourceManager::Load<CModel>("Arrowsign",		"Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");		// ���Ŕ��f��

	CResourceManager::Load<CModel>("Signboard",		"Field\\Object\\signboard.obj");								// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("Number0", "Field\\Object\\number0.obj");										// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number1", "Field\\Object\\number1.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2", "Field\\Object\\number2.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");

	CResourceManager::Load<CModel>("RotateFloor",		"Field\\Gimmick\\RotateFloor.obj");							// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloorFrame",	"Field\\Gimmick\\RotateFloorFrame.obj");					// ��]���鏰�g

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// �t�B�[���h
	CField_Worlds_1* field = new CField_Worlds_1();
	field->Scale(10.0f, 10.f, 10.f);
	AddTask(field);

	
	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(-195.0f, 200.0f, 9.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -180.0f, 0.0f);
	}
	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CGameCamera* mainCamera = new CGameCamera
		//CCamera* mainCamera = new CCamera
		(
			camPos,
			player->Position() + CVector(0.0f, 10.0f, 0.0f)
		);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	mainCamera->AddCollider(field->GetWallCol());


	// ��]���鏰�M�~�b�N(���)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(285.0f, 170.0f, -24.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rotatetimegimmickPos = CVector(285.0f, 170.0f, -24.0f);
	if (rotatetimegimmick != nullptr)
	{
		rotatetimegimmick->SetStartPosition(rotatetimegimmickPos);
		rotatetimegimmick->Rotation(0.0f, 0.0f, 180.0f);
	}
	AddTask(rotatetimegimmick);
}


// �X�e�[�W�j��
void CStage1::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}
