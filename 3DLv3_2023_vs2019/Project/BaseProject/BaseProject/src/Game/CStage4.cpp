#include "CStage4.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSeesawAdventure.h"
#include "CSeesaw.h"
#include "CStageSky.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CMeat1Event.h"
#include "CInput.h"

// �R���X�g���N�^
CStage4::CStage4()
{
	mStageNo = 4;
}

// �f�X�g���N�^
CStage4::~CStage4()
{

}

// �X�e�[�W�ǂݍ���
void CStage4::Load()
{
	// �X�e�[�W�̋�
	CResourceManager::Load<CModel>("StageSky", "Field\\StageSky\\Sky(Sphere).obj");
	// �X�e�[�W���f��
	CResourceManager::Load<CModel>("SeesawStage(Base)", "Field\\SeesawStage\\SeesawStage(Base).obj");
	// �X�e�[�W���R���C�_�[
	CResourceManager::Load<CModel>("SeesawStage(Floor)", "Field\\SeesawStage\\SeesawStage(FloorCol).obj");
	// �X�e�[�W�ǃR���C�_�[
	CResourceManager::Load<CModel>("SeesawStage(Wall)", "Field\\SeesawStage\\SeesawStage(WallCol).obj");
	// �X�e�[�W�����R���C�_�[
	CResourceManager::Load<CModel>("SeesawStage(Fall)", "Field\\SeesawStage\\SeesawStage(FallCol).obj");

	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("SeesawModel", "Field\\Gimmick\\SeesawGimmick\\SeesawModel.obj");
	// �V�[�\�[���f��
	CResourceManager::Load<CModel>("SeesawModelCol", "Field\\Gimmick\\SeesawGimmick\\SeesawModel(Col).obj");
	
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");
	// �T�[�N���G�t�F�N�g
	CResourceManager::Load<CModel>("CircleEffect1", "Effect\\CharacterEffect\\CharaEffectCircle.obj");
	CResourceManager::Load<CModel>("CircleEffect2", "Effect\\CharacterEffect\\CharaEffectCircle(Widthver).obj");
	// �L�����N�^�[�G�t�F�N�g
	CResourceManager::Load<CModel>("CharEffect", "Effect\\CharacterEffect\\CharacterEffect(Up).obj");
	// �L�����N�^�[�G�t�F�N�g(���C��)
	CResourceManager::Load<CModel>("LineEffect", "Effect\\CharacterEffect\\CharacterEffect(Line).obj");

	// T�L�[�̉摜
	CResourceManager::Load<CTexture>("TUI", "UI\\GimmickUI\\T.png");

	CResourceManager::Load<CTexture>("Laser", "Effect\\laser.png");

	CInput::ShowCursor(false);

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	mpFeild = new CSeesawAdventure();
	mpFeild->Position(0.0f, 0.0f, 0.0f);
	mpFeild->Scale(4.0f, 4.0f, 4.0f);
	mpFeild->Rotate(0.0f, 0.0f, 0.0f);
	AddTask(mpFeild);

	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	//// �����R���C�_�[
	//mpFallCol = new CHopsAndHoopsFallCol();
	//mpFallCol->Scale(20.0f, 3.0f, 20.0f);
	//AddTask(mpFallCol);


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

	//// ��1���擾�����
	//// �n�C�W�����v�L�m�R���쐬
	//CJumpingKinokoHigh* highkinoko = new CJumpingKinokoHigh
	//(
	//	CVector(-483.0f, 5.0f, 500.0f),
	//	CVector(1.0f, 1.0f, 1.0f),
	//	CVector(0.0f, 0.0f, 0.0f)
	//);
	//AddTask(highkinoko);
	//highkinoko->SetEvent(mtEvent);
	//mtEvent->SetHighKinoko(highkinoko);

	CMeat2* meat2 = new CMeat2
	(
		CVector(337.0f, 35.0f, 1290.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat2->SetMeatNumber(2);
	AddTask(meat2);

	CMeat3* meat3 = new CMeat3
	(
		CVector(-337.0f, 35.0f, 1290.0f),
		CVector(0.0f, 0.0f, 0.0f),
		CVector(4.0f, 4.0f, 4.0f)
	);
	meat3->SetMeatNumber(3);
	AddTask(meat3);

	/////////////////////////////////////////////////////////////////////////////////////

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	// �����l�_ : 329.0f, -275.0f, -954.0f
	CVector playerPos = CVector(329.0f, -275.0f, -954.0f);
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
	mainCamera->AddCollider(mpFeild->GetWallCol());
}

// �X�e�[�W�j��
void CStage4::Unload()
{
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->RemoveCollider(mpFeild->GetWallCol());
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}