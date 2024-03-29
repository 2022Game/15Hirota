#include "CStageSelectionStage.h"
#include "CGameCamera.h"
#include "CCamera.h"
#include "CStageSelection.h"
#include "CPlayer.h"
#include "CStageButton.h"
#include "CNeedle.h"

// �R���X�g���N�^
CStageSelectionStage::CStageSelectionStage()
{
	mStageNo = 0;
}

// �f�X�g���N�^
CStageSelectionStage::~CStageSelectionStage()
{

}

// �X�e�[�W�ǂݍ���
void CStageSelectionStage::Load()
{
	CResourceManager::Load<CModel>("StageSelection", "Field\\StageSentaku.obj");				// �X�e�[�W�Z���N�g�X�e�[�W
	CResourceManager::Load<CModel>("StageSelectionFloorCol", "Field\\StageSentakuFloor.obj");	// �X�e�[�W�Z���N�g�X�e�[�W(��)
	CResourceManager::Load<CModel>("StageSelectionWallCol", "Field\\StageSentakuWall.obj");		// �X�e�[�W�Z���N�g�X�e�[�W(��)
	CResourceManager::Load<CModel>("StageButton", "Field\\Object\\StageBotan.obj");				// �X�e�[�W�{�^��
	CResourceManager::Load<CModel>("Needle", "Field\\Gimmick\\NeedleObject(needle).obj");		// �j�I�u�W�F�N�g�̐j
	CResourceManager::Load<CModel>("Needlebase", "Field\\Gimmick\\NeedleObject(base).obj");		// �j�I�u�W�F�N�g�̓y��
	CResourceManager::Load<CModel>("NeedleCol", "Field\\Gimmick\\NeedleObjectCol.obj");			// �j�I�u�W�F�N�g�̃R���C�_�[
	CResourceManager::Load<CModel>("NeedleBaseCol", "Field\\Gimmick\\NeedleObjectBaseCol.obj");	// �j�I�u�W�F�N�g�̃x�[�X�R���C�_�[

	// �w�i�F�ݒ�
	System::SetClearColor(0.1921569f, 0.3019608f, 0.4745098f, 1.0f);

	// �t�B�[���h
	CStageSelection* field = new CStageSelection();
	AddTask(field);

	// �X�e�[�W�I�����f��
	CStageButton* button = new CStageButton(
		CVector(150.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	AddTask(button);

	// �j���f��
	CNeedle* needle = new CNeedle(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlePos = CVector(100.0f, 11.0f, 0.0f);
	if (needle != nullptr)
	{
		needle->SetStartPosition(needlePos);
	}
	AddTask(needle);
	// �j���f���x�[�X
	CNeedleBase* needlebase = new CNeedleBase(
		CVector(100.0f, 11.0f, 0.0f),
		CVector(10.0f, 10.0f, 10.0f),
		CVector(0.0f, 0.0f, 0.0f),
		ETag::ePlayer, ELayer::ePlayer);
	CVector needlebasePos = CVector(100.0f, 11.0f, 0.0f);
	if (needlebase != nullptr)
	{
		needlebase->SetStartPosition(needlebasePos);
	}
	AddTask(needlebase);

	// �����X�^�[(�v���C���[)
	CPlayer* player = CPlayer::Instance();
	CVector playerPos = CVector(-245.0f, 60.0f, 0.0f);
	if (player != nullptr)
	{
		player->SetStartPosition(playerPos);
		player->Rotation(0.0f, -90.0f, 0.0f);
	}

	// �J�����̈ʒu�ƌ�����ݒ�
	CVector camPos = playerPos + player->Rotation() * CVector(0.0f, 30.0f, -100.0f);
	CCamera* mainCamera = CCamera::MainCamera();
	mainCamera->LookAt(camPos, playerPos, CVector::up);
	mainCamera->SetFollowTargetTf(player);
	// �X�t�B�A�����b�V�����炢
	//mainCamera->AddCollider(field->GetWallCol());
}

// �X�e�[�W�j��
void CStageSelectionStage::Unload()
{
	// �x�[�X�X�e�[�W�j������
	CStageBase::Unload();
}