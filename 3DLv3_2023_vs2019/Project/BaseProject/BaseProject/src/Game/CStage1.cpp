#include "CStage1.h"
#include "CDamageObject.h"
#include "CGoalObject.h"
#include "CStone1.h"
#include "CField.h"
#include "CSoldier.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CDisappearFloor.h"
#include "CYukari.h"
#include "CJumpingObject.h"
#include "CSignboard.h"
#include "CGameCamera.h"
#include "CFallingObjects.h"
#include "CRisingObject.h"
#include "CEnemyManager.h"
#include "CHatenaBlock.h"
#include "CRengaBlock.h"
#include "CNumberFloor1.h"
#include "CVanguard.h"


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
	CResourceManager::Load<CModel>("Field", "Field\\GameStage(1).obj");							// ��1��
	CResourceManager::Load<CModel>("FloorCol", "Field\\GameStageFloor(1).obj");					// ��1�ʂ̏�
	CResourceManager::Load<CModel>("WallCol", "Field\\GameStageWall(1).obj");					// ��1�ʂ̕�
	CResourceManager::Load<CModel>("EnemyWallCol", "Field\\GameStageEnemyWall(1).obj");			// ��1�ʂ̓G�̕�
	CResourceManager::Load<CModel>("GoalCube", "Field\\Object\\GoalCube.obj");					// �S�[���̓y��
	CResourceManager::Load<CModel>("GoalPost", "Field\\Object\\GoalPost.obj");					// �S�[���̃|�X�g
	CResourceManager::Load<CModel>("Stone1", "Field\\Object\\Stone1.obj");						// ��1
	CResourceManager::Load<CModel>("Tree1", "Field\\Object\\Tree1.obj");						// ��1
	CResourceManager::Load<CModel>("Signboard", "Field\\Object\\signboard.obj");				// �ŔI�u�W�F�N�g(�W�����v�q���g)
	CResourceManager::Load<CModel>("Number3", "Field\\Object\\number3.obj");					// �O�Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number2", "Field\\Object\\number2.obj");					// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number1", "Field\\Object\\number1.obj");					// ��Ԗڂ̏��u���b�N
	CResourceManager::Load<CModel>("Number0", "Field\\Object\\number0.obj");					// ��Ԗڂ̏�
	CResourceManager::Load<CModel>("Sky", "Field\\Sky.obj");									// ��̃I�u�W�F

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);


	// �t�B�[���h
	CField* field = new CField();
	AddTask(field);

	// �񐔐������f��
	CNumberFloor1* number = new CNumberFloor1(
		CVector(-100.0f, 1.0f, -430.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector numberPos = CVector(-100.0f, 1.0f, -430.0f);
	if (number != nullptr)
	{
		number->SetStartPosition(numberPos);
	}
	AddTask(number);

	//// �񐔐������f��
	//CNumberFloor1* number1 = new CNumberFloor1(
	//	CVector(-30.0f, 1.0f, -150.0f),
	//	CVector(2.0f, 2.0f, 2.0f),
	//	CVector(0.0f, -90.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//CVector numberPos1 = CVector(-30.0f, 1.0f, -150.0f);
	//if (number != nullptr)
	//{
	//	number1->SetStartPosition(numberPos1);
	//}
	//AddTask(number1);

	// �l�p���f��
	CDamageObject* floor = new CDamageObject(
		CVector(-20.0f, -20.0f, -340.0f), 
		CVector(5.5f, 1.0f, 3.25f), 
		CVector(0.0f, 0.0f, 0.0f), 
		5.0f);
	AddTask(floor);

	// �S�[���I�u�W�F�N�g
	CGoalObject* goal = new CGoalObject(
		CVector(20.0f, 95.0f, -450.0f),
		CVector(1.5f, 1.5f, 1.5f),
		CVector(0.0f, 90.0f, 0.0f));
	AddTask(goal);

	//// �S�[���I�u�W�F�N�g
	//CGoalObject* goal = new CGoalObject(
	//	CVector(0.0f, 0.0f, -100.0f),
	//	CVector(1.5f, 1.5f, 1.5f),
	//	CVector(0.0f, 90.0f, 0.0f));
	//AddTask(goal);

	// ��1
	CStone1* stone1 = new CStone1(
		CVector(-80.0f, 0.0f, -200.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f));
	AddTask(stone1);

	// �����鏰
	CDisappearFloor* dfloor = new CDisappearFloor
	(
		CVector(0.0f, 10.0f, -200.0f),
		CVector(0.5f, 2.0f, 0.5f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(dfloor);


	//// �W�����v���鏰
	//CJumpingObject* jump1 = new CJumpingObject
	//(
	//	CVector(-100.0f, 1.0f, -430.0f),
	//	CVector(0.5f, 0.5f, 0.5f),
	//	CVector(0.0f, 0.0f, 0.0f),
	//	ETag::ePlayer, ELayer::ePlayer
	//);
	//AddTask(jump1);

	// �Ŕ�		-380�͑Ί�
	CSignboard* board = new CSignboard
	(
		CVector(-50.0f, 1.0f, -300.0f),
		CVector(15.0f, 15.0f, 15.0f),
		CVector(0.0f, -30.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(board);

	// �������鏰
	CFallingObjects* fallobj = new CFallingObjects
	(
		CVector(20.0f, 95.0f, -500.0f),
		CVector(1.0f, 1.0f, 1.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector fallobjpos = CVector(20.0f, 95.0f, -500.0f);
	if (fallobj != nullptr)
	{
		fallobj->SetStartPosition(fallobjpos);
	}
	AddTask(fallobj);

	//// �G(�K�X�}�X�N���m) ///////////////////////////////////////////

	CSoldier* sol1 = new CSoldier();
	sol1->Scale(1.0f, 1.0f, 1.0f);
	sol1->Position(-100.0f, 150, -150);
	AddTask(sol1);

	CSoldier* sol2 = new CSoldier();
	sol2->Scale(1.0f, 1.0f, 1.0f);
	sol2->Position(-50.0f, 150.0f, -150.0f);
	AddTask(sol2);

	/*CSoldier* sol3 = new CSoldier();
	sol3->Scale(1.0f, 1.0f, 1.0f);
	sol3->Position(50.0f, 150.0f, -200.0f);
	AddTask(sol3);*/

	/*CSoldier* sol4 = new CSoldier();
	sol4->Scale(1.0f, 1.0f, 1.0f);
	sol4->Position(0.0f, 150.0f, -500.0f);
	AddTask(sol4);*/

	/*CSoldier* sol5 = new CSoldier();
	sol5->Scale(1.0f, 1.0f, 1.0f);
	sol5->Position(0.0f, 50.0f, -550.0f);
	AddTask(sol5);*/
	
	////////////////////////////////////////////////////////////////////

	CVanguard* van = new CVanguard();
	van->Scale(1.4f, 1.4f, 1.4f);
	van->Position(0.0f, 150.0f, -500.0f);
	AddTask(van);

	/*CVanguard* van = new CVanguard();
	van->Scale(1.4f, 1.4f, 1.4f);
	van->Position(0.0f, 150.0f, -100.0f);
	AddTask(van);*/

	// �n�e�i�u���b�N�ƃ����K�u���b�N�̊Ԋu�͖�7.3f
	// �n�e�i�u���b�N
	CHatenaBlock* hatena = new CHatenaBlock
	(
		CVector(30.0f, 6.0f, -50.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos = CVector(30.0f, 6.0f, -50.0f);
	if (hatena != nullptr)
	{
		hatena->SetStartPosition(hatenaPos);
	}
	AddTask(hatena);

	CHatenaBlock* hatena1 = new CHatenaBlock
	(
		CVector(0.0f, 6.0f, -250.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos1 = CVector(0.0f, 6.0f, -250.0f);
	if (hatena1 != nullptr)
	{
		hatena1->SetStartPosition(hatenaPos1);
	}
	AddTask(hatena1);

	CHatenaBlock* hatena2 = new CHatenaBlock
	(
		CVector(7.3f, 6.0f, -450.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos2 = CVector(7.3f, 6.0f, -150.0f);
	if (hatena2 != nullptr)
	{
		hatena2->SetStartPosition(hatenaPos2);
	}
	AddTask(hatena2);

	CHatenaBlock* hatena3 = new CHatenaBlock
	(
		CVector(-100.0f, 19.0f, -430.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector hatenaPos3 = CVector(-100.0f, 19.0f, -430.0f);
	if (hatena3 != nullptr)
	{
		hatena3->SetStartPosition(hatenaPos3);
	}
	AddTask(hatena3);

	// �����K�u���b�N
	CRengaBlock* renga = new CRengaBlock
	(
		CVector(37.3f, 6.0f, -50.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rengaPos = CVector(37.3f, 6.0f, -50.0f);
	if (renga != nullptr)
	{
		renga->SetStartPosition(rengaPos);
	}
	AddTask(renga);

	// �����K�u���b�N
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(22.7f, 6.0f, -50.0f),
		CVector(5.0f, 5.0f, 5.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	CVector rengaPos1 = CVector(22.7f, 6.0f, -50.0f);
	if (renga1 != nullptr)
	{
		renga1->SetStartPosition(rengaPos1);
	}
	AddTask(renga1);



	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	player->MaxStatus();
	CVector playerPos = CVector(0.0f, 30.0f, -20.0f);
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

	
	//// �䂩�肳��
	//CYukari* yukari = new CYukari();
	//yukari->Scale(1.0f, 1.0f, 1.0f);
	//yukari->Position(0.0f, 100.0f, -200.0f);
	//AddTask(yukari);
}


// �X�e�[�W�j��
void CStage1::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}
