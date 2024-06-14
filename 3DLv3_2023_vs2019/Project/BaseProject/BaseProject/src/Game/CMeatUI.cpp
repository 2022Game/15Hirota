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
	bool Meat1 = meat1->IsMeat1(); 
	bool Meat2 = meat2->IsMeat2();
	bool Meat3 = meat3->IsMeat3();

	for (int i = 0; i < mAcquisition.size(); ++i)
	{
		CImage* item1 = mAcquisition[0];
		CImage* item2 = mAcquisition[1];
		CImage* item3 = mAcquisition[2];

		// �擾��ԂɊ�Â��Ď擾�ς݉摜��`�悷��
		if (Meat1)
		{
			item1->Render();
		}
		else
		{
			item1->SetEnable(false);
		}
		if (Meat2)
		{
			item2->Render();
		}
		else
		{
			item2->SetEnable(false);
		}
		if (Meat3)
		{
			item3->Render();
		}
		else
		{
			item3->SetEnable(false);
		}
	}

	for (int i = 0; i < mUnacquired.size(); i++)
	{
		CImage* item1 = mUnacquired[0];
		CImage* item2 = mUnacquired[1];
		CImage* item3 = mUnacquired[2];
		if (!Meat1)
		{
			item1->Render();
		}
		else
		{
			item1->SetEnable(false);
		}
		if (!Meat2)
		{
			item2->Render();
		}
		else
		{
			item2->SetEnable(false);
		}
		if (!Meat3)
		{
			item3->Render();
		}
		else
		{
			item3->SetEnable(false);
		}
	}
}