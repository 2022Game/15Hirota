#include "CMeatUI.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CImage.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"

#define MENU_ALPHA 0.75f

// �R���X�g���N�^
CMeatUI::CMeatUI()
	: CTask(ETaskPriority::eUI,0,ETaskPauseType::eGame)
	, mIsOpened(false)
{
	// ���擾���̓��̃A�C�e���摜
	int Count = 3;
	float spaceX = (float)WINDOW_WIDTH * 0.3f / (Count + 1);
	for (int i = 0; i < Count; i++)
	{
		CImage* item = new CImage
		(
			"UI/StageUI/Meat(Unacquired).png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetSize(100.0f, 200.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = spaceX * (i + 1); // ��ʕ�����v�Z
		float posY = (float)WINDOW_HEIGHT * 0.1f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mUnacquired.push_back(item);
	}

	// �擾���̓��̃A�C�e���摜
	for (int i = 0; i < Count; i++)
	{
		CImage* item = new CImage
		(
			"UI/StageUI/Meat(Acquisition).png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetSize(100.0f, 200.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = spaceX * (i + 1); // ��ʕ�����v�Z
		float posY = (float)WINDOW_HEIGHT * 0.1f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mAcquisition.push_back(item);
	}

	SetEnable(false);
	SetShow(false);
}

// �f�X�g���N�^
CMeatUI::~CMeatUI()
{
	if (mIsOpened)
	{
		Close();
	}
}

// �J��
void CMeatUI::Open()
{
	// ���ɊJ���Ă�����A�������Ȃ�
	if (mIsOpened) return;

	mIsOpened = true;
	SetEnable(true);
	SetShow(true);
	// ���j���[�J�����t���O���グ��
	mIsOpened = true;
}

// ����
void CMeatUI::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	// ���j���[���J�����t���O������
	mIsOpened = false;
}

// �J���Ă��邩�ǂ���
bool CMeatUI::IsOpened() const
{
	return mIsOpened;
}

// �X�V����
void CMeatUI::Update()
{

}

// �`�揈��
void CMeatUI::Render()
{
	CMeat1* meat1 = CMeat1::Instance();
	CMeat2* meat2 = CMeat2::Instance();
	CMeat3* meat3 = CMeat3::Instance();
	bool Meat[] = { meat1->IsMeat1(), meat2->IsMeat2(), meat3->IsMeat3() };

	// �擾�ς݉摜�̕`��
	for (int i = 0; i < mAcquisition.size(); ++i)
	{
		CImage* item = mAcquisition[i];
		if (Meat[i])
		{
			item->Render();
		}
		else
		{
			item->SetEnable(false);
		}
	}

	// ���擾�摜�̕`��
	for (int i = 0; i < mUnacquired.size(); ++i)
	{
		CImage* item = mUnacquired[i];
		if (!Meat[i])
		{
			item->Render();
		}
		else
		{
			item->SetEnable(false);
		}
	}
}