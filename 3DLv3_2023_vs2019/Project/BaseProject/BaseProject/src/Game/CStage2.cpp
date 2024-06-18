#include "CStage2.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CGoalObject.h"
#include "CHopsAndHoopsField.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CJumpingKinoko.h"
#include "CJumpingKinokoLeftRight.h"
#include "CJumpingKinokoUpDown.h"
#include "CHopsAndHoopsFallCol.h"
#include "CSavePoint1.h"
#include "CRingBeamer.h"

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
	// ���˂�L�m�R�R���C�_�[								 
	CResourceManager::Load<CModel>("JumpingKinokoCol",		"Field\\Gimmick\\Jump\\JumpingKinoko(Col).obj");
	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerUP",			"Effect\\BeamObj(Upper).obj");
	// �����O�r�[�}���f��(��)								  
	CResourceManager::Load<CModel>("RingBeamerLO",			"Effect\\BeamObj(Lower).obj");
	// �r���r���G�t�F�N�g							    
	CResourceManager::Load<CModel>("Biribiri",				"Effect\\BhimaEffect.obj");
	// �����O�r�[�}���f��(�R���C�_�[)						  
	CResourceManager::Load<CModel>("BiribiriCol",			"Effect\\BhimaEffect(Col).obj");

	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	CHopsAndHoopsField* field = new CHopsAndHoopsField();
	field->Position(0.0f, 0.0f, 0.0f);
	field->Scale(4.0f, 4.0f, 4.0f);
	field->Rotate(0.0f, 180.0f, 0.0f);
	AddTask(field);
	// �����R���C�_�[
	mpHopsAndHoopsFallCol = new CHopsAndHoopsFallCol();
	mpHopsAndHoopsFallCol->Scale(4.0f, 4.0f, 4.0f);
	AddTask(mpHopsAndHoopsFallCol);

	// �Z�[�u�|�C���g
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(0.0f, 0.0f, 480.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// �S�[���|�X�g
	CGoalObject* goal = new CGoalObject
	(
		CVector(0.0f, 0.0f, 1000.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 90.0f, 0.0f)
	);
	AddTask(goal);

	// �����Ȃ��L�m�R
	// �I�u�W�F�N�g��z�u���郋�[�v
	for (int i = 0; i < 4; ++i) {

		// X���̈ʒu��ݒ�
		float xPos = 0.0f;
		if (i == 3) xPos = -80.0f;

		// Y���̈ʒu��ݒ�
		float yPos = 0.0f;
		/*if (i == 0) yPos = 2.5f;*/

		// Z���̈ʒu��ݒ�
		float zPos = i * 55.0f;
		if (i == 0) zPos = 144.0f;
		if (i == 1) zPos = 199.0f;
		if (i == 2) zPos = 254.0f;
		if (i == 3) zPos = 480.0f;

		// X���̃X�P�[���l��ݒ�
		float xScale = 1.0f;	

		// Z���̃X�P�[���l��ݒ�
		float zScale = 1.0f;
	
		// �I�u�W�F�N�g���쐬���ă^�X�N�ɒǉ�
		CJumpingKinoko* jumpkinoko = new CJumpingKinoko
		(
			CVector(xPos, yPos, zPos),
			CVector(xScale, 1.0f, zScale),
			CVector(0.0f, 90.0f, 0.0f),
			ETag::ePlayer, ELayer::ePlayer
		);

		AddTask(jumpkinoko); // �^�X�N�ɒǉ�
	}

	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight1 = new CJumpingKinokoLeftRight
	(
		CVector(0.0f, 0.0f, 309.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(40.0f, 0.0f, 0.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoLeftRight1);
	// �����L�m�R(���E)
	CJumpingKinokoLeftRight* jumpkinokoLeftRight2 = new CJumpingKinokoLeftRight
	(
		CVector(-135.0f, 0.0f, 480.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 0.0f, 50.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoLeftRight2);

	// �����L�m�R(�㉺)
	CJumpingKinokoUpDown* jumpkinokoUpDown1 = new CJumpingKinokoUpDown
	(
		CVector(0.0f, 0.0f, 364.0f),
		CVector(1.0f, 1.0f, 1.0f),
		CVector(0.0f, 90.0f, 0.0f),
		CVector(0.0f, 40.0f, 0.0f),
		10.0f,
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(jumpkinokoUpDown1);

	// �����O�r�[�}1
	CRingBeamerUpper* beamerUp1 = new CRingBeamerUpper
	(
		CVector(-55.0f, 8.0f, 199.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp1);
	// �����O�r�[�}1
	CRingBeamerLower* beamerLow1 = new CRingBeamerLower
	(
		CVector(-55.0f, 7.5f, 199.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow1);

	// �����O�r�[�}2
	CRingBeamerUpper* beamerUp2 = new CRingBeamerUpper
	(
		CVector(70.0f, 8.0f, 299.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerUp2);
	// �����O�r�[�}2
	CRingBeamerLower* beamerLow2 = new CRingBeamerLower
	(
		CVector(70.0f, 7.5f, 299.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(beamerLow2);

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

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(0.0f, 20.0f, 50.0f);
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