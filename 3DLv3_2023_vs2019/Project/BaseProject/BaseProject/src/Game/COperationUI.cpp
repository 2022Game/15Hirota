#include "COperationUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"
#include "CStageManager.h"

// �R���X�g���N�^
COperationUI::COperationUI(std::string path)
	: mScale(0.0f)
{
	// T�摜
	mpKay = new CImage
	(
		path.c_str(),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	CVector2 size(150.0f, 150.0f);
	mpKay->SetSize(size);
	mpKay->SetCenter(size * 0.5f);

	// �o�b�N�O���E���h�摜
	mpBG = new CImage
	(
		"Frame",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	mpBG->SetSize(size);
	mpBG->SetCenter(size * 0.5f);
	mpBG->SetAlpha(0.7f);
}

// �f�X�g���N�^
COperationUI::~COperationUI()
{
	SAFE_DELETE(mpBG);
	SAFE_DELETE(mpKay);
}

// �폜
void COperationUI::Kill()
{
	CTask::Kill();
}

// ���[���h���W��ݒ�
void COperationUI::SetWorldPos(const CVector& worldPos)
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

// �X�V����
void COperationUI::Update()
{
	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;

	mpBG->SetPos(pos);
	mpBG->SetShow(IsShow());
	mpKay->SetPos(pos);
	mpKay->SetShow(IsShow());
}

// �`�揈��
void COperationUI::Render()
{
	mpBG->Render();
	mpKay->Render();
}