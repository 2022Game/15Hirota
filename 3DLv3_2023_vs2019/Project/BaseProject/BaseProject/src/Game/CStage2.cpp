#include "CStage2.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CGoalObject.h"
#include "CHopsAndHoopsField.h"
#include "CStageSky.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoLeftRight.h"
#include "CJumpingKinokoUpDown.h"
#include "CJumpingKinokoTurnRight.h"
#include "CJumpingKinokoTurnLeft.h"
#include "CHopsAndHoopsFallCol.h"
#include "CSavePoint1.h"
#include "CSavePoint2.h"
#include "CRingBeamer.h"
#include "CElectricLaser.h"
#include "CHatenaBlock.h"
#include "CTreasureChest.h"
#include "CMetalLadder.h"
#include "CRengaBlock.h"
#include "CPropeller.h"
#include "CMeat1Event.h"
#include "CJumpingKinokoHigh.h"

// �R���X�g���N�^
CStage2::CStage2()
{
	mStageNo = 2;
}

// �f�X�g���N�^
CStage2::~CStage2()
{

}

// �X�e�[�W�ǂݍ���
void CStage2::Load()
{
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky",				"Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("HopsAndHoops(Base)",	"Field\\HopsAndHoops\\Stage2(Base).obj");
	// �X�e�[�W���R���C�_�[
	CResourceManager::Load<CModel>("HopsAndHoops(Col)",		"Field\\HopsAndHoops\\Stage2(FloorCol).obj");
	// �X�e�[�W���R���C�_�[
	CResourceManager::Load<CModel>("HopsAndHoops(FallCol)", "Field\\HopsAndHoops\\Stage2(FallCol).obj");
	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint",				"Field\\Gimmick\\SavePoint.obj");
	// �S�[���|�X�g���f��							    
	CResourceManager::Load<CModel>("GoalPost",				"Field\\Object\\GoalPost.obj");
	// �S�[���u���b�N���f��							   
	CResourceManager::Load<CModel>("GoalCube",				"Field\\Object\\GoalCube.obj");
	// ���˂�L�m�R���f��							    
	CResourceManager::Load<CModel>("JumpingKinoko",			"Field\\Gimmick\\Jump\\JumpingKinoko(Base).obj");
	// ���˂�L�m�R���f��2						    
	CResourceManager::Load<CModel>("JumpingKinoko2Color",	"Field\\Gimmick\\Jump\\JumpingKinoko(Base_2Color).obj");
	// ���˂�L�m�R���f��3						    
	CResourceManager::Load<CModel>("JumpingKinoko3Color",	"Field\\Gimmick\\Jump\\JumpingKinoko(Base_3Color).obj");
	// ���˂�L�m�R�R���C�_�[								 
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// ���W�����v�L�m�R���f��
	CResourceManager::Load<CModel>("HighKinoko",			"Field\\Gimmick\\Jump\\HighJumpKinoko.obj");
	// ���W�����v�L�m�R�R���C�_�[
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\HighJumpKinokoCol.obj");
	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerUP",			"Effect\\BeamObj(Upper).obj");
	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerLO",			"Effect\\BeamObj(Lower).obj");
	// �r���r���G�t�F�N�g							    
	CResourceManager::Load<CModel>("Biribiri",				"Effect\\BhimaEffect.obj");
	// �����O�r�[�}���f��(�R���C�_�[)						  
	CResourceManager::Load<CModel>("BiribiriCol",			"Effect\\BhimaEffect(Col).obj");
	// �����O�r�[�}���f��(�R���C�_�[)						  
	CResourceManager::Load<CTexture>("LightningBolt",		"Effect\\lightning_bolt.png");
	// �n�e�i�u���b�N(�A�C�e���ۗL)
	CResourceManager::Load<CModel>("HatenaBlock",			"Field\\Object\\hatena.obj");
	// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	CResourceManager::Load<CModel>("HatenaBlockAfter",		"Field\\Object\\UsedHatenaBlock.obj");
	// �����K�u���b�N
	CResourceManager::Load<CModel>("RengaBlock",			"Field\\Object\\RengaBlock.obj");
	// ��
	CResourceManager::Load<CModel>("TreasureChest",			"Field\\Gimmick\\Chest\\TreasureChest.obj");
	// ��(�W)
	CResourceManager::Load<CModel>("TreasureChestTwo",		"Field\\Gimmick\\Chest\\TreasureChestTwo.obj");
	// ��(�W�R���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestCol",		"Field\\Gimmick\\Chest\\TreasureChest(FloorCol).obj");
	// ��(�ǃR���C�_�[)
	CResourceManager::Load<CModel>("TreasureChestWallCol",	"Field\\Gimmick\\Chest\\TreasureChest(WallCol).obj");
	// �v���y��
	CResourceManager::Load<CModel>("Propeller",				"Field\\Gimmick\\propeller.obj");
	// �v���y��(Col)
	CResourceManager::Load<CModel>("PropellerWallCol",		"Field\\Gimmick\\propeller(Col).obj");

	// �����̒�q�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Metalladder",			"Field\\HopsAndHoops\\Metalladder(Base).obj");
	// �����̒�q�I�u�W�F�N�g(Col)
	CResourceManager::Load<CModel>("MetalladderCol",		"Field\\HopsAndHoops\\Metalladder(Col).obj");
	// �����̒�q�I�u�W�F�N�g(TopCol)
	CResourceManager::Load<CModel>("MetalladderTopCol",		"Field\\HopsAndHoops\\Metalladder(TopCol).obj");

	// �����f��
	CResourceManager::Load<CModel>("Meat",			"Item\\StageItem\\niku.obj");
	// �񕜖�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Healing",		"Item\\StatusItem\\HealingItem.obj");
	// �񕜃I�u�W�F�N�g
	CResourceManager::Load<CModel>("Heart",			"Item\\StatusItem\\Heart.obj");
	// ���G�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Star",			"Item\\StatusItem\\Star.obj");
	// �U���̓A�b�v���f��
	CResourceManager::Load<CModel>("AttackPotion",	"Item\\StatusItem\\AttackPotion.obj");

	// �G�t�F�N�g
	CResourceManager::Load<CModel>("CircleEffect1",			"Effect\\CharacterEffect\\CharaEffectCircle.obj");
	CResourceManager::Load<CModel>("CircleEffect2",			"Effect\\CharacterEffect\\CharaEffectCircle(Widthver).obj");
	// �L�����N�^�[�G�t�F�N�g
	CResourceManager::Load<CModel>("CharEffect",			"Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// �L�����N�^�[�G�t�F�N�g(���C��)
	CResourceManager::Load<CModel>("LineEffect",			"Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CHopsAndHoopsField* field = new CHopsAndHoopsField();
	field->Position(0.0f, 0.0f, 0.0f);
	field->Scale(4.0f, 4.0f, 4.0f);
	field->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(field);
	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);
	// �����R���C�_�[
	mpHopsAndHoopsFallCol = new CHopsAndHoopsFallCol();
	mpHopsAndHoopsFallCol->Scale(10.0f, 3.0f, 10.0f);
	AddTask(mpHopsAndHoopsFallCol);

	// �Z�[�u�|�C���g1
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 0.0f, 480.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);
	// �Z�[�u�|�C���g2
	CSavePoint2* savepoint2 = new CSavePoint2
	(
		CVector(0.0f, 53.0f, 994.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint2->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint2);

	// �S�[���|�X�g
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.0f, 1520.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// �����Ȃ��L�m�R�@
	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 13; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 3) xPos = -100.0f;
		if (i == 4) xPos = -210.0f;
		if (i == 5) xPos = -210.0f;
		if (i == 6) xPos = -265.0f;
		if (i == 7) xPos = 0.0f;
		if (i == 8) xPos = 0.0f;
		if (i == 9) xPos = 0.0f;
		if (i == 10) xPos = 0.0f;
		if (i == 11) xPos = 160.0f;
		if (i == 12) xPos = 160.0f;

		// Y���̈ʒu��ݒ�
		float yPos = 0.0f;
		if (i == 9) yPos = 55.0f;
		if (i == 10) yPos = 55.0f;
		if (i == 11) yPos = 0.0f;
		if (i == 12) yPos = 0.0f;

		// Z���̈ʒu��ݒ�
		float zPos = i * 55.0f;
		if (i == 0) zPos = 144.0f;
		if (i == 1) zPos = 199.0f;
		if (i == 2) zPos = 254.0f;
		if (i == 3) zPos = 480.0f;
		if (i == 4) zPos = 450.0f;
		if (i == 5) zPos = 510.0f;
		if (i == 6) zPos = 480.0f;
		if (i == 7) zPos = 570.0f;
		if (i == 8) zPos = 680.0f;
		if (i == 9) zPos = 1050.0f;
		if (i == 10) zPos = 1105.0f;
		if (i == 11) zPos = 1235.0f;
		if (i == 12) zPos = 1290.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 1.0f;
		if (i == 8) xScale = 2.0f;

		// Z���̃X�P�[���l��ݒ�
		float zScale = 1.0f;
		if (i == 8) zScale = 2.0f;
	
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CJumpingKinoko* jumpkinoko = new CJumpingKinoko
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 1.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f)
		);

		AddTask(jumpkinoko); // �^�X�N�ɒǉ�
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight1 = new CJumpingKinokoLeftRight
	(
		CVector(0.0f, 0.0f, 309.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoLeftRight1);
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight2 = new CJumpingKinokoLeftRight
	(
		CVector(-155.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 0.0f, 50.0f),
		10.0f
	);
	AddTask(jumpkinokoLeftRight2);
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight3 = new CJumpingKinokoLeftRight
	(
		CVector(-360.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(50.0f, 0.0f, 0.0f),
		13.0f
	);
	AddTask(jumpkinokoLeftRight3);
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight4 = new CJumpingKinokoLeftRight
	(
		CVector(-60.0f, 0.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(30.0f, 0.0f, 0.0f),
		5.0f
	);
	AddTask(jumpkinokoLeftRight4);
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight5 = new CJumpingKinokoLeftRight
	(
		CVector(60.0f, 0.0f, 625.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(-30.0f, 0.0f, 0.0f),
		5.0f
	);
	AddTask(jumpkinokoLeftRight5);
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	// �����L�m�R(�㉺)
	CJumpingKinokoUpDown* jumpkinokoUpDown1 = new CJumpingKinokoUpDown
	(
		CVector(0.0f, 0.0f, 364.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 40.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoUpDown1);
	// �����L�m�R(�㉺)
	CJumpingKinokoUpDown* jumpkinokoUpDown2 = new CJumpingKinokoUpDown
	(
		CVector(120.0f, 30.0f, 1180.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, -30.0f, 0.0f),
		10.0f
	);
	AddTask(jumpkinokoUpDown2);
	/////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////////////////////////////////
	// �����L�m�R(�E�~��])
	CJumpingKinokoTurnRight* rotatekinoko1 = new CJumpingKinokoTurnRight
	(
		CVector(0.0f, 55.0f, 1180.0f),
		CVector(1.3f, 1.0f, 1.3f),
		CVector(0.0f, 0.0f, 0.0f),
		30.0f, 30.0f, 80.0f,
		true
	);
	AddTask(rotatekinoko1);
	//////////////////////////////////////////////////////////////////////////////////////

	// �����O�r�[�}1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-55.0f, 8.0f, 254.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// �����O�r�[�}1
	CRingBeamerLower* beamerLow1 = new CRingBeamerLower
	(
		CVector(-55.0f, 7.5f, 254.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow1);

	// �����O�r�[�}2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(-210.0f, 8.0f, 390.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// �����O�r�[�}2
	CRingBeamerLower* beamerLow2 = new CRingBeamerLower
	(
		CVector(-210.0f, 7.5f, 390.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow2);

	// �����O�r�[�}3
	CRingBeamerUpper* beamerUp3 = new CRingBeamerUpper
	(
		CVector(-210.0f, 8.0f, 570.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp3);
	// �����O�r�[�}3
	CRingBeamerLower* beamerLow3 = new CRingBeamerLower
	(
		CVector(-210.0f, 7.5f, 570.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow3);

	// ����̓d��1
	CElectricLaser* laser1 = new CElectricLaser
	(
		CVector(0.0f, 20.0f, 810.0f),
		CVector(0.0f, 40.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f),
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f)
	);
	AddTask(laser1);
	// ����̓d��2
	CElectricLaser* laser2 = new CElectricLaser
	(
		CVector(0.0f, 50.0f, 810.0f),
		CVector(0.0f, -40.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f),
		CVector(-75.0f, 5.0f, 0.0f),
		CVector(75.0f, 5.0f, 0.0f)
	);
	AddTask(laser2);

	// ����̓d��3
	CElectricLaser* laser3 = new CElectricLaser
	(
		CVector(0.0f, 50.0f, 935.0f),
		CVector(0.0f, 50.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f),
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f)
	);
	AddTask(laser3);
	// ����̓d��4
	CElectricLaser* laser4 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(0.0f, -50.0f, 0.0f),
		2.0f,
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f),
		CVector(-75.0f, 0.0f, 0.0f),
		CVector(75.0f, 0.0f, 0.0f)
	);
	AddTask(laser4);

	// ����̓d��5
	CElectricLaser* laser5 = new CElectricLaser
	(
		CVector(-340.0f, 15.0f, 480.0f),
		CVector(0.0f, 10.0f, 0.0f),
		3.0f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser5);

	// ����̓d��6
	CElectricLaser* laser6 = new CElectricLaser
	(
		CVector(-450.0f, 10.0f, 480.0f),
		CVector(0.0f, 0.0f, 0.0f),
		0.1f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser6);

	// ����̓d��7
	CElectricLaser* laser7 = new CElectricLaser
	(
		CVector(-450.0f, 30.0f, 480.0f),
		CVector(0.0f, 0.0f, 0.0f),
		0.1f,
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f),
		CVector(0.0f, 0.0f, 65.0f),
		CVector(0.0f, 0.0f, -65.0f)
	);
	AddTask(laser7);

	// ����̓d��
	CElectricLaser* laser8 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(40.0f, 0.0f, 0.0f),
		2.0f,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f),
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f)
	);
	AddTask(laser8);
	// ����̓d��
	CElectricLaser* laser9 = new CElectricLaser
	(
		CVector(0.0f, 0.0f, 935.0f),
		CVector(-40.0f, 0.0f, 0.0f),
		2.0f,
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f),
		CVector(0.0f, -75.0f, 0.0f),
		CVector(0.0f, 75.0f, 0.0f)
	);
	AddTask(laser9);

	// �����K�u���b�N1
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(0.0f, 1.0f, 10.0f),
		CVector(6.0f, 6.0f, 6.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga1);

	// �v���y��
	CPropeller* propeller = new CPropeller
	(
		CVector(0.0f, 30.0f, 950.0f),
		CVector(1.0f, 1.0f, 1.0f),
		0.5f
	);
	AddTask(propeller);

	// ��1
	CTreasureChest* treasure1 = new CTreasureChest
	(
		CVector(0.0f, 0.0f, 60.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure1);
	// �󔠊W1
	CTreasureChestTwo* treasureTwo1 = new CTreasureChestTwo
	(
		CVector(0.0f, 3.8f, 60.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo1);

	// ��2
	CTreasureChest* treasure2 = new CTreasureChest
	(
		CVector(-50.0f, 56.5f, 994.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 180.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasure2);
	// �󔠊W2
	CTreasureChestTwo* treasureTwo2 = new CTreasureChestTwo
	(
		CVector(-50.0f, 59.5f, 994.0f),
		CVector(4.0f, 4.0f, 4.0f),
		CVector(0.0f, 180.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(treasureTwo2);

	// �o�����Ԃ��쐬
	CMetalLadder* metalladder = new CMetalLadder
	(
		"Metalladder", "MetalladderTopCol",
		CVector(0.0f, 15.0f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 15.0f)	// ���ʕ����̈ړ�
	);
	metalladder->Scale(4.0f, 4.0f, 4.0f);
	metalladder->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(metalladder);

	//// ���I�u�W�F�N�g /////////////////////////////////////////////////////////////////
	
	// ��1�l���C�x���g�𐶐�
	CMeat1Event* mtEvent = new CMeat1Event();
	AddTask(mtEvent);

	CMeat1* meat1 = new CMeat1
	(
		CVector(-483.0f, 10.0f, 483.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	AddTask(meat1);
	meat1->SetMeatNumber(1);
	meat1->SetEvent(mtEvent);
	mtEvent->AddMeat1(meat1);

	// ��1���擾�����
	// �n�C�W�����v�L�m�R���쐬
	CJumpingKinokoHigh* highkinoko = new CJumpingKinokoHigh
	(
		CVector(-483.0f, 5.0f, 500.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(highkinoko);
	highkinoko->SetEvent(mtEvent);
	mtEvent->SetHighKinoko(highkinoko);

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

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	// �����l�_ : 0.0f, 20.0f, 50.0f
	// ���ԃ|�C���g : 0.0f, 0.0f, 480.0f
	// ���ԃ|�C���g2 : 0.0f, 53.0f, 994.0f
	// ��1�̏ꏊ : -483.0f, 10.0f, 483.0f
	CVector playerPos = CVector(0.0f, 53.0f, 994.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, 0.0f, 0.0f);//0.0f, 225.0f, 0.0f
	}

	// �J�����̈ʒu�ƌ�����ݒ� -1109.0f, 90.0f, 1200.0f
	// CVector(-757.0f, 90.0f, -958.0f),
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(camPos, playerPos, CVector::up);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(mpField1->GetWallCol());
}

// �X�e�[�W�j��
void CStage2::Unload()
{
	CCamera* mainCamera = CCamera::MainCamera();
	//mainCamera->RemoveCollider(mpField1->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}