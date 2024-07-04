#include "CButton1UI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"

CButton1UI::CButton1UI()
	: mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpUI = new CImage("EnterUI");
	mpUI->SetSize(100.0f, 100.0f);
}

// �f�X�g���N�^
CButton1UI::~CButton1UI()
{

}

// �폜
void CButton1UI::Kill()
{
	CTask::Kill();
	mpUI->Kill();
}

void CButton1UI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

void CButton1UI::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos - CVector(0.0f,0.0f,0.0f));

	// ���߂��X�N���[�����W�����g�̍��W�ɐݒ�
	mPosition = screenPos;
}

void CButton1UI::Update()
{
	// �t���[���ʒu��ݒ�
	//CVector2 pos = mPosition - CVector2(FRAME_SIZE_X, 0.0f) * 0.5f;
	mpUI->SetPos(mPosition);
	mpUI->SetShow(IsShow());

	// �t���[���̒��S�ʒu
	mpUI->SetCenter
	(
		30.0f * mCenterRatio.X(),
		30.0f * mCenterRatio.Y()
	);
}