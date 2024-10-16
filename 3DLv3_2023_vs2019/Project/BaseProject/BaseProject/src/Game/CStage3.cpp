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
#include "CCircleLine.h"
#include "CBGMManager.h"

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
	CResourceManager::Load<CModel>("Stage3WallCol",		"Field\\Final Stage\\WallCol.obj");
	// ��������R���C�_�[
	CResourceManager::Load<CModel>("Stage3FallCol", "Field\\Final Stage\\FallCol.obj");

	// �󓇃��f��
	CResourceManager::Load<CModel>("Skyisland", "GameGimmick\\Object\\Skyisland.obj");

	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint", "GameGimmick\\Gimmick\\SaveFlag\\SavePoint.obj");
	// �S�[���|�X�g���f��
	CResourceManager::Load<CModel>("GoalPost", "GameGimmick\\Gimmick\\Goal\\GoalPost.obj");
	// �S�[���u���b�N���f��
	CResourceManager::Load<CModel>("GoalCube", "GameGimmick\\Gimmick\\Goal\\GoalCube.obj");

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

	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerUP", "Effect\\BeamObj(Upper).obj");
	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerLO", "Effect\\BeamObj(Lower).obj");
	// �r���r���G�t�F�N�g							    
	CResourceManager::Load<CModel>("Biribiri", "Effect\\BhimaEffect.obj");
	// �����O�r�[�}���f��(�R���C�_�[)						  
	CResourceManager::Load<CModel>("BiribiriCol", "Effect\\BhimaEffect(Col).obj");
	// �����O�r�[�}���f��(�R���C�_�[)						  
	CResourceManager::Load<CTexture>("LightningBolt", "Effect\\lightning_bolt.png");
	// �T�[�N�����C��
	CResourceManager::Load<CModel>("CircleLine", "GameGimmick\\Gimmick\\Jump\\CircleLine.obj");

	// ��]���鏰���f��
	CResourceManager::Load<CModel>("RotateFloor", "GameGimmick\\Gimmick\\Rotate\\RotateFloor.obj");
	// ��]���鏰�̕\���̃R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorFrontCol", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol.obj");
	// ��]���鏰�̗����̃R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorBackCol", "GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol.obj");
	// ��]���鏰���f��(����)
	CResourceManager::Load<CModel>("RotateFloorOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloor(Opposition).obj");
	// ��]���鏰�̕\���̃R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorFrontColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol(Opposition).obj");
	// ��]���鏰�̗����̃R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorBackColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol(Opposition).obj");

	// �Ή����ˊ�(�^���N)
	//CResourceManager::Load<CModel>("", "");	
	// �Ή����ˊ�(�y��)
	//CResourceManager::Load<CModel>("", "");
	// �Ή����ˊ�(�R���C�_�[)
	//CResourceManager::Load<CModel>("", "");

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

	// BGM���Đ�
	CBGMManager::Instance()->Play(EBGMType::eStage3);

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

	// �Z�[�u�|�C���g1
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 0.0f, 453.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);
	// �Z�[�u�|�C���g2
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(0.0f, 0.0f, 1550.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// �S�[���|�X�g
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, -5.0f, 1850.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 8; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 2) xPos = 109.0f;
		if (i == 3) xPos = -114.0f;
		if (i == 4) xPos = 119.0f;
		if (i == 5) xPos = -124.0f;
		if (i == 6) xPos = 109.0f;
		if (i == 7) xPos = -114.0f;
		
		// Y���̈ʒu��ݒ�
		float yPos = -2.0f;
		if (i == 1) yPos = -10.0f;
		if (i == 2) yPos = -10.0f;
		if (i == 3) yPos = -10.0f;
		if (i == 4) yPos = -10.0f;
		if (i == 5) yPos = -10.0f;
		if (i == 6) yPos = -10.0f;
		if (i == 7) yPos = -10.0f;
		
		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0) zPos = 80.0f;
		if (i == 1) zPos = 1050.0f;
		if (i == 2) zPos = 1100.0f;
		if (i == 3) zPos = 1100.0f;
		if (i == 4) zPos = 1150.0f;
		if (i == 5) zPos = 1150.0f;
		if (i == 6) zPos = 1210.0f;
		if (i == 7) zPos = 1210.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 2.0f;
		if (i == 0) xScale = 3.0f;
		if (i == 1) xScale = 6.0f;
		if (i == 4) xScale = 4.0f;
		if (i == 5) xScale = 4.0f;

		// Z���̃X�P�[���l��ݒ�
		float zScale = 2.0f;
		if (i == 0) zScale = 4.0f;
		if (i == 1) zScale = 7.0f;
		if (i == 4) zScale = 5.0f;
		if (i == 5) zScale = 5.0f;

		// Y���̉�]�l��ݒ�
		float yRotate = 45.0f;

		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CNumberFloor3* numberfloor3 = new CNumberFloor3
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 2.0f, zScale),
			CVector(0.0f, yRotate, 0.0f)
		);

		AddTask(numberfloor3);
	}

	// 1��
	CNumberFloor1* number1 = new CNumberFloor1
	(
		CVector(104.0f, -10.0f, 1380.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f)
	);
	AddTask(number1);

	// 1��
	CNumberFloor1* number2 = new CNumberFloor1
	(
		CVector(-114.0f, -10.0f, 1380.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f)
	);
	AddTask(number2);

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
	CCircleNbFlLeft2* floor2left1 = new CCircleNbFlLeft2
	(
		CVector(63.0f, -15.0f, 153.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		false
	);
	AddTask(floor2left1);

	// ������(�E�~��])
	CCircleNbFlRight2* floor2right2 = new CCircleNbFlRight2
	(
		CVector(109.0f, -10.0f, 1300.0f),
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		30.0f, 30.0f, 40.0f,
		true
	);
	AddTask(floor2right2);

	// ������(���~��])
	CCircleNbFlLeft2* floor2left2 = new CCircleNbFlLeft2
	(
		CVector(-114.0f, -10.0f, 1300.0f),
		CVector(3.0f, 3.0f, 3.0f),
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

	// �w�肵���ړ��|�C���g�Ԃ��ړ�����񐔐�����
	CMoveToNbFl1* mn1f2 = new CMoveToNbFl1
	(
		CVector(3.0f, 2.0f, 3.0f),
		CVector(0.0f, 45.0f, 0.0f),
		2.0f
	);
	mn1f2->SetReturnRoute(false);
	mn1f2->AddMovePoint(CVector(100.0f, -10.0f, 1450.0f), 3.0f);
	mn1f2->AddMovePoint(CVector(-100.0f, -10.0f, 1450.0f), 3.0f);
	AddTask(mn1f2);

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

	// �w�肵���ʒu�Ɉړ�����W�����v�L�m�R
	CJumpingKinokoMoveTo* jkmt1 = new CJumpingKinokoMoveTo
	(
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f),
		1.0f
	);
	jkmt1->SetReturnRoute(false);
	jkmt1->AddMovePoint(CVector(55.0f, 0.0f, 690.0f), 4.0f);
	jkmt1->AddMovePoint(CVector(202.0f, 0.0f, 690.0f), 4.0f);
	jkmt1->AddMovePoint(CVector(202.0f, 0.0f, 776.0f), 4.0f);
	jkmt1->AddMovePoint(CVector(55.0f, 0.0f, 776.0f), 4.0f);
	AddTask(jkmt1);

	// �w�肵���ʒu�Ɉړ�����W�����v�L�m�R
	CJumpingKinokoMoveTo* jkmt2 = new CJumpingKinokoMoveTo
	(
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f),
		1.0f
	);
	jkmt2->SetReturnRoute(false);
	jkmt2->AddMovePoint(CVector(-55.0f, 0.0f, 690.0f), 4.0f);
	jkmt2->AddMovePoint(CVector(-202.0f, 0.0f, 690.0f), 4.0f);
	jkmt2->AddMovePoint(CVector(-202.0f, 0.0f, 776.0f), 4.0f);
	jkmt2->AddMovePoint(CVector(-55.0f, 0.0f, 776.0f), 4.0f);
	AddTask(jkmt2);

	// �����O�r�[�}1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(124.0f, 8.0f, 735.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// �����O�r�[�}1
	CRingBeamerLower* beamerLow1 = new CRingBeamerLower
	(
		CVector(124.0f, 7.5f, 735.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow1);
	CCircleLine* cline4 = new CCircleLine
	(
		CVector(124.0f, 8.0f, 735.0f),
		CVector(24.0f, 8.0f, 24.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(cline4);

	// �����O�r�[�}2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(-124.0f, 8.0f, 735.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// �����O�r�[�}2
	CRingBeamerLower* beamerLow2 = new CRingBeamerLower
	(
		CVector(-124.0f, 7.5f, 735.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow2);
	CCircleLine* cline5 = new CCircleLine
	(
		CVector(-124.0f, 8.0f, 735.0f),
		CVector(24.0f, 8.0f, 24.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(cline5);

	// ��]���鏰
	for (int i = 0; i < 7; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 1) xPos = 73.0f;
		if (i == 2) xPos = -76.0f;
		if (i == 3) xPos = 36.5f;
		if (i == 4) xPos = -38.0f;
		if (i == 5) xPos = 109.5f;
		if (i == 6) xPos = -114.0f;
		
		// Y���̈ʒu��ݒ�
		//float yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0) zPos = 826.0f;
		if (i == 1) zPos = 866.0f;
		if (i == 2) zPos = 866.0f;
		if (i == 3) zPos = 906.0f;
		if (i == 4) zPos = 906.0f;
		if (i == 5) zPos = 986.0f;
		if (i == 6) zPos = 986.0f;

		// ��]���鏰
		CRotateFloorGimmick* floorGimmick1 = new CRotateFloorGimmick
		(
			CVector(xPos, 0.0f, zPos),
			CVector(4.0f, 4.0f, 4.0f),
			CVector(0.0f, 0.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);
		AddTask(floorGimmick1);
	}

	// ��]���鏰(����)
	for (int i = 0; i < 4; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 0) xPos = 73.0f;
		if (i == 1) xPos = -76.0f;
		if (i == 2) xPos = 109.5f;
		if (i == 3) xPos = -114.0f;

		// Y���̈ʒu��ݒ�
		//float yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = 0.0f;
		if (i == 0) zPos = 946.0f;
		if (i == 1) zPos = 946.0f;
		if (i == 2) zPos = 1066.0f;
		if (i == 3) zPos = 1066.0f;

		// ��]���鏰
		CRotateFloorGimmickOpposition* floorGimmickOpt1 = new CRotateFloorGimmickOpposition
		(
			CVector(xPos, 0.0f, zPos),
			CVector(4.0f, 4.0f, 4.0f),
			CVector(0.0f, 0.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);
		AddTask(floorGimmickOpt1);
	}

	// ���Ԃŉ�]���鏰
	CRotateFloorTimeGimmick* timeGimmick1 = new CRotateFloorTimeGimmick
	(
		CVector(109.0f, 0.0f, 1026.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(timeGimmick1);

	// ���Ԃŉ�]���鏰
	CRotateFloorTimeGimmick* timeGimmick2 = new CRotateFloorTimeGimmick
	(
		CVector(-114.0f, 0.0f, 1026.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(timeGimmick2);

	// ��C
	CCannon* Cannon = new CCannon
	(
		CVector(390.0f, 8.0f, 1090.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 45.0f, 0.0f),
		"Cannon"
	);
	AddTask(Cannon);
	// ��C�y��
	CCannonFoundationsBase* Cannonfound = new CCannonFoundationsBase
	(
		CVector(390.0f, 8.0f, 1090.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -90.0f, 0.0f)
	);
	AddTask(Cannonfound);

	// ��C
	CCannon* Cannon1 = new CCannon
	(
		CVector(-390.0f, 8.0f, 1090.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, -45.0f, 0.0f),
		"Cannon"
	);
	AddTask(Cannon1);
	// ��C�y��
	CCannonFoundationsBase* Cannonfound1 = new CCannonFoundationsBase
	(
		CVector(-390.0f, 8.0f, 1090.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(Cannonfound1);

	// ��C(�΍�����)
	CPowerfulCannon* targetCannon = new CPowerfulCannon
	(
		CVector(4.0f, 85.0f, 1303.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f),
		"Cannon"
	);
	AddTask(targetCannon);
	// ��C�y��
	CCannonFoundationsBase* targetCannonfound = new CCannonFoundationsBase
	(
		CVector(4.0f, 85.0f, 1303.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 00.0f, 0.0f)
	);
	AddTask(targetCannonfound);

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
	// ��]���鏰 : 10.0f, 10.0f, 826.0f
	// �Z�[�u�|�C���g2 : 0.0f, 0.0f, 1550.0f
	CVector playerPos = CVector(0.0f, 10.0f, 1550.0f);
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