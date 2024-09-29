#include "CStage1.h"
#include "COneShotFloorField.h"
#include "COneShotFallCol.h"
#include "CStageSky.h"
#include "CPlayer.h"
#include "CNumberFloor1.h"
#include "CNumberFloor2.h"
#include "CNumberFloor3.h"
#include "CCircleNbFlRight1.h"
#include "CCircleNbFlRight2.h"
#include "CCircleNbFlRight3.h"
#include "CCircleNbFlLeft1.h"
#include "CCircleNbFlLeft2.h"
#include "CCircleNbFlLeft3.h"
#include "CMoveToNbFl1.h"
#include "CMoveToNbFl2.h"
#include "CMoveToNbFl3.h"
#include "CRisingObject.h"
#include "CTreasureChest.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
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
#include "CCannon.h"
#include "CSpring.h"
#include "CAlwaysVerticalNeedle.h"

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
	// �X�e�[�W�̃x�[�X���f��
	CResourceManager::Load<CModel>("Stage1Base", "Field\\OneShotFloor\\StageBase.obj");
	// �X�e�[�W�̃��C�����f��
	CResourceManager::Load<CModel>("Stage1Line", "Field\\OneShotFloor\\Line.obj");
	// �X�e�[�W�̏��R���C�_�[
	CResourceManager::Load<CModel>("Stage1FloorCol", "Field\\OneShotFloor\\FloorCol.obj");
	// �X�e�[�W�̗����R���C�_�[
	CResourceManager::Load<CModel>("Stage1FallCol", "Field\\OneShotFloor\\FallCol.obj");
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("FieldCube", "GameGimmick\\Object\\cube.obj");

	// �M�~�b�N�֘A
	// ��]���鏰�̃��f��
	CResourceManager::Load<CModel>("Rotationg", "GameGimmick\\Gimmick\\Rotate\\Rotationg.obj");
	// ��]���鏰�̃R���C�_�[
	CResourceManager::Load<CModel>("RotationgCol", "GameGimmick\\Gimmick\\Rotate\\RotationgCol.obj");
	// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number0", "GameGimmick\\Gimmick\\NumberFloor\\number0.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number1", "GameGimmick\\Gimmick\\NumberFloor\\number1.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2", "GameGimmick\\Gimmick\\NumberFloor\\number2.obj");
	// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3", "GameGimmick\\Gimmick\\NumberFloor\\number3.obj");
	// ��
	//CResourceManager::Load<CModel>("TreasureChest", "GameGimmick\\Gimmick\\TreasureChest.obj");
	// // ��(�W)
	//CResourceManager::Load<CModel>("TreasureChestTwo", "GameGimmick\\Gimmick\\TreasureChestTwo.obj");
	// // ��(�W�R���C�_�[)
	//CResourceManager::Load<CModel>("TreasureChestCol", "GameGimmick\\Gimmick\\TreasureChest(FloorCol).obj");
	// // ��(�ǃR���C�_�[)
	//CResourceManager::Load<CModel>("TreasureChestWallCol", "GameGimmick\\Gimmick\\TreasureChest(WallCol).obj");
	// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("FlamethrowerModel", "GameGimmick\\Gimmick\\Flame\\Flamethrower(foundation).obj");
	// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("FlamethrowerTank", "GameGimmick\\Gimmick\\Flame\\Flamethrower(tank).obj");
	// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("FlamethrowerCol", "GameGimmick\\Gimmick\\Flame\\Flamethrower(WallCol).obj");
	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint", "GameGimmick\\Gimmick\\SaveFlag\\SavePoint.obj");
	// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalPost", "GameGimmick\\Gimmick\\Goal\\GoalPost.obj");
	// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("GoalCube", "GameGimmick\\Gimmick\\Goal\\GoalCube.obj");
	//// �j���f��(�㉺)
	//CResourceManager::Load<CModel>("Needle", "GameGimmick\\Gimmick\\Needle\\NeedleObject(needle).obj");
	//// �j���f���R���C�_�[(�㉺)
	//CResourceManager::Load<CModel>("NeedleCol", "GameGimmick\\Gimmick\\Needle\\NeedleObjectCol.obj");
	//// �j�x�[�X���f��(�㉺)
	//CResourceManager::Load<CModel>("NeedleBase", "GameGimmick\\Gimmick\\Needle\\NeedleObject(base).obj");
	//// �j�x�[�X�R���C�_�[(�㉺)
	//CResourceManager::Load<CModel>("NeedleBaseCol", "GameGimmick\\Gimmick\\Needle\\NeedleObjectBaseCol.obj");
	//// �j���f��(���E)
	//CResourceManager::Load<CModel>("NeedleLeftRight", "GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Needle).obj");
	//// �j���f���R���C�_�[(���E)
	//CResourceManager::Load<CModel>("NeedleColLeftRight", "GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(NeedleCol).obj");
	//// �j�x�[�X���f��(���E)
	//CResourceManager::Load<CModel>("NeedleBaseLeftRight", "GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(Base).obj");
	//// �j�x�[�X�R���C�_�[(���E)
	//CResourceManager::Load<CModel>("NeedleBaseColLeftRight", "GameGimmick\\Gimmick\\Needle\\NeedleObjLeftRight(BaseCol).obj");
	// ��C�y�䃂�f��
	CResourceManager::Load<CModel>("CannonFound", "GameGimmick\\Gimmick\\Cannon\\CannonFoundations.obj");
	// ��C
	CResourceManager::Load<CModel>("Cannon", "GameGimmick\\Gimmick\\Cannon\\Cannon.obj");
	// ��C�ʃ��f��
	CResourceManager::Load<CModel>("CannonBall", "GameGimmick\\Gimmick\\Cannon\\CannonBall.obj");
	// �o�l���f��(��ƃo�l)
	CResourceManager::Load<CModel>("Spring", "GameGimmick\\Gimmick\\Jump\\Spring.obj");
	// �o�l���f��(��)
	CResourceManager::Load<CModel>("SpringLower", "GameGimmick\\Gimmick\\Jump\\SpringLower.obj");
	// �o�l�R���C�_�[���f��
	CResourceManager::Load<CModel>("SpringCol", "GameGimmick\\Gimmick\\Jump\\SpringCol.obj");
	// �펞�o�Ă���j���f��
	CResourceManager::Load<CModel>("AlwaysNeedle", "GameGimmick\\Gimmick\\Needle\\Always\\AlwaysNeedleBase.obj");
	// �펞�o�Ă���j���f���̃R���C�_�[
	CResourceManager::Load<CModel>("AlwaysNeedleBaseCol", "GameGimmick\\Gimmick\\Needle\\Always\\AlwaysNeedleBaseCol.obj");
	// �펞�o�Ă���j���f���̐j�R���C�_�[
	CResourceManager::Load<CModel>("AlwaysNeedleCol", "GameGimmick\\Gimmick\\Needle\\Always\\AlwaysNeedleBaseNeedleCol.obj");
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// �A�C�e���֘A
	// �u���[���_�����f��
	CResourceManager::Load<CModel>("BlueMedal", "Item\\BlueMedal\\Bluemedal.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.0f, 0.0f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	// �t�B�[���h
	mpField = new COneShotFloorField();
	mpField->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpField);
	// �����R���C�_�[
	mpFallCol = new COneShotFallCol();
	mpFallCol->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFallCol);

	//// ��
	//mpSky = new CStageSky();
	//mpSky->Scale(150.0f, 150.0f, 150.0f);
	//AddTask(mpSky);

	// �Z�[�u�|�C���g1
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(26.0f, 5.0f, 390.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);
	// �Z�[�u�|�C���g2
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(26.0f, 5.0f, 673.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint2->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 1; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 0) xPos = 26.0f;

		// Y���̈ʒu��ݒ�
		float yPos = 0.0f;
		if (i == 0) yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0)   zPos = 340.0f;
		
		// X���̃X�P�[���l��ݒ�
		float xScale = 3.0f;
		
		// Z���̃X�P�[���l��ݒ�
		float zScale = 3.0f;
	
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloor1* numberfloor1 = new CNumberFloor1
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 2.0f, zScale),
			CVector(0.0f, 45.0f, 0.0f)
		);

		AddTask(numberfloor1); // �^�X�N�ɒǉ�
	}

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 2; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 0) xPos = 75.0f;
		if (i == 1) xPos = -23.0f;

		// Y���̈ʒu��ݒ�
		float yPos = 0.0f;
		if (i == 0) yPos = 0.0f;
		if (i == 1) yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0) zPos = 305.0f;
		if (i == 1) zPos = 305.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 3.0f;

		// Z���̃X�P�[���l��ݒ�
		float zScale = 3.0f;
		
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloor2* numberfloor2 = new CNumberFloor2
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 2.0f, zScale),
			CVector(0.0f, 45.0f, 0.0f)
		);

		AddTask(numberfloor2); // �^�X�N�ɒǉ�
	}

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 6; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 0) xPos = 26.0f;
		if (i == 1) xPos = 26.0f;
		// �����[�g
		if (i == 2) xPos = 95.0f;
		if (i == 3) xPos = 143.0f;
		if (i == 4) xPos = 173.0f;
		if (i == 5) xPos = 240.0f;
		
		// Y���̈ʒu��ݒ�
		float yPos = 0.0f;
		if (i == 0) yPos = -35.0f;
		if (i == 1) yPos = 5.0f;
		// �����[�g
		if (i == 2) yPos = 0.0f;
		if (i == 3) yPos = 0.0f;
		if (i == 4) yPos = 0.0f;
		if (i == 5) yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0)   zPos = 26.0f;
		if (i == 1)   zPos = 630.0f;
		// �����[�g
		if (i == 2)   zPos = 720.0f;
		if (i == 3)   zPos = 770.0f;
		if (i == 4)   zPos = 820.0f;
		if (i == 5)   zPos = 1100.0f;
		
		// X���̃X�P�[���l��ݒ�
		float xScale = 3.0f;
		if (i == 5) xScale = 5.0f;

		// Z���̃X�P�[���l��ݒ�
		float zScale = 3.0f;
		if (i == 5) zScale = 5.0f;

		// Y���̉�]�l��ݒ�
		float yRotate = 45.0f;
		if (i == 2) yRotate = 30.0f;
		if (i == 3) yRotate = 38.0f;
		if (i == 4) yRotate = 45.0f;
		
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloor3* numberfloor3 = new CNumberFloor3
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 2.0f, zScale),
			CVector(0.0f, yRotate, 0.0f)
		);

		AddTask(numberfloor3); // �^�X�N�ɒǉ�
	}

	// ������(�E�~��])
	CCircleNbFlRight3* floor3right1 = new CCircleNbFlRight3
	(
		CVector(26.0f, -3.0f, 490.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 35.0f, 35.0f,
		true
	);
	AddTask(floor3right1);

	// ������(���~��])
	CCircleNbFlLeft3* floor3left1 = new CCircleNbFlLeft3
	(
		CVector(220.0f, -5.0f, 927.0f),
		CVector(3.0f, 3.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 30.0f,
		true
	);
	AddTask(floor3left1);

	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl3* mn3f1 = new CMoveToNbFl3
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		5.0f
	);
	mn3f1->SetReturnRoute(false);
	mn3f1->AddMovePoint(CVector(-37.0f, 0.0f, 473.0f), 9.0f);
	mn3f1->AddMovePoint(CVector(-37.0f, 0.0f, 640.0f), 9.0f);
	AddTask(mn3f1);

	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl3* mn3f2 = new CMoveToNbFl3
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		5.0f
	);
	mn3f2->SetReturnRoute(false);
	mn3f2->AddMovePoint(CVector(90.0f, 0.0f, 640.0f), 9.0f);
	mn3f2->AddMovePoint(CVector(90.0f, 0.0f, 473.0f), 9.0f);
	AddTask(mn3f2);

	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl3* mn3f4 = new CMoveToNbFl3
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		5.0f
	);
	mn3f4->SetReturnRoute(false);
	mn3f4->AddMovePoint(CVector(133.0f, 0.0f, 1021.0f), 5.0f);
	mn3f4->AddMovePoint(CVector(319.0f, 0.0f, 1021.0f), 5.0f);
	AddTask(mn3f4);

	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl3* mn3f5 = new CMoveToNbFl3
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		5.0f
	);
	mn3f5->SetReturnRoute(false);
	mn3f5->AddMovePoint(CVector(319.0f, 0.0f, 1164.0f), 5.0f);
	mn3f5->AddMovePoint(CVector(133.0f, 0.0f, 1164.0f), 5.0f);
	AddTask(mn3f5);

	// �펞�o�Ă���j���f��
	CAlwaysVerticalNeedle* alwaysNeedle1 = new CAlwaysVerticalNeedle
	(
		CVector(26.0f, 7.0f, 580.0f),
		CVector(3.0f, 3.0f, 3.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(alwaysNeedle1);

	// �펞�o�Ă���j���f��
	CAlwaysVerticalNeedle* alwaysNeedle2 = new CAlwaysVerticalNeedle
	(
		CVector(90.0f, 7.0f, 640.0f),
		CVector(3.0f, 3.0f, 3.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(alwaysNeedle2);

	// �펞�o�Ă���j���f��
	CAlwaysVerticalNeedle* alwaysNeedle3 = new CAlwaysVerticalNeedle
	(
		CVector(-37.0f, 7.0f, 640.0f),
		CVector(3.0f, 3.0f, 3.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(alwaysNeedle3);

	// �o�l(��ƃo�l)
	CSpring* spring1 = new CSpring
	(
		CVector(26.0f, -26.0f, 114.0f),
		CVector(1.8f, 1.8f, 1.8f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(spring1);
	// �o�l(��)
	CSpringLower* springlower1 = new CSpringLower
	(
		CVector(26.0f, -26.0f, 114.0f),
		CVector(1.8f, 1.8f, 1.8f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(springlower1);

	//// ��C
	//CCannon* cannon = new CCannon
	//(
	//	CVector(0.0f, 25.0f, 325.0f),
	//	CVector(3.0f, 3.0f, 3.0f),
	//	CVector(0.0f, 180.0f, 0.0f)
	//);
	//AddTask(cannon);
	//// ��C�y��
	//CCannonFoundations* cannonfound = new CCannonFoundations
	//(
	//	CVector(0.0f, 25.0f, 325.0f),
	//	CVector(3.0f, 3.0f, 3.0f),
	//	CVector(0.0f, 180.0f, 0.0f)
	//);
	//AddTask(cannonfound);


	//CNumberFloor1* floor1 = new CNumberFloor1
	//(
	//	CVector(-60.0f, 0.0f, -70.0f),
	//	CVector(4.0f, 3.0f, 4.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(floor1);

	//CNumberFloor2* floor2 = new CNumberFloor2
	//(
	//	CVector(-120.0f, 0.0f, -70.0f),
	//	CVector(4.0f, 3.0f, 4.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(floor2);

	//CNumberFloor3* floor3 = new CNumberFloor3
	//(
	//	CVector(-180.0f, 0.0f, -70.0f),
	//	CVector(4.0f, 3.0f, 4.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(floor3);

	//// �����Ɖ�]���郂�f��1
	//CRotationg* rotationg = new CRotationg
	//(
	//	CVector(60.0f, 12.0f, -70.0f),
	//	CVector(10.0f, 10.0f, 10.0f),
	//	1.0f
	//);
	//AddTask(rotationg);

	//// ���Ԓl�_
	//CRisingObject* rising1 = new CRisingObject
	//(
	//	CVector(0.0f, 12.0f, 325.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rising1);

	//// �S�[���l�_
	//CRisingObject* rising2 = new CRisingObject
	//(
	//	CVector(0.0f, 12.0f, 670.0f),
	//	CVector(2.0f, 1.0f, 2.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(rising2);

	//// �S�[���|�X�g0.0f, 10.0f, 720.0f
	//CGoalObject* goal = new CGoalObject
	//(
	//	CVector(0.0f, 0.5f, 669.0f),
	//	CVector(2.0f, 2.0f, 2.0f),
	//	CVector(0.0f, 90.0f, 0.0f)
	//);
	//AddTask(goal);

	//// �Z�[�u�|�C���g
	//CSavePoint1* savepoint1 = new CSavePoint1
	//(
	//	CVector(0.0f, 15.0f, 325.0f),
	//	CVector(8.0f, 8.0f, 8.0f),
	//	CVector(0.0f, 10.0f, 0.0f)
	//);
	//savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	//AddTask(savepoint1);

	//// �j���f��1
	//CNeedleUpDown* needle1 = new CNeedleUpDown(
	//	CVector(0.0f, 10.0f, 450.0f),
	//	CVector(20.0f, 20.0f, 20.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	3.6f,
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needle1);
	//// �j���f���x�[�X1
	//CNeedleUpDownBase* needlebase1 = new CNeedleUpDownBase(
	//	CVector(0.0f, 10.0f, 450.0f),
	//	CVector(20.0f, 20.0f, 20.0f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer);
	//AddTask(needlebase1);

	////// �j���f��1
	////CNeedleLeftRight* needle1 = new CNeedleLeftRight(
	////	CVector(-130.0f, 280.0f, -1080.0f),
	////	CVector(10.0f, 10.0f, 10.0f),
	////	CVector(0.0f, 0.0f, 0.0f),
	////	ETag::ePlayer, ELayer::ePlayer);
	////AddTask(needle1);
	////// �j���f���x�[�X1
	////CNeedleLeftRightBase* needlebase1 = new CNeedleLeftRightBase(
	////	CVector(-130.0f, 280.0f, -1080.0f),
	////	CVector(10.0f, 10.0f, 10.0f),
	////	CVector(0.0f, 0.0f, 0.0f),
	////	ETag::ePlayer, ELayer::ePlayer);
	////AddTask(needlebase1);
	//// �Ή����ˊ탂�f��
	//// ������
	//CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	//(
	//	CVector(-100.0f, 15.0f, 140.0f),
	//	CVector(2.0f, 2.0f, 2.0f),
	//	CVector(0.0f, -90.0f, 0.0f)
	//);
	//AddTask(flamethrower1);
	//// �Ή����ˊ�̓y��
	//CRisingObject* dodai = new CRisingObject
	//(
	//	CVector(-100.0f, 15.0f, 140.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(dodai);

	////// �Ή����ˊ탂�f��
	////// �E���� 
	////CFixedFlamethrower* flamethrower2 = new CFixedFlamethrower
	////(
	////	CVector(-100.0f, 15.0f, 625.0f),
	////	CVector(2.0f, 2.0f, 2.0f),
	////	CVector(0.0f, -90.0f, 0.0f)
	////);
	////AddTask(flamethrower2);
	////// �Ή����ˊ�̓y��
	////CRisingObject* dodai2 = new CRisingObject
	////(
	////	CVector(-100.0f, 15.0f, 625.0f),
	////	CVector(1.0f, 1.0f, 1.0f),
	////	ETag::ePlayer, ELayer::ePlayer
	////);
	////AddTask(dodai2);

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
	// �Z�[�u�|�C���g1 : 26.0f, 10.0f, 390.0f
	// �Z�[�u�|�C���g2 : 26.0f, 10.0f, 673.0f
	CVector playerPos = CVector(26.0f, 10.0f, 673.0f);
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

	//// �u���[���_�����쐬
	//CBlueMedal* medal1 = new CBlueMedal
	//(
	//	CVector(70.0f, 22.0f, 325.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(medal1);
	//medal1->SetEvent(bmEvent);
	//bmEvent->AddBlueMedal(medal1);

	//CBlueMedal* medal2 = new CBlueMedal
	//(
	//	CVector(-70.0f, 22.0f, 455.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(medal2);
	//medal2->SetEvent(bmEvent);
	//bmEvent->AddBlueMedal(medal2);

	//CBlueMedal* medal3 = new CBlueMedal
	//(
	//	CVector(70.0f, 22.0f, 455.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(medal3);
	//medal3->SetEvent(bmEvent);
	//bmEvent->AddBlueMedal(medal3);

	//CBlueMedal* medal4 = new CBlueMedal
	//(
	//	CVector(0.0f, 22.0f, 130.0f),
	//	CVector(3.0f, 3.0f, 3.0f)
	//);
	//AddTask(medal4);
	//medal4->SetEvent(bmEvent);
	//bmEvent->AddBlueMedal(medal4);

	///////////////////////////////////////////////////////////////////////////

	////��Q���̕ǂ��쐬
	//CObstacleWall* wall = new CObstacleWall
	//(
	//	CVector(0.0f, 25.0f, 623.0f),
	//	CQuaternion(0.0f, 0.0f, 0.0f),
	//	CVector(4.0f, 20.0f, 0.2f)
	//);
	//AddTask(wall);
	//wall->SetEvent(bmEvent);
	//bmEvent->SetObstacle(wall);
}

// �X�e�[�W�j��
void CStage1::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	//CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	CStageBase::Unload();
}