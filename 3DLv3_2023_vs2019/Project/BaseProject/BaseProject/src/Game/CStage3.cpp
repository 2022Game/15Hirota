#include "CStage3.h"
#include "CPlayer.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CStageSky.h"
#include "CCamera.h"
#include "CStageTime.h"
#include "CGameCamera.h"
#include "CEnemyManager.h"
#include "CInput.h"
#include "CFinalStageField.h"
#include "CFinalStageFallCol.h"
#include "CNumberFloor1.h"
#include "CNumberFloor2.h"
#include "CNumberFloor3.h"
#include "CNbFlMove2.h"
#include "CCircleNbFlLeft2.h"
#include "CCircleNbFlRight2.h"
#include "CMoveToNbFl1.h"
#include "CHorizontalCannon.h"
#include "CCannon.h"
#include "CPowerfulCannon.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoMoveTo.h"
#include "CRingBeamer.h"
#include "CFixedFlamethrower.h"
#include "CRotateFloorGimmick.h"
#include "CRotateFloorGimmickOpposition.h"
#include "CRotateFloorTimeGimmick.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CGoalObject.h"
#include "CRengaBlock.h"
#include "CHatenaBlock.h"
#include "CPicoChan.h"
#include "CSoldier.h"
#include "CVanguard.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"

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
	CResourceManager::Load<CModel>("StageSky",		"Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("Stage3Base",	"Field\\Final Stage\\Base.obj");
	// �X�e�[�W�̃��C�����f��
	CResourceManager::Load<CModel>("Stage3Line",	"Field\\Final Stage\\Line.obj");
	// ���̃R���C�_�[
	CResourceManager::Load<CModel>("Stage3FloorCol","Field\\Final Stage\\FloorCol.obj");
	// �ǂ̃R���C�_�[
	//CResourceManager::Load<CModel>("WallCol",		"Field\\GameStage(Worlds_3)\\GameStage_1(wallCol).obj");
	// ��������R���C�_�[
	CResourceManager::Load<CModel>("Stage3FallCol", "Field\\Final Stage\\FallCol.obj");

	// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Number0", "GameGimmick\\Gimmick\\NumberFloor\\number0.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number1", "GameGimmick\\Gimmick\\NumberFloor\\number1.obj");
	// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2", "GameGimmick\\Gimmick\\NumberFloor\\number2.obj");
	// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number3", "GameGimmick\\Gimmick\\NumberFloor\\number3.obj");

	// ��C�y�䃂�f��
	CResourceManager::Load<CModel>("CannonFound", "GameGimmick\\Gimmick\\Cannon\\CannonFoundations.obj");
	// ������C�y�䃂�f��
	CResourceManager::Load<CModel>("HorizontalCannonFound", "GameGimmick\\Gimmick\\Cannon\\CannonFoundation(Horizontal).obj");
	// ��C
	CResourceManager::Load<CModel>("Cannon", "GameGimmick\\Gimmick\\Cannon\\Cannon.obj");
	// ������C
	CResourceManager::Load<CModel>("HorizontalCannon", "GameGimmick\\Gimmick\\Cannon\\HorizontalCannon.obj");
	// ��C�ʃ��f��
	CResourceManager::Load<CModel>("CannonBall", "GameGimmick\\Gimmick\\Cannon\\CannonBall.obj");

	// �Ή����ˊ�(�^���N)
	CResourceManager::Load<CModel>("", "");	
	// �Ή����ˊ�(�y��)
	CResourceManager::Load<CModel>("", "");
	// �Ή����ˊ�(�R���C�_�[)
	CResourceManager::Load<CModel>("", "");

	// ���˂�L�m�R���f��							    
	CResourceManager::Load<CModel>("JumpingKinoko", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// ���˂�L�m�R���f��2						    
	CResourceManager::Load<CModel>("JumpingKinoko2Color", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base_2Color).obj");
	// ���˂�L�m�R���f��3						    
	CResourceManager::Load<CModel>("JumpingKinoko3Color", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Base_3Color).obj");
	// ���˂�L�m�R�R���C�_�[								 
	CResourceManager::Load<CModel>("JumpingKinokoCol", "GameGimmick\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1960784f, 0.6f, 0.8f, 1.0f);

	CInput::ShowCursor(false);

	//// �t�B�[���h�֘A /////////////////////////////////////////////////////////////////

	// �t�B�[���h
	mpFinalStage = new CFinalStageField();
	mpFinalStage->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStage);
	// �����R���C�_�[
	mpFinalStageFallCol = new CFinalStageFallCol();
	mpFinalStageFallCol->Scale(1.0f, 1.0f, 1.0f);
	AddTask(mpFinalStageFallCol);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 1; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		//if (i == 0) xPos = 26.0f;

		// �����[�g
		//if (i == 2) xPos = 95.0f;
		
		// �S�[���t��
		//if (i == 7) xPos = 26.0f;


		// Y���̈ʒu��ݒ�
		float yPos = -2.0f;
		//if (i == 0) yPos = -35.0f;
		
		// �����[�g
		//if (i == 2) yPos = 0.0f;
		
		// �S�[���t��
		//if (i == 7) yPos = 5.0f;		

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0) zPos = 80.0f;

		// �����[�g
		//if (i == 2) zPos = 720.0f;

		// �S�[���t��
		//if (i == 7) zPos = 1450.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 2.0f;
		//if (i == 5) xScale = 5.0f;

		// Z���̃X�P�[���l��ݒ�
		float zScale = 2.0f;
		//if (i == 5) zScale = 5.0f;

		// Y���̉�]�l��ݒ�
		float yRotate = 45.0f;
		//if (i == 2) yRotate = 30.0f;

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
	CCircleNbFlRight2* floor2right1 = new CCircleNbFlRight2
	(
		CVector(-60.0f, -15.0f, 153.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		true
	);
	AddTask(floor2right1);

	// ������(���~��])
	CCircleNbFlLeft2* floor2left2 = new CCircleNbFlLeft2
	(
		CVector(63.0f, -15.0f, 153.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		false
	);
	AddTask(floor2left2);


	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl1* mn1f1 = new CMoveToNbFl1
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		2.0f
	);
	mn1f1->SetReturnRoute(false);
	mn1f1->AddMovePoint(CVector(78.0f, -15.0f, 237), 3.0f);
	mn1f1->AddMovePoint(CVector(-78.0f, -15.0f, 237), 3.0f);
	AddTask(mn1f1);

	// ��C(�h����C�̒e)
	CHorizontalCannon* cannon1 = new CHorizontalCannon
	(
		CVector(-178.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(cannon1);
	// ��C�y��
	CCannonFoundationsHorizontal* cannonfound1 = new CCannonFoundationsHorizontal
	(
		CVector(-178.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(cannonfound1);

	// ��C(�h����C�̒e)
	CHorizontalCannon* cannon2 = new CHorizontalCannon
	(
		CVector(173.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(cannon2);
	// ��C�y��
	CCannonFoundationsHorizontal* cannonfound2 = new CCannonFoundationsHorizontal
	(
		CVector(173.0f, 8.0f, 153.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(cannonfound2);

	// �W�����v�L�m�R
	CJumpingKinoko* jumpkinoko = new CJumpingKinoko
	(
		CVector(0.0f, -2.0f, 650.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f)
	);

	AddTask(jumpkinoko);

	
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

	// �s�R�����
	CPicoChan* pico = new CPicoChan();
	pico->Position(0.0f, 8.0f, 453.0f);
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->SetCenterPoint(CVector(0.0f, 0.0f, 453.0f), 30.0f);
	AddTask(pico);
	
	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	// �����l�_ : 0.0f, 10.0f, 0.0f
	// ���Ԓn�_ : 0.0f, 320.0f, -1050.0f
	// �{�X�O	: 0.0f, 430.0f, -1890.0f
	// �S�[���t��:	-367.0f, 395.0f, -2040.0f
	// �Ή����ˊ�̑O : -207.0f, 126.0f, -912.0f
	CVector playerPos = CVector(0.0f, 15.0f, 0.0f);
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
	//mainCamera->AddCollider(mpPlainsStageField->GetWallCol());

}

// �X�e�[�W�j��
void CStage3::Unload()
{
	// �J��������Փ˂���R���C�_�[����菜��
	CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpPlainsStageField->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}