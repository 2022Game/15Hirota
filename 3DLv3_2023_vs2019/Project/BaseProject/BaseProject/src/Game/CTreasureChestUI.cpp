#include "CTreasureChestUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CPlayer.h"

CTreasureChestUI::CTreasureChestUI()
	: mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	mpUI = new CImage("TUI");
	mpUI->SetSize(150.0f, 150.0f);
}

// �f�X�g���N�^
CTreasureChestUI::~CTreasureChestUI()
{

}

// �폜
void CTreasureChestUI::Kill()
{
	CTask::Kill();
	mpUI->Kill();
}

void CTreasureChestUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

void CTreasureChestUI::SetWorldPos(const CVector& worldPos)
{
	// ���݂̃J�������擾
	CCamera* cam = CCamera::CurrentCamera();
	if (cam == nullptr) return;

	// �ݒ肳�ꂽ���[���h���W���X�N���[�����W�ɕϊ�
	CVector screenPos = cam->WorldToScreenPos(worldPos);

	// �ݒ肳�ꂽ���[���h���W���J�����̔w��ł���΁A
	// �Q�[�W��\�����Ȃ�
	if (screenPos.Z() < 0.0f)
	{
		SetShow(false);
		return;
	}

	// �X�N���[�����W��UI�̈ʒu�Ƃ��Đݒ�
	mPosition = screenPos;
}

void CTreasureChestUI::Update()
{
	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;
	//pos.X(pos.X() - 0.0f * mCenterRatio.X() * mScale);
	mpUI->SetPos(pos/* + CVector2(0.0f, 0.0f) * mScale*/);

	mpUI->SetShow(IsShow());

	// �Q�[�W�̒��S�ʒu��ݒ�
	mpUI->SetCenter
	(
		0.0f,
		0.0f
	);
}