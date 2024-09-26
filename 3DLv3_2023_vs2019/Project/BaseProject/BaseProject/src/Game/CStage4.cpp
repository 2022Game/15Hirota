#include "CStage4.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CSeesawAdventure.h"
#include "CSeesaw.h"
#include "CSplitSeesaw.h"
#include "CSpring.h"
#include "CStageSky.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CMeat1Event.h"
#include "CInput.h"
#include "CRotateFloorTimeGimmick.h"
#include "CSeesawStageFallCol.h"
#include "CSavePoint1.h"
#include "CPicoChan.h"
#include "CMetalLadder.h"
#include "CRengaBlock.h"
#include "CHatenaBlock.h"

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
	// �V�[�\�[���f���R���C�_�[
	CResourceManager::Load<CModel>("SeesawModelCol", "Field\\Gimmick\\SeesawGimmick\\SeesawModel(Col).obj");
	// �����V�[�\�[���f��
	CResourceManager::Load<CModel>("SplitSeesawModel", "Field\\Gimmick\\SeesawGimmick\\SplitSeesaw.obj");
	// �����V�[�\�[���f���R���C�_�[
	CResourceManager::Load<CModel>("SplitSeesawModelCol", "Field\\Gimmick\\SeesawGimmick\\SplitSeesawCol.obj");

	// �o�l���f��(��ƃo�l)
	CResourceManager::Load<CModel>("Spring", "GameGimmick\\Gimmick\\Jump\\Spring.obj");
	// �o�l���f��(��)
	CResourceManager::Load<CModel>("SpringLower", "GameGimmick\\Gimmick\\Jump\\SpringLower.obj");
	// �o�l�R���C�_�[���f��
	CResourceManager::Load<CModel>("SpringCol", "GameGimmick\\Gimmick\\Jump\\SpringCol.obj");

	// ��]���鏰
	CResourceManager::Load<CModel>("RotateFloor", "GameGimmick\\Gimmick\\Rotate\\RotateFloor.obj");
	// ��]���鏰�̑O�R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorFrontCol", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol.obj");
	// ��]���鏰�̌��R���C�_�[
	CResourceManager::Load<CModel>("RotateFloorBackCol", "GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol.obj");
	// ��]���鏰(����)
	CResourceManager::Load<CModel>("RotateFloorOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloor(Opposition).obj");
	// ��]���鏰�̑O�R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorFrontColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorFrontCol(Opposition).obj");
	// ��]���鏰�̌��R���C�_�[(����)
	CResourceManager::Load<CModel>("RotateFloorBackColOpposition", "GameGimmick\\Gimmick\\Rotate\\RotateFloorBackCol(Opposition).obj");

	// �����̒�q�I�u�W�F�N�g
	CResourceManager::Load<CModel>("4Metalladder", "GameGimmick\\SeesawStage\\SeesawStage(MetalLadder).obj");
	// �����̒�q�I�u�W�F�N�g(Col)
	CResourceManager::Load<CModel>("4MetalladderCol", "GameGimmick\\SeesawStage\\SeesawStage(MetalLadderCol).obj");
	// �����̒�q�I�u�W�F�N�g(TopCol)
	CResourceManager::Load<CModel>("4MetalladderTopCol", "GameGimmick\\SeesawStage\\SeesawStage(MetalLadderColTop).obj");

	// �Z�[�u�|�C���g���f��
	CResourceManager::Load<CModel>("SavePoint", "GameGimmick\\Gimmick\\SaveFlag\\SavePoint.obj");

	// �n�e�i�u���b�N(�A�C�e���ۗL)
	CResourceManager::Load<CModel>("HatenaBlock", "GameGimmick\\Object\\hatena.obj");
	// �n�e�i�u���b�N(�A�C�e���s�ۗL)
	CResourceManager::Load<CModel>("HatenaBlockAfter", "GameGimmick\\Object\\UsedHatenaBlock.obj");
	// �����K�u���b�N
	CResourceManager::Load<CModel>("RengaBlock", "GameGimmick\\Object\\RengaBlock.obj");
	
	// �����f��
	CResourceManager::Load<CModel>("Meat", "Item\\StageItem\\niku.obj");
	// �񕜃I�u�W�F�N�g
	CResourceManager::Load<CModel>("Heart", "Item\\StatusItem\\Heart.obj");
	// ���G�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Star", "Item\\StatusItem\\Star.obj");
	// ���_�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Medal", "Item\\StatusItem\\Medal.obj");
	// �񕜖�I�u�W�F�N�g
	CResourceManager::Load<CModel>("Healing", "Item\\StatusItem\\HealingItem.obj");
	// �U���̓A�b�v���f��
	CResourceManager::Load<CModel>("AttackPotion", "Item\\StatusItem\\AttackPotion.obj");

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

	// �s�R�����
	CResourceManager::Load<CModelX>("Pico", "Character\\PicoChan\\PicoChan.x");

	CInput::ShowCursor(false);

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	mpFeild = new CSeesawAdventure();
	mpFeild->Position(0.0f, 0.0f, 0.0f);
	mpFeild->Scale(4.0f, 4.0f, 4.0f);
	mpFeild->Rotate(0.0f, 0.0f, 0.0f);
	AddTask(mpFeild);

	// �����R���C�_�[
	mpFallCol = new CSeesawStageFallCol();
	mpFallCol->Scale(4.0f, 4.0f, 4.0f);
	AddTask(mpFallCol);

	// ��
	mpSky = new CStageSky();
	mpSky->Scale(150.0f, 150.0f, 150.0f);
	AddTask(mpSky);

	// �Z�[�u�|�C���g1
	CSavePoint1* savepoint1 = new CSavePoint1
	(
		CVector(328.0f, -192.0f, -546.0f),
		CVector(7.0f, 7.0f, 7.0f),
		CVector(0.0f, 10.0f, 0.0f)
	);
	savepoint1->Rotation(0.0f, 90.0f, 0.0f);
	AddTask(savepoint1);

	// �V�[�\�[���f��
	CSeesaw* seesaw1 = new CSeesaw
	(
		CVector(328.0f, -277.0f, -875.0f),
		CVector(6.5f, 5.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 40.0f, 40.0f, 20.0f, 20.0f
	);
	AddTask(seesaw1);

	// �V�[�\�[���f��
	CSeesaw* seesaw2 = new CSeesaw
	(
		CVector(328.0f, -237.0f, -790.0f),
		CVector(6.5f, 5.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 40.0f, 40.0f, 20.0f, 20.0f
	);
	AddTask(seesaw2);

	// �V�[�\�[���f��
	CSeesaw* seesaw3 = new CSeesaw
	(
		CVector(328.0f, -217.0f, -744.0f),
		CVector(6.5f, 5.5f, 6.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 40.0f, 40.0f, 20.0f, 20.0f
	);
	AddTask(seesaw3);

	// ��]���鏰
	CRotateFloorTimeGimmick* timefloor = new CRotateFloorTimeGimmick
	(
		CVector(328.0f, -191.0f, -618.0f),
		CVector(5.0f, 5.0f, 5.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(timefloor);

	// �����V�[�\�[���f��
	CSplitSeesaw* splits1 = new CSplitSeesaw
	(
		CVector(328.0f, -260.0f, -828.0f),
		CVector(1.0f, 1.5f, 1.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 35.0f, 35.0f, 10.0f, 10.0f
	);
	AddTask(splits1);

	// �����V�[�\�[���f��
	CSplitSeesaw* splits2 = new CSplitSeesaw
	(
		CVector(328.0f, -192.0f, -370.0f),
		CVector(1.0f, 1.5f, 1.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 35.0f, 35.0f, 10.0f, 10.0f
	);
	AddTask(splits2);

	// �����V�[�\�[���f��
	CSplitSeesaw* splits3 = new CSplitSeesaw
	(
		CVector(328.0f, -175.0f, -336.0f),
		CVector(1.0f, 1.5f, 1.5f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer
		, 45.0f, 45.0f, 15.0f, 15.0f
	);
	AddTask(splits3);

	// �o�l(��ƃo�l)
	CSpring* spring1 = new CSpring
	(
		CVector(328.0f, -306.0f, -918.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(spring1);
	// �o�l(��)
	CSpringLower* springlower1 = new CSpringLower
	(
		CVector(328.0f, -306.0f, -918.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(springlower1);

	// �o�l(��ƃo�l)
	CSpring* spring2 = new CSpring
	(
		CVector(328.0f, -192.0f, -425.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(spring2);
	// �o�l(��)
	CSpringLower* springlower2 = new CSpringLower
	(
		CVector(328.0f, -192.0f, -425.0f),
		CVector(2.0f, 2.0f, 2.0f),
		CVector(0.0f, 0.0f, 0.0f)
	);
	AddTask(springlower2);

	// �����K�u���b�N1
	CRengaBlock* renga1 = new CRengaBlock
	(
		CVector(300.0f, -150.0f, -80.0f),
		CVector(9.0f, 9.0f, 9.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga1);
	// �n�e�i�u���b�N1
	CHatenaBlock* hatena1 = new CHatenaBlock
	(
		CVector(287.0f, -150.0f, -80.0f),
		CVector(9.0f, 9.0f, 9.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(hatena1);
	// �����K�u���b�N1
	CRengaBlock* renga2 = new CRengaBlock(
		CVector(274.0f, -150.0f, -80.0f),
		CVector(9.0f, 9.0f, 9.0f),
		ETag::ePlayer, ELayer::ePlayer
	);
	AddTask(renga2);

	// �o�����Ԃ��쐬
	CMetalLadder* metalladder = new CMetalLadder
	(
		"4Metalladder", "4MetalladderCol", "4MetalladderTopCol",
		CVector(0.0f, 15.0f, 0.0f),	// ������̈ړ�
		CVector(0.0f, 0.0f, 15.0f)	// ���ʕ����̈ړ�
	);
	metalladder->Scale(4.0f, 4.0f, 4.0f);
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

	// �s�R�����
	CPicoChan* pico = new CPicoChan();
	pico->Scale(15.5f, 15.5f, 15.5f);
	pico->Position(415.0f, -127.0f, -80.0f);
	pico->SetCenterPoint(CVector(415.0f, -125.0f, -80.0f),30.0f);
	AddTask(pico);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	// �����l�_ : 333.0f, -277.0f, -988.0f
	CVector playerPos = CVector(328.0f, -277.0f, -958.0f);
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