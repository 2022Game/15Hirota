#include "CSignboardUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"

CSignboardUI::CSignboardUI()
	: mCenterRatio(0.0f,0.0f)
	, mScale(0.0f)
{
	mpCSiUI = new CImage("SignboardUI");
	mpCSiUI->SetSize(30.0f, 30.0f);
}

// �f�X�g���N�^
CSignboardUI::~CSignboardUI()
{

}

// �폜
void CSignboardUI::Kill()
{
	CTask::Kill();
	mpCSiUI->Kill();
}

void CSignboardUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

void CSignboardUI::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	CVector playerPos = CPlayer::Instance()->Position();

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos - CVector(0.0f, 1.0f, 0.0f));


	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}


	float distanceToPlayer = (worldPos - playerPos).Length();
	if (CSignboard::Instance()->IsFoundPlayer())
	{
		SetShow(true);
	}
	else
	{
		SetShow(false);	
	}

	//CDebugPrint::Print("SetShow %s\n", IsShow() ? "true" : "false");

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;

}

void CSignboardUI::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpCSiUI->SetPos(mPosition);
	mpCSiUI->SetSize(CVector2(30.0f, 30.0f));
	mpCSiUI->SetShow(IsShow());


	// �t���[���̒��S�ʒu
	mpCSiUI->SetCenter
	(
		30.0f * mCenterRatio.X(),
		30.0f * mCenterRatio.Y()
	);
}