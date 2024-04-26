#include "CStage3.h"
#include "CNumberField.h"
#include "CPlayer.h"
#include "CNumberFloor1.h"
#include "CNumberFloorOnce.h"
#include "CRisingObject.h"
#include "CTreasureChest.h"
#include "CSavePoint.h"
#include "CFixedFlamethrower.h"
#include "CGoalObject.h"

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
	CResourceManager::Load<CModel>("NumberFallCol",			"Field\\FallCol.obj");							// ��������R���C�_�[

	// �M�~�b�N�֘A
	CResourceManager::Load<CModel>("Number0",				"Field\\Object\\number0.obj");					// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number1",				"Field\\Object\\number1.obj");					// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2",				"Field\\Object\\number2.obj");					// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3",				"Field\\Object\\number3.obj");					// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("FieldCube",				"Field\\Object\\cube.obj");						// �����̎l�p�̃��f��
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\TreasureChest.obj");			// ��
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\TreasureChestTwo.obj");		// ��(�W)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\TreasureChest(FloorCol).obj");	// ��(�W�R���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\TreasureChest(WallCol).obj");	// ��(�ǃR���C�_�[)
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");				// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("FlamethrowerModel",		"Field\\Gimmick\\Flamethrower(foundation).obj");// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("FlamethrowerTank",		"Field\\Gimmick\\Flamethrower(tank).obj");		// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("FlamethrowerCol",		"Field\\Gimmick\\Flamethrower(WallCol).obj");	// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("GoalPost",				"Field\\Object\\GoalPost.obj");					// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalCube",				"Field\\Object\\GoalCube.obj");					// �S�[���u���b�N���f��

	// �w�i�F�ݒ�
	System::SetClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	CNumberField* field = new CNumberField();
	field->Scale(1.0f, 1.0f, 1.0f);
	field->Position(0.0f, -190.0f, 0.0f);
	AddTask(field);

	// �����l�_
	CRisingObject* rising = new CRisingObject
	(
		CVector(0.0f, 12.0f, -70.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising);

	// ���Ԓl�_
	CRisingObject* rising1 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 350.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising1);

	// �S�[���l�_
	CRisingObject* rising2 = new CRisingObject
	(
		CVector(0.0f, 12.0f, 740.0f),
		CVector(2.0f, 1.0f, 2.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(rising2);

	// �S�[���|�X�g0.0f, 10.0f, 720.0f
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 4.5f, -50.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 14; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 5) xPos	=	70.0f;
		if (i == 6) xPos	= -	70.0f;
		if (i == 7) xPos	=	70.0f;
		if (i == 8) xPos	= -	70.0f;
		if (i == 9) xPos	=	70.0f;
		if (i == 10) xPos	= -	70.0f;
		if (i == 11) xPos	=	50.0f;
		if (i == 12) xPos	= -	50.0f;
		if (i == 13) xPos	=	 0.0f;
		
		// Y���̈ʒu��ݒ�
		float yPos = i * 0.0f;
		if (i == 4) yPos = 2.5f;

		// Z���̈ʒu��ݒ�
		float zPos = i * 70.0f;
		if (i == 5)   zPos = 5 * 70.0f;
		if (i == 6)   zPos = 5 * 70.0f;
		if (i == 7)   zPos = 6 * 70.0f;
		if (i == 8)   zPos = 6 * 70.0f;
		if (i == 9)   zPos = 7 * 70.0f;
		if (i == 10)  zPos = 7 * 70.0f;
		if (i == 11)  zPos = 8 * 70.0f;
		if (i == 12)  zPos = 8 * 70.0f;
		if (i == 13)  zPos = 9 * 70.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 4.0f;
		if (i == 2) xScale = 6.0f;
		if (i == 13)xScale = 6.0f;


		// Z���̃X�P�[���l��ݒ�
		float zScale = 4.0f;
		if (i == 2) zScale = 6.0f;
		if (i == 13) zScale = 6.0f;
		
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloorOnce* numberfloor = new CNumberFloorOnce
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 3.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);

		AddTask(numberfloor); // �^�X�N�ɒǉ�
	}

	// �Z�[�u�|�C���g
	CSavePoint* savepoint = new CSavePoint
	(
		CVector(0.0f, 15.0f, 350.0f),
		CVector(8.0f, 8.0f, 8.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint);


	// ��
	CTreasureChest* treasure = new CTreasureChest
	(
		CVector(0.0f, 18.0f, 779.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure);
	// �󔠊W
	CTreasureChestTwo* treasureTwo = new CTreasureChestTwo
	(
		CVector(0.0f, 20.8f, 779.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo);


	// �Ή����ˊ탂�f��
	// ������
	CFixedFlamethrower* flamethrower1 = new CFixedFlamethrower
	(
		CVector(-100.0f, 15.0f, 140.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
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
		CVector(-100.0f, 15.0f, 630.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(flamethrower2);
	// �Ή����ˊ�̓y��
	CRisingObject* dodai2 = new CRisingObject
(
		CVector(-100.0f, 15.0f, 630.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dodai2);


	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 14.5f, -70.0f);	//197.0f,1235.0f,279.0f
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);
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
	//mainCamera->AddCollider(mpField_Worlds_1->GetWallCol());
}

// �X�e�[�W�j��
void CStage3::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	//CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField_Worlds_1->GetWallCol());
	CStageBase::Unload();
}