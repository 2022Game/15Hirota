#include "CStage1.h"
#include "COneShotFloorField.h"
#include "CStageSky.h"
#include "CPlayer.h"
#include "CNumberFloor1.h"
#include "CNumberFloor2.h"
#include "CNumberFloor3.h"
#include "CRisingObject.h"
#include "CTreasureChest.h"
#include "CSavePoint1.h"
#include "CFixedFlamethrower.h"
#include "CGoalObject.h"
#include "CBlueMedalEvent.h"
#include "CBlueMedal.h"
#include "CObstacleWall.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CNeedleUpDown.h"
#include "CNeedleLeftRight.h"
#include "CInput.h"
#include "CRotationg.h"

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
	// �I�u�W�F�N�g�֘A
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCube", "Field\\Object\\cube.obj");
	// ��������R���C�_�[
	CResourceManager::Load<CModel>("NumberFallCol", "Field\\FallCol.obj");

	// �M�~�b�N�֘A
	// ��]���鏰�̃��f��
	CResourceManager::Load<CModel>("Rotationg", "Field\\Gimmick\\Rotate\\Rotationg.obj");
	// ��]���鏰�̃R���C�_�[
	CResourceManager::Load<CModel>("RotationgCol", "Field\\Gimmick\\Rotate\\RotationgCol.obj");
	// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number0", "Field\\Object\\number0.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number1", "Field\\Object\\number1.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2", "Field\\Object\\number2.obj");
	// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");
	// ��
	//CResourceManager::Load<CModel>("TreasureChest", "Field\\Gimmick\\TreasureChest.obj");
	// // ��(�W)
	//CResourceManager::Load<CModel>("TreasureChestTwo", "Field\\Gimmick\\TreasureChestTwo.obj");
	// // ��(�W�R���C�_�[)
	//CResourceManager::Load<CModel>("TreasureChestCol", "Field\\Gimmick\\TreasureChest(FloorCol).obj");
	// // ��(�ǃR���C�_�[)
	//CResourceManager::Load<CModel>("TreasureChestWallCol", "Field\\Gimmick\\TreasureChest(WallCol).obj");
	// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("FlamethrowerModel", "Field\\Gimmick\\Fire\\Flamethrower(foundation).obj");
	// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("FlamethrowerTank", "Field\\Gimmick\\Fire\\Flamethrower(tank).obj");
	// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("FlamethrowerCol", "Field\\Gimmick\\Fire\\Flamethrower(WallCol).obj");
	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint", "Field\\Gimmick\\SavePoint.obj");
	// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalPost", "Field\\Object\\GoalPost.obj");
	// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("GoalCube", "Field\\Object\\GoalCube.obj");
	// �j���f��(�㉺)
	CResourceManager::Load<CModel>("Needle", "Field\\Gimmick\\Needle\\NeedleObject(needle).obj");
	// �j���f���R���C�_�[(�㉺)
	CResourceManager::Load<CModel>("NeedleCol", "Field\\Gimmick\\Needle\\NeedleObjectCol.obj");
	// �j�x�[�X���f��(�㉺)
	CResourceManager::Load<CModel>("NeedleBase", "Field\\Gimmick\\Needle\\NeedleObject(base).obj");
	// �j�x�[�X�R���C�_�[(�㉺)
	CResourceManager::Load<CModel>("NeedleBaseCol", "Field\\Gimmick\\Needle\\NeedleObjectBaseCol.obj");
	// �j���f��(���E)
	CResourceManager::Load<CModel>("NeedleLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(Needle).obj");
	// �j���f���R���C�_�[(���E)
	CResourceManager::Load<CModel>("NeedleColLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(NeedleCol).obj");
	// �j�x�[�X���f��(���E)
	CResourceManager::Load<CModel>("NeedleBaseLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(Base).obj");
	// �j�x�[�X�R���C�_�[(���E)
	CResourceManager::Load<CModel>("NeedleBaseColLeftRight", "Field\\Gimmick\\Needle\\NeedleObjLeftRight(BaseCol).obj");
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// �A�C�e���֘A
	// �u���[���_�����f��
	CResourceManager::Load<CModel>("BlueMedal", "Field\\Object\\Bluemedal.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	CInput::ShowCursor(false);

	COneShotFloorField* field = new COneShotFloorField();
	field->Scale(1.0f, 1.0f, 1.0f);
	field->Position(0.0f, -200.0f, 0.0f);
	AddTask(field);

	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	// �����l�_
	CRisingObject* rising = new CRisingObject
	(
		CVector(0.0f, 12.0f, -70.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising);


	CNumberFloor1* floor1 = new CNumberFloor1
	(
		CVector(-60.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor1);

	CNumberFloor2* floor2 = new CNumberFloor2
	(
		CVector(-120.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor2);

	CNumberFloor3* floor3 = new CNumberFloor3
	(
		CVector(-180.0f, 0.0f, -70.0f),
		CVector(4.0f, 3.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(floor3);

	// �����Ɖ�]���郂�f��1
	CRotationg* rotationg = new CRotationg
	(
		CVector(60.0f, 12.0f, -70.0f),
		CVector(10.0f, 10.0f, 10.0f),
		1.0f
	);
	AddTask(rotationg);

	// ���Ԓl�_
	CRisingObject* rising1 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 325.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising1);

	// �S�[���l�_
	CRisingObject* rising2 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 670.0f),
		CVector(2.0f, 1.0f, 2.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising2);

	// �S�[���|�X�g0.0f, 10.0f, 720.0f
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.5f, 669.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 14; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 5) xPos = 70.0f;
		if (i == 6) xPos = -70.0f;
		if (i == 7) xPos = 70.0f;
		if (i == 8) xPos = -70.0f;
		if (i == 9) xPos = 70.0f;
		if (i == 10) xPos = -70.0f;
		if (i == 11) xPos = 50.0f;
		if (i == 12) xPos = -50.0f;
		if (i == 13) xPos = 0.0f;

		// Y���̈ʒu��ݒ�
		float yPos = i * 0.0f;
		if (i == 4) yPos = 2.5f;

		// Z���̈ʒu��ݒ�
		float zPos = i * 65.0f;
		if (i == 5)   zPos = 5 * 65.0f;
		if (i == 6)   zPos = 5 * 65.0f;
		if (i == 7)   zPos = 6 * 65.0f;
		if (i == 8)   zPos = 6 * 65.0f;
		if (i == 9)   zPos = 7 * 65.0f;
		if (i == 10)  zPos = 7 * 65.0f;
		if (i == 11)  zPos = 8 * 65.0f;
		if (i == 12)  zPos = 8 * 65.0f;
		if (i == 13)  zPos = 9 * 65.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 4.0f;
		if (i == 2) xScale = 6.0f;
		if (i == 13)xScale = 6.0f;


		// Z���̃X�P�[���l��ݒ�
		float zScale = 4.0f;
		if (i == 2) zScale = 6.0f;
		if (i == 13) zScale = 6.0f;

		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloor1* numberfloor1 = new CNumberFloor1
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 3.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f)
		);

		AddTask(numberfloor1); // �^�X�N�ɒǉ�
	}

	// �Z�[�u�|�C���g
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 15.0f, 325.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// �j���f��1
	CNeedleUpDown* needle1 = new CNeedleUpDown(
		CVector(0.0f, 10.0f, 450.0f),
		CVector(20.0f, 20.0f, 20.0f),
		CVector(0.0f, 0.0f, 0.0f),
		3.6f,
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(needle1);
	// �j���f���x�[�X1
	CNeedleUpDownBase* needlebase1 = new CNeedleUpDownBase(
		CVector(0.0f, 10.0f, 450.0f),
		CVector(20.0f, 20.0f, 20.0f),
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
	// �Ή����ˊ탂�f��
	// ������
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(flamethrower1);
	// �Ή����ˊ�̓y��
	CRisingObject* dodai = new CRisingObject
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai);

	// �Ή����ˊ탂�f��
	// �E���� 
	CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 625.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(flamethrower2);
	// �Ή����ˊ�̓y��
	CRisingObject* dodai2 = new CRisingObject
	(
		CVector(-100.0f, 15.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai2);

	CMeat1* meat1 = new CMeat1
	(
		CVector(0.0f, 45.0f, 134.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	AddTask(meat1);
	meat1->SetMeatNumber(1);

	CMeat2* meat2 = new CMeat2
	(
		CVector(70.0f, 25.0f, 390.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(-70.0f, 25.0f, 390.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);


	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 25.5f, -70.0f);	//197.0f,1235.0f,279.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);
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
	//mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());



	// �u���[���_���l���C�x���g�𐶐�
	CBlueMedalEvent* bmEvent = new CBlueMedalEvent();
	AddTask(bmEvent);

	///////////////////////////////////////////////////////////////////////////

	// �u���[���_�����쐬
	CBlueMedal* medal1 = new CBlueMedal
	(
		CVector(70.0f, 22.0f, 325.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal1);
	medal1->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal1);

	CBlueMedal* medal2 = new CBlueMedal
	(
		CVector(-70.0f, 22.0f, 455.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal2);
	medal2->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal2);

	CBlueMedal* medal3 = new CBlueMedal
	(
		CVector(70.0f, 22.0f, 455.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal3);
	medal3->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal3);

	CBlueMedal* medal4 = new CBlueMedal
	(
		CVector(0.0f, 22.0f, 130.0f),
		CVector(3.0f, 3.0f, 3.0f)
	);
	AddTask(medal4);
	medal4->SetEvent(bmEvent);
	bmEvent->AddBlueMedal(medal4);

	///////////////////////////////////////////////////////////////////////////

	//��Q���̕ǂ��쐬
	CObstacleWall* wall = new CObstacleWall
	(
		CVector(0.0f, 25.0f, 623.0f),
		CQuaternion(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 20.0f, 0.2f)
	);
	AddTask(wall);
	wall->SetEvent(bmEvent);
	bmEvent->SetObstacle(wall);
}

// �X�e�[�W�j��
void CStage1::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	//CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	CStageBase::Unload();
}
