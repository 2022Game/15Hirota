#include "CClimbUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"

CClimbUI::CClimbUI()
	: mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpUI = new CImage("EUI");
	mpUI->SetSize(150.0f, 150.0f);
}

// �f�X�g���N�^
CClimbUI::~CClimbUI()
{

}

// �폜
void CClimbUI::Kill()
{
	CTask::Kill();
	mpUI->Kill();
}

void CClimbUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

void CClimbUI::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos - CVector(0.0f, 0.0f, 0.0f));

	//// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	//// �Q�[�W��\�����Ȃ�
	//if (screenPos.Z() < 0.0f)
	//{
	//	SetShow(false);
	//	return;
	//}

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;
}

void CClimbUI::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpUI->SetPos(mPosition);
	mpUI->SetShow(IsShow());

	// �t���[���̒��S�ʒu
	mpUI->SetCenter
	(
		0.0f * mCenterRatio.X(),
		0.0f * mCenterRatio.Y()
	);
}