#include "COperationInstructionsUI.h"
#include "Maths.h"
#include "CImage.h"
#include "CCamera.h"
#include "CSignboard.h"
#include "CPlayer.h"
#include "CStageManager.h"

// UI�f�[�^
const COperationInstructionsUI::UIData COperationInstructionsUI::UI_DATA[] =
{
	// �摜��
	{"TUI"},
	{"EnterUI"},
};

// �R���X�g���N�^
COperationInstructionsUI::COperationInstructionsUI(std::string path)
	: mPath(path)
	, mCenterRatio(0.0f, 0.0f)
	, mScale(0.0f)
{
	//// UI�摜�f�[�^
	//int datasize = ARRAY_SIZE(UI_DATA);
	//for (int i = 0; i < datasize; i++)
	//{
	//	const UIData& data = UI_DATA[i];
	//	CImage* ui = new CImage
	//	(
	//		data.UIName.c_str(), // UIData�̉摜�����g�p
	//		ETaskPriority::eUI,
	//		0,
	//		ETaskPauseType::eGame,
	//		false, false
	//	);
	//	CVector2 size(150.0f, 150.0f);
	//	mUIimages[i]->SetSize(size);
	//	mUIimages[i]->SetCenter(size * 0.5f);
	//	mUIimages.push_back(ui);
	//}

	// �o�b�N�O���E���h�摜
	mpUI = new CImage
	(
		"TUI",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	CVector2 size(150.0f, 150.0f);
	mpUI->SetSize(size);
	mpUI->SetCenter(size * 0.5f);

	// �o�b�N�O���E���h�摜
	mpBG = new CImage
	(
		"PBarImage",
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eGame,
		false, false
	);
	mpBG->SetSize(size);
	mpBG->SetCenter(size * 0.5f);
}

// �f�X�g���N�^
COperationInstructionsUI::~COperationInstructionsUI()
{
	SAFE_DELETE(mpBG);
	SAFE_DELETE(mpUI);
	/*CStageManager::RemoveTask(this);
	int size = mUIimages.size();
	for (int i = 0; i < size; i++)
	{
		CImage* img = mUIimages[i];
		mUIimages[i] = nullptr;
		SAFE_DELETE(img);
	}
	mUIimages.clear();*/
}

// �폜
void COperationInstructionsUI::Kill()
{
	CTask::Kill();
}

// �摜�̃Z���^�[�T�C�Y��ݒ�
void COperationInstructionsUI::SetCenterRatio(const CVector2& ratio)
{
	mCenterRatio = ratio;
}

// ���[���h���W��ݒ�
void COperationInstructionsUI::SetWorldPos(const CVector& worldPos)
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
void COperationInstructionsUI::Update()
{
	// �Q�[�W�̈ʒu��ݒ�
	CVector2 pos = mPosition;

	/*for (CImage* img : mUIimages)
	{
		img->SetPos(pos);
		img->SetShow(IsShow());
		img->Update();
	}*/

	mpBG->SetPos(pos);
	mpBG->SetShow(IsShow());
	mpUI->SetPos(pos);
	mpUI->SetShow(IsShow());
}

// �`�揈��
void COperationInstructionsUI::Render()
{
	mpBG->Render();
	mpUI->Render();

	/*int size = ARRAY_SIZE(UI_DATA);
	for (int i = 0; i < size; i++)
	{
		mUIimages[i]->Render();
	}*/
}