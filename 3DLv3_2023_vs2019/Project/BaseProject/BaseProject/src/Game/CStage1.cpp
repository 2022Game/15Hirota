#include "CStage1.h"
#include "CField_Worlds_1.h"
#include "CField_Worlds_1_FallCol.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CWireMeshClimbWall.h"
#include "CWireMeshMoveClimbWall.h"
#include "CVanguard.h"
#include "CStageTime.h"
#include "CBlueMedal.h"
#include "CRotationg.h"
#include "CFixedFlamethrower.h"
#include "CJumpingObject.h"
#include "CSavePoint.h"
#include "CNumberFloor1.h"
#include "CNumberFloorOnce.h"
#include "CTreasureChest.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"


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
	CResourceManager::Load<CModel>("Stage",				 "Field\\GameStage(Worlds_1)\\GameStage_1(Stage).obj");					// �X�e�[�W���f��
	CResourceManager::Load<CModel>("StageSky",			 "Field\\GameStage(Worlds_1)\\GameStage_1(StageSky).obj");				// �X�e�[�W�󃂃f��
	CResourceManager::Load<CModel>("FloorCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(floorCol).obj");				// ���̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(wallCol).obj");				// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("FallCol",			 "Field\\GameStage(Worlds_1)\\GameStage_1(FallCol).obj");				// ��������R���C�_�[
	CResourceManager::Load<CModel>("WireMesh",			 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Stop).obj");			// ���ԃ��f��
	CResourceManager::Load<CModel>("WireMeshCol",		 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopCol).obj");		// ���ԃR���C�_�[
	CResourceManager::Load<CModel>("WireMeshTopCol",	 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_StopTopCol).obj");	// ���Ԓ���R���C�_�[
	CResourceManager::Load<CModel>("WireMeshMove",		 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_Move).obj");			// �������ԃ��f��
	CResourceManager::Load<CModel>("WireMeshMoveCol",	 "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_MoveCol).obj");		// �������ԃR���C�_�[
	CResourceManager::Load<CModel>("WireMeshMoveTopCol", "Field\\GameStage(Worlds_1)\\GameStage_1(WireMesh_MoveTopCol).obj");	// �������Ԓ���R���C�_�[
	CResourceManager::Load<CModel>("Load",				 "Field\\GameStage(Worlds_1)\\GameStage_1(load).obj");					// �����f��
	CResourceManager::Load<CModel>("Cloud",				 "Field\\GameStage(Worlds_1)\\GameStage_1(cloud).obj");					// �_���f��
	CResourceManager::Load<CModel>("Fance",				 "Field\\GameStage(Worlds_1)\\GameStage_1(fance).obj");					// �t�F���X���f��
	CResourceManager::Load<CModel>("Flowers",			 "Field\\GameStage(Worlds_1)\\GameStage_1(flowers).obj");				// �ԃ��f��
	CResourceManager::Load<CModel>("GoalPost",			 "Field\\GameStage(Worlds_1)\\GameStage_1(GoalPost).obj");				// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalBlock",			 "Field\\GameStage(Worlds_1)\\GameStage_1(GoalBlock).obj");				// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("Grass",				 "Field\\GameStage(Worlds_1)\\GameStage_1(grass).obj");					// �����f��
	CResourceManager::Load<CModel>("Mushroom",			 "Field\\GameStage(Worlds_1)\\GameStage_1(mushroom).obj");				// �L�m�R���f��
	CResourceManager::Load<CModel>("RockShrub",			 "Field\\GameStage(Worlds_1)\\GameStage_1(rock&shrub).obj");			// ��ƒ�؃��f��
	CResourceManager::Load<CModel>("SkyIsland",			 "Field\\GameStage(Worlds_1)\\GameStage_1(skyisland).obj");				// �󓇃��f��
	CResourceManager::Load<CModel>("Tree",				 "Field\\GameStage(Worlds_1)\\GameStage_1(Tree).obj");					// �؃��f��
	CResourceManager::Load<CModel>("Branch",			 "Field\\GameStage(Worlds_1)\\GameStage_1(Branch).obj");				// �؂芔�Ɩ؂̎}���f��
	CResourceManager::Load<CModel>("Arrowsign",			 "Field\\GameStage(Worlds_1)\\GameStage_1(arrowsign).obj");				// ���Ŕ��f��

	
	// �X�e�[�W�M�~�b�N�֘A
	CResourceManager::Load<CModel>("Rotationg",				"Field\\GameStage(Worlds_1)\\GameStage_1(RotationgObject).obj");	// ��]���鏰�̃��f��
	CResourceManager::Load<CModel>("RotationgCol",			"Field\\GameStage(Worlds_1)\\GameStage_1(RotationgObjectCol).obj");	// ��]���鏰�̃R���C�_�[
	CResourceManager::Load<CModel>("Signboard",				"Field\\Object\\signboard.obj");									// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("Number0",				"Field\\Object\\number0.obj");										// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number1",				"Field\\Object\\number1.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2",				"Field\\Object\\number2.obj");										// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3",				"Field\\Object\\number3.obj");										// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("FieldCube",				"Field\\Object\\cube.obj");											// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("BlueMedal",				"Field\\Object\\Bluemedal.obj");									// �u���[���_�����f��
	CResourceManager::Load<CModel>("RotateFloor",			"Field\\Gimmick\\RotateFloor.obj");									// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloorFrontCol",	"Field\\Gimmick\\RotateFloorFrontCol.obj");							// ��]���鏰�̑O�R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorBackCol",	"Field\\Gimmick\\RotateFloorBackCol.obj");							// ��]���鏰�̌��R���C�_�[
	CResourceManager::Load<CModel>("FlamethrowerModel",		"Field\\Gimmick\\Flamethrower(foundation).obj");					// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("FlamethrowerTank",		"Field\\Gimmick\\Flamethrower(tank).obj");							// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("FlamethrowerCol",		"Field\\Gimmick\\Flamethrower(WallCol).obj");						// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");									// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\TreasureChest.obj");								// ��
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\TreasureChestTwo.obj");							// ��(�W)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\TreasureChest(FloorCol).obj");						// ��(�W�R���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\TreasureChest(WallCol).obj");						// ��(�ǃR���C�_�[)


	CResourceManager::Load<CModel>("HatenaBlock",			 "Field\\Object\\hatena.obj");						// �n�e�i�u���b�N(�A�C�e���ۗL)
	CResourceManager::Load<CModel>("HatenaBlockAfter",		 "Field\\Object\\UsedHatenaBlock.obj");				// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	CResourceManager::Load<CModel>("RengaBlock",			 "Field\\Object\\RengaBlock.obj");					// �����K�u���b�N
	
	CResourceManager::Load<CModel>("Heart",					"Item\\StatusItem\\Heart.obj");				// �񕜃I�u�W�F�N�g
	CResourceManager::Load<CModel>("Star",					"Item\\StatusItem\\Star.obj");				// ���G�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Medal",					"Item\\StatusItem\\Medal.obj");				// ���_�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Healing",				"Item\\StatusItem\\HealingItem.obj");		// �񕜖�I�u�W�F�N�g
	CResourceManager::Load<CModel>("AttackPotion",			"Item\\StatusItem\\AttackPotion.obj");		// �U���̓A�b�v���f��

	// �L�����N�^�[�֘A
	//CResourceManager::Load<CModelX>("Vanguard", "Character\\Vanguard\\VanguardModel.x");										// ���@���K�[�h

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	// �t�B�[���h
	mpField_Worlds_1 = new CField_Worlds_1();
	mpField_Worlds_1->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpField_Worlds_1);
	// �����R���C�_�[
	mpFallCol = new CField_Worlds_1_FallCol();
	mpFallCol->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpFallCol);

	/////////////////////////////////////////////////////////////////////////////////////

	// �X�e�[�W�M�~�b�N

	// �o�����Ԃ��쐬
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 10.0f)	// ���ʕ����̈ړ�
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// �����o�����Ԃ��쐬
	CWireMeshMoveClimbWall* wiremeshmoveWall = new CWireMeshMoveClimbWall
	(
		"WireMeshMove", "WireMeshMoveTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 10.0f),	// ���ʕ����̈ړ�
		CVector(-0.5f,0.3f,0.0f),
		CVector(40.0f,0.0f,0.0f),
		10.0f
	);
	wiremeshmoveWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshmoveWall);

	//// �����Ɖ�]���郂�f��
	//CRotationg* rotationg = new CRotationg
	//(
	//	CVector(804.0f, 212.0f, -182.0f),
	//	CVector(5.0f, 5.0f, 5.0f),
	//	1.0f
	//);
	//AddTask(rotationg);

	//// �Ή����ˊ탂�f��
	//// ���ʕ���
	//CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	//(
	//	CVector(810.0f, 125.0f, -384.0f),
	//	CVector(2.0f, 2.0f, 2.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(flamethrower1);

	//// �Ή����ˊ탂�f��
	//// �E����
	//CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	//(
	//	CVector(1115.0f, 213.0f, -447.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//flamethrower2->Rotate(-90.0f, 0.0f, -90.0f);
	//AddTask(flamethrower2);

	//// �W�����v�I�u�W�F�N�g
	//CJumpingObject* jumping1 = new CJumpingObject
	//(
	//	CVector(1183.0f, 250.0f, -350.0f),
	//	CVector(0.5f, 0.5f, 0.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(jumping1);

	//// �W�����v�I�u�W�F�N�g
	//CJumpingObject* jumping2 = new CJumpingObject
	//(
	//	CVector(1244.0f, 285.0f, -211.0f),
	//	CVector(0.5f, 0.5f, 0.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(jumping2);

	// �񐔃I�u�W�F�N�g(���)
	CNumberFloorOnce* numberfloor1 = new CNumberFloorOnce
	(
		CVector(-9.0f, 323.0f, -1273.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(numberfloor1);


	// ��]���鏰�M�~�b�N(����)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(190.0f, 123.0f, -110.0f),
		CVector(4.5f, 4.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);

	//// ��]���鏰�M�~�b�N(�W�����v)
	//CRotateFloorGimmick* rotategimmick = new CRotateFloorGimmick(
	//	CVector(1500.0f, 360.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick);

	//// ��]���鏰�M�~�b�N(�W�����v)
	//CRotateFloorGimmick* rotategimmick2 = new CRotateFloorGimmick(
	//	CVector(1560.0f, 370.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick2);

	// �Z�[�u�|�C���g
	CSavePoint* savepoint = new CSavePoint
	(
		CVector(-9.0f, 320.0f, -1173.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint);


	/////////////////////////////////////////////////////////////////////////////////////

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

	/////////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////////

	// 438,358,-1221

	// ��
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(438.0f, 350.0f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// �󔠊W
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(438.0f, 354.8f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// ��
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-207.0f, 194.0f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// �󔠊W
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-207, 197.8f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);


	// �����K�u���b�N
	CRengaBlock* hatena = new CRengaBlock(
		CVector(-9.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena);

	// �����K�u���b�N
	CRengaBlock* hatena1 = new CRengaBlock(
		CVector(-19.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena1);

	// �����K�u���b�N
	CRengaBlock* hatena2 = new CRengaBlock(
		CVector(9.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena2);

	// �����K�u���b�N
	CRengaBlock* hatena3 = new CRengaBlock(
		CVector(19.0f, 322.0f, -1243.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena3);

	/////////////////////////////////////////////////////////////////////////////////////

	// �L�����N�^�[

	//// ���@���K�[�h
	//CVanguard* van = new CVanguard();
	//CVanguard* vanPos = CVanguard::Instance();
	//van->Scale(1.4f, 1.4f, 1.4f);
	//van->Position(496.0f, 335.0f, -167.0f);
	//AddTask(van);
	
	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(190.0f, 125.0f, 269.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 180.0f, 0.0f);
	}
	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(
		camPos,
		playerPos,
		CVector::up
	);
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
