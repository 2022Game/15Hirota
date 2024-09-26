#include "CStage3.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CCamera.h"
#include "CStageTime.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CPlainsStageField.h"
#include "CPlainsStageFallCol.h"
#include "CWireMeshClimbWall.h"
#include "CWireMeshMoveClimbWall.h"
#include "CRotateFloorGimmickOpposition.h"
#include "CRotateFloorTimeGimmick.h"
#include "CRotateFloorGimmick.h"
#include "CFixedFlamethrower.h"
#include "CNumberFloor3.h"
#include "CJumpingObject.h"
#include "CTreasureChest.h"
#include "CNumberFloor1.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"
#include "CBlueMedal.h"
#include "CRotationg.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CSeesaw.h"
#include "CJumpingKinoko.h"
#include "CNeedleUpDown.h"
#include "CNeedleLeftRight.h"
#include "CRingBeamer.h"
#include "CGoalObject.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CInput.h"
#include "CPicoChan.h"

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
	CResourceManager::Load<CModel>("Stage",							"Field\\GameStage(Worlds_3)\\GameStage_1(Stage).obj");
	// �X�e�[�W�󃂃f��
	CResourceManager::Load<CModel>("StageSky",						"Field\\GameStage(Worlds_3)\\GameStage_1(StageSky).obj");
	// ���̃R���C�_�[
	CResourceManager::Load<CModel>("FloorCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(floorCol).obj");
	// �ǂ̃R���C�_�[
	CResourceManager::Load<CModel>("WallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// ��������R���C�_�[
	CResourceManager::Load<CModel>("FallCol",						"Field\\GameStage(Worlds_3)\\GameStage_1(FallCol).obj");
	// ���ԃ��f��
	CResourceManager::Load<CModel>("WireMesh",						"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_Stop).obj");
	// ���ԃR���C�_�[
	CResourceManager::Load<CModel>("WireMeshCol",					"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_StopCol).obj");
	// ���Ԓ���R���C�_�[
	CResourceManager::Load<CModel>("WireMeshTopCol",				"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_StopTopCol).obj");
	// �������ԃ��f��
	CResourceManager::Load<CModel>("WireMeshMove",					"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_Move).obj");
	// �������ԃR���C�_�[
	CResourceManager::Load<CModel>("WireMeshMoveCol",				"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_MoveCol).obj");
	// �������Ԓ���R���C�_�[
	CResourceManager::Load<CModel>("WireMeshMoveTopCol",			"Field\\GameStage(Worlds_3)\\GameStage_1(WireMesh_MoveTopCol).obj");
	// �����f��
	CResourceManager::Load<CModel>("Load",							"Field\\GameStage(Worlds_3)\\GameStage_1(load).obj");
	// �_���f��
	CResourceManager::Load<CModel>("Cloud",							"Field\\GameStage(Worlds_3)\\GameStage_1(cloud).obj");
	// �t�F���X���f��
	CResourceManager::Load<CModel>("Fance",							"Field\\GameStage(Worlds_3)\\GameStage_1(fance).obj");
	// �ԃ��f��
	CResourceManager::Load<CModel>("Flowers",						"Field\\GameStage(Worlds_3)\\GameStage_1(flowers).obj");
	//// �S�[���|�X�g���f��
	//CResourceManager::Load<CModel>("GoalPost",						"Field\\GameStage(Worlds_3)\\GameStage_1(GoalPost).obj");
	//// �S�[���u���b�N���f��
	//CResourceManager::Load<CModel>("GoalBlock",						"Field\\GameStage(Worlds_3)\\GameStage_1(GoalBlock).obj");
	// �����f��
	CResourceManager::Load<CModel>("Grass",							"Field\\GameStage(Worlds_3)\\GameStage_1(grass).obj");
	// �L�m�R���f��
	CResourceManager::Load<CModel>("Mushroom",						"Field\\GameStage(Worlds_3)\\GameStage_1(mushroom).obj");
	// ��ƒ�؃��f��
	CResourceManager::Load<CModel>("RockShrub",						"Field\\GameStage(Worlds_3)\\GameStage_1(rock&shrub).obj");
	// �󓇃��f��
	CResourceManager::Load<CModel>("SkyIsland",						"Field\\GameStage(Worlds_3)\\GameStage_1(skyisland).obj");
	// �؃��f��
	CResourceManager::Load<CModel>("Tree",							"Field\\GameStage(Worlds_3)\\GameStage_1(Tree).obj");
	// �؂芔�Ɩ؂̎}���f��
	CResourceManager::Load<CModel>("Branch",						"Field\\GameStage(Worlds_3)\\GameStage_1(Branch).obj");
	// ���Ŕ��f��
	CResourceManager::Load<CModel>("Arrowsign",						"Field\\GameStage(Worlds_3)\\GameStage_1(arrowsign).obj");


	// �X�e�[�W�M�~�b�N�֘A
	// ��]���鏰�̃��f��
	CResourceManager::Load<CModel>("Rotationg",						"Field\\GameStage(Worlds_3)\\GameStage_1(RotationgObject).obj");
	// ��]���鏰�̃R���C�_�[
	CResourceManager::Load<CModel>("RotationgCol",					"Field\\GameStage(Worlds_3)\\GameStage_1(RotationgObjectCol).obj");
	// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("Signboard",						"GameGimmick\\Object\\signboard.obj");
	// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number0",						"GameGimmick\\Gimmick\\NumberFloor\\number0.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number1",						"GameGimmick\\Gimmick\\NumberFloor\\number1.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2",						"GameGimmick\\Gimmick\\NumberFloor\\number2.obj");
	// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3",						"GameGimmick\\Gimmick\\NumberFloor\\number3.obj");
	// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCube",						"GameGimmick\\Object\\cube.obj");
	// �u���[���_�����f��
	CResourceManager::Load<CModel>("BlueMedal",						"Item\\BlueMedal\\Bluemedal.obj");
	// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloor",					"GameGimmick\\Gimmick\\Rotate\\RotateFloor.obj");
	// ��]���鏰�̑O�R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorFrontCol",			"GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol.obj");
	// ��]���鏰�̌��R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorBackCol",			"GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol.obj");
	// ��]���鏰(����)
	CResourceManager::Load<CModel>("RotateFloorOpposition",			"GameGimmick\\Gimmick\\Rotate\\RotateFloor(Opposition).obj");
	// ��]���鏰�̑O�R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorFrontColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol(Opposition).obj");
	// ��]���鏰�̌��R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorBackColOpposition",	"GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol(Opposition).obj");
	// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("FlamethrowerModel",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(foundation).obj");
	// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("FlamethrowerTank",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(tank).obj");
	// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("FlamethrowerCol",				"GameGimmick\\Gimmick\\Flame\\Flamethrower(WallCol).obj");
	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint",						"GameGimmick\\Gimmick\\SaveFlag\\SavePoint.obj");
	// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalPost",						"GameGimmick\\Gimmick\\Goal\\GoalPost.obj");
	// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("GoalCube",						"GameGimmick\\Gimmick\\Goal\\GoalCube.obj");
	// ��
	CResourceManager::Load<CModel>("TreasureChest",					"GameGimmick\\Gimmick\\Chest\\TreasureChest.obj");
	// ��(�W)
	CResourceManager::Load<CModel>("TreasureChestTwo",				"GameGimmick\\Gimmick\\Chest\\TreasureChestTwo.obj");
	// ��(�W�R���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestCol",				"GameGimmick\\Gimmick\\Chest\\TreasureChest(FloorCol).obj");
	// ��(�ǃR���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestWallCol",			"GameGimmick\\Gimmick\\Chest\\TreasureChest(WallCol).obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("SeesawModel",					"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel.obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("SeesawModelCol",				"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(Col).obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("centerCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(CenterCol).obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("rightCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(RightCol).obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("leftCol",						"GameGimmick\\Gimmick\\SeesawGimmick\\SeesawModel(LeftCol).obj");
	// ���˂�L�m�R���f��
	CResourceManager::Load<CModel>("JumpingKinoko",					"GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// ���˂�L�m�R�R���C�_�[
	CResourceManager::Load<CModel>("JumpingKinokoCol",				"GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// �j���f��(�㉺)
	CResourceManager::Load<CModel>("Needle",						"GameGimmick\\Gimmick\\Needle\\NeedleObject(needle).obj");
	// �j���f���R���C�_�[(�㉺)
	CResourceManager::Load<CModel>("NeedleCol",						"GameGimmick\\Gimmick\\Needle\\NeedleObjectCol.obj");
	// �j�x�[�X���f��(�㉺)
	CResourceManager::Load<CModel>("NeedleBase",					"GameGimmick\\Gimmick\\Needle\\NeedleObject(base).obj");
	// �j�x�[�X�R���C�_�[(�㉺)
	CResourceManager::Load<CModel>("NeedleBaseCol",					"GameGimmick\\Gimmick\\Needle\\NeedleObjectBaseCol.obj");
	// �j���f��(���E)
	CResourceManager::Load<CModel>("NeedleLeftRight",				"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Needle).obj");
	// �j���f���R���C�_�[(���E)
	CResourceManager::Load<CModel>("NeedleColLeftRight",			"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(NeedleCol).obj");
	// �j�x�[�X���f��(���E)
	CResourceManager::Load<CModel>("NeedleBaseLeftRight",			"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Base).obj");
	// �j�x�[�X�R���C�_�[(���E)
	CResourceManager::Load<CModel>("NeedleBaseColLeftRight",		"GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(BaseCol).obj");
	// �����O�r�[�}���f��(��)
	CResourceManager::Load<CModel>("RingBeamerUP",					"Effect\\BeamObj(Upper).obj");
	// �����O�r�[�}���f��(��)
	CResourceManager::Load<CModel>("RingBeamerLO",					"Effect\\BeamObj(Lower).obj");
	// �r���r���G�t�F�N�g
	CResourceManager::Load<CModel>("Biribiri",						"Effect\\BhimaEffect.obj");
	// �����O�r�[�}���f��(�R���C�_�[)
	CResourceManager::Load<CModel>("BiribiriCol",					"Effect\\BhimaEffect(Col).obj");


	// �n�e�i�u���b�N(�A�C�e���ۗL)
	CResourceManager::Load<CModel>("HatenaBlock",					"GameGimmick\\Gimmick\\Block\\hatena.obj");
	// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	CResourceManager::Load<CModel>("HatenaBlockAfter",				"GameGimmick\\Gimmick\\Block\\UsedHatenaBlock.obj");
	// �����K�u���b�N
	CResourceManager::Load<CModel>("RengaBlock",					"GameGimmick\\Gimmick\\Block\\RengaBlock.obj");

	// �񕜃I�u�W�F�N�g
	CResourceManager::Load<CModel>("Heart",							"Item\\StatusItem\\Heart.obj");
	// ���G�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Star",							"Item\\StatusItem\\Star.obj");
	// ���_�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Medal",							"Item\\StatusItem\\Medal.obj");
	// �񕜖�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Healing",						"Item\\StatusItem\\HealingItem.obj");
	// �U���̓A�b�v���f��
	CResourceManager::Load<CModel>("AttackPotion",					"Item\\StatusItem\\AttackPotion.obj");
	// �����f��
	CResourceManager::Load<CModel>("Meat",							"Item\\StageItem\\niku.obj");

	// �L�����N�^�[�֘A
	
	// �e
	CResourceManager::Load<CModel>("Bullet", "Item\\Bullet1\\Bullet.obj");
	// M1�K�[�����h(�e)
	CResourceManager::Load<CModel>("Gun_M1G", "Item\\Gun_M1Garand\\Gun_M1Garand.obj");

	// �G�t�F�N�g�֘A
	// �e�̃G�t�F�N�g
	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");
	// �X���b�V���G�t�F�N�g
	CResourceManager::Load<CModel>("Slash", "Effect\\slash.obj");
	// �L�����N�^�[�G�t�F�N�g
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// �L�����N�^�[�G�t�F�N�g(���C��)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// T�L�[�̉摜
	CResourceManager::Load<CTexture>("TUI", "UI\\GimmickUI\\T.png");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	//// �t�B�[���h�֘A /////////////////////////////////////////////////////////////////

	// �t�B�[���h
	mpPlainsStageField = new CPlainsStageField();
	mpPlainsStageField->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpPlainsStageField);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);
	// �����R���C�_�[
	mpCPlainsStageFallCol = new CPlainsStageFallCol();
	mpCPlainsStageFallCol->Scale(8.0f, 8.0f, 8.0f);
	AddTask(mpCPlainsStageFallCol);

	// �Z�[�u�|�C���g
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 320.0f, -1173.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// �Z�[�u�|�C���g
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(0.0f, 400.0f, -1890.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint2->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// �S�[���|�X�g
	CGoalObject* goal = new CGoalObject
	(
		CVector(-367.0f, 395.0f, -2060.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	/////////////////////////////////////////////////////////////////////////////////////

	//// �X�e�[�W�I�u�W�F�N�g�֘A ///////////////////////////////////////////////////////
	
	// �o���ǁ����˂�L�m�R���񐔃I�u�W�F�N�g�������Ɖ�]����I�u�W�F�N�g���W�����v�I�u�W�F�N�g��
	// ��]���I�u�W�F�N�g���V�[�\�[���󔠁������K�u���b�N���Ή����ˊ큨�j�I�u�W�F�N�g�������O�r�[��

	// �o�����Ԃ��쐬
	CWireMeshClimbWall* wiremeshWall = new CWireMeshClimbWall
	(
		"WireMesh", "WireMeshTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 15.0f)	// ���ʕ����̈ړ�
	);
	wiremeshWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshWall);

	// �����o�����Ԃ��쐬
	CWireMeshMoveClimbWall* wiremeshmoveWall = new CWireMeshMoveClimbWall
	(
		"WireMeshMove", "WireMeshMoveTopCol",
		CVector(0.0f, 14.5f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 15.0f),	// ���ʕ����̈ړ�
		CVector(-0.5f, 0.3f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f
	);
	wiremeshmoveWall->Scale(8.0f, 8.0f, 8.0f);
	AddTask(wiremeshmoveWall);

	// ���˂�L�m�R
	CJumpingKinoko* jumping1 = new CJumpingKinoko
	(
		CVector(-148.0f, 247.0f, -1059.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(jumping1);

	// ���˂�L�m�R
	CJumpingKinoko* jumping2 = new CJumpingKinoko
	(
		CVector(0.0f, 295.0f, -1110.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(jumping2);

	// �񐔃I�u�W�F�N�g(3��)
	CNumberFloor3* numberfloor3 = new CNumberFloor3
	(
		CVector(0.0f, 323.0f, -1273.0f),
		CVector(4.0f, 1.0f, 4.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(numberfloor3);

	//// �񐔃I�u�W�F�N�g(3��)
	//CNumberFloor1* numberfloor2 = new CNumberFloor1
	//(
	//	CVector(0.0f, 366.0f, -1440.0f),
	//	CVector(4.0f, 1.0f, 4.0f),
	//	CVector(0.0f, -90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(numberfloor2);

	//// �񐔃I�u�W�F�N�g(3��)
	//CNumberFloor1* numberfloor3 = new CNumberFloor1
	//(
	//	CVector(0.0f, 366.0f, -1750.0f),
	//	CVector(4.0f, 1.0f, 4.0f),
	//	CVector(0.0f, -90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(numberfloor3);

	// �����Ɖ�]���郂�f��1
	CRotationg* rotationg = new CRotationg
	(
		CVector(12.3f, 212.0f, -689.0f),
		CVector(5.0f, 5.0f, 5.0f),
		1.0f
	);
	AddTask(rotationg);

	// �����Ɖ�]���郂�f��2
	CRotationg* rotationg2 = new CRotationg
	(
		CVector(0.0f, 366.0f, -1590.0f),
		CVector(6.0f, 5.0f, 6.0f),
		0.5f
	);
	rotationg2->SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
	AddTask(rotationg2);

	////////////////////////////////////////////////////////////////////////////////////////
	// ��]���鏰�M�~�b�N(����)
	CRotateFloorTimeGimmick* rotatetimegimmick = new CRotateFloorTimeGimmick(
		CVector(190.0f, 123.0f, -110.0f),
		CVector(4.5f, 4.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotatetimegimmick);

	// ��]���鏰�M�~�b�N(�W�����v)
	// �󔠂ւ̓��̂�̓r��
	CRotateFloorGimmick* rotategimmick1 = new CRotateFloorGimmick(
		CVector(179.0f, 320.0f, -1212.0f),
		CVector(3.3f, 3.3f, 3.3f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick1);

	// ��]���鏰�M�~�b�N(�W�����v)
	// �S�[���܂ł̓��̂�̓r���@��
	CRotateFloorGimmickOpposition* rotategimmick2 = new CRotateFloorGimmickOpposition(
		CVector(-53.0f, 335.0f, -1335.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick2);

	// ��]���鏰�M�~�b�N(�W�����v)
	// �S�[���܂ł̓��̂�̓r���@�E
	CRotateFloorGimmick* rotategimmick3 = new CRotateFloorGimmick(
		CVector(53.0f, 335.0f, -1335.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick3);

	// ��]���鏰�M�~�b�N(�W�����v)
	// �S�[���܂ł̓��̂�̓r���@�^��
	CRotateFloorTimeGimmick* rotategimmick4 = new CRotateFloorTimeGimmick(
		CVector(0.0f, 355.0f, -1388.0f),
		CVector(4.3f, 4.3f, 4.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick4);

	// ��]���鏰�M�~�b�N(�W�����v)
	// �S�[���܂ł̓��̂�̓r���@�^��
	CRotateFloorGimmick* rotategimmick5 = new CRotateFloorGimmick(
		CVector(0.0f, 386.0f, -1800.0f),
		CVector(5.3f, 5.3f, 5.3f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rotategimmick5);
	////////////////////////////////////////////////////////////////////////////////////////

	//// �V�[�\�[���f��
	//CSeesaw* seesaw1 = new CSeesaw
	//(
	//	CVector(190.0f, 135.0f, 90.0f),
	//	CVector(8.5f, 5.5f, 10.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(seesaw1);


	//// ��]���鏰�M�~�b�N(�W�����v)
	//CRotateFloorGimmick* rotategimmick2 = new CRotateFloorGimmick(
	//	CVector(1560.0f, 370.0f, -209.0f),
	//	CVector(3.3f, 3.3f, 3.3f),
	//	CVector(0.0f, 90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rotategimmick2);

	//////////////////////////////////////////////////////////
	// ��1
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(438.0f, 350.0f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// �󔠊W1
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(438.0f, 354.8f, -1221.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// ��2
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-207.0f, 194.0f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// �󔠊W2
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-207, 197.8f, -454.0f),
		CVector(6.0f, 6.0f, 6.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);
	//////////////////////////////////////////////////////////

	// �����K�u���b�N1
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(-219.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga1);
	// �n�e�i�u���b�N1
	CHatenaBlock* hatena1 = new CHatenaBlock
	(
		CVector(-211.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena1);
	// �����K�u���b�N1
	CRengaBlock* renga2 = new CRengaBlock(
		CVector(-203.0f, 251.0f, -1087.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga2);

	// �����K�u���b�N2
	CRengaBlock* renga3 = new CRengaBlock
	(
		CVector(83.0f, 285.0f, -1060.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga3);
	// �n�e�i�u���b�N2
	CHatenaBlock* hatena2 = new CHatenaBlock
	(
		CVector(83.0f, 285.0f, -1052.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena2);
	// �����K�u���b�N2
	CRengaBlock* renga4 = new CRengaBlock(
		CVector(83.0f, 285.0f, -1044.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga4);


	// �����K�u���b�N5
	CRengaBlock* renga5 = new CRengaBlock
	(
		CVector(0.0f, 410.0f, -1900.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga5);

	// �j���f��1
	CNeedleUpDown* needle1 = new CNeedleUpDown(
		CVector(-150.0f, 408.0f, -1890.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		1.4f,
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needle1);
	// �j���f���x�[�X1
	CNeedleUpDownBase* needlebase1 = new CNeedleUpDownBase(
		CVector(-150.0f, 408.0f, -1890.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needlebase1);

	//// �j���f��1
	//CNeedleLeftRight* needle1 = new CNeedleLeftRight(
	//	CVector(-130.0f, 280.0f, -1080.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needle1);
	//// �j���f���x�[�X1
	//CNeedleLeftRightBase* needlebase1 = new CNeedleLeftRightBase(
	//	CVector(-130.0f, 280.0f, -1080.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needlebase1);

	// �����O�r�[�}1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-70.0f, 379.0f, -1440.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// �����O�r�[�}1
	CRingBeamerLower* beamerLo1 = new CRingBeamerLower
	(
		CVector(-70.0f, 378.0f, -1440.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo1);

	// �����O�r�[�}2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(100.0f, 379.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// �����O�r�[�}2
	CRingBeamerLower* beamerLo2 = new CRingBeamerLower
	(
		CVector(100.0f, 378.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo2);

	// �����O�r�[�}3
	CRingBeamerUpper* beamerUp3 = new CRingBeamerUpper
	(
		CVector(-100.0f, 379.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp3);
	// �����O�r�[�}3
	CRingBeamerLower* beamerLo3 = new CRingBeamerLower
	(
		CVector(-100.0f, 378.0f, -1622.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLo3);

	// �Ή����ˊ탂�f��
	// ����
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-258.0f, 173.0f, -990.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, -90.0f, -90.0f)
	);
	AddTask(flamethrower1);

	// �Ή����ˊ탂�f��
	// �E��
	CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	(
		CVector(-149.0f, 209.0f, -990.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 90.0f)
	);
	AddTask(flamethrower2);

	/////////////////////////////////////////////////////////////////////////////////////

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
	// �\���W���[1
	CSoldier* soldier1 = new CSoldier();
	soldier1->Scale(1.5f, 1.5f, 1.5f);
	soldier1->Position(7.7f, 138.0f, -274.0f);
	soldier1->SetCenterPoint(CVector(7.7f, 130.0f, -274.0f), 40.0f);
	AddTask(soldier1);
	// �\���W���[2
	CSoldier* soldier2 = new CSoldier();
	soldier2->Scale(1.5f, 1.5f, 1.5f);
	soldier2->Position(-173.7f, 138.0f, -652.0f);
	soldier2->SetCenterPoint(CVector(-173.7f, 130.0f, -652.0f), 40.0f);
	AddTask(soldier2);

	// �s�R�����
	CPicoChan* pico = new CPicoChan();
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->Position(-187.0f, 130.0f, -903.0f);
	pico->SetCenterPoint(CVector(-187.0f, 130.0f, -903.0f), 30.0f);
	AddTask(pico);


	// ���@���K�[�h
	CVanguard* van = new CVanguard();
	CVanguard* vanPos = CVanguard::Instance();
	van->Scale(1.4f, 1.4f, 1.4f);
	van->Position(0.0f, 900.0f, -2050.0f);
	AddTask(van);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// �����l�_ : 190.0f, 130.0f.0f, 269.0f
	// ���Ԓn�_ : 0.0f, 320.0f, -1050.0f
	// �{�X�O	: 0.0f, 430.0f, -1890.0f
	// �S�[���t��:	-367.0f, 395.0f, -2040.0f
	// �Ή����ˊ�̑O : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(190.0f, 140.0f, 269.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 180.0f, 0.0f);
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
	mainCamera->AddCollider(mpPlainsStageField->GetWallCol());

}

// �X�e�[�W�j��
void CStage3::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpPlainsStageField->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}