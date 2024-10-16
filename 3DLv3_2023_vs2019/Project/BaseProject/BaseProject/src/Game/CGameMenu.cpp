#include "CGameMenu.h"
#include "CInput.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CImage.h"
#include "CStageManager.h"

#define MENU_ALPHA 0.75f

CGameMenu::CGameMenu()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mIsOpened(false)
{
	mpBackground = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpBackground->SetCenter(mpBackground->GetSize() * 0.5f);
	mpBackground->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpBackground->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);

	int menuItemCount = 3;
	float spaceY = (float)WINDOW_HEIGHT / (menuItemCount + 1);
	for (int i = 0; i < menuItemCount; i++)
	{
		CImage* item = new CImage
		(
			"UI/menu_item.png",
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = (1280.0f - 1024.0f + item->GetSize().X()) * 0.5f + 100.0f;
		item->SetPos(posX, spaceY * (i + 1));
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mMenuItems.push_back(item);
	}

	mpSelectFrame = new CImage
	(
		"UI/menu_item_select.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpSelectFrame->SetCenter(mpSelectFrame->GetSize() * 0.5f);
	mpSelectFrame->SetColor(1.0f, 0.5f, 0.0f, MENU_ALPHA);

	SetEnable(false);
	SetShow(false);
}

CGameMenu::~CGameMenu()
{
	CStageManager::RemoveTask(this);
	// �폜�����Ƃ��Ƀ��j���[���J�����܂܂ł���΁A
	// ���j���[�����
	if (mIsOpened)
	{
		Close();
	}
}

void CGameMenu::Open()
{
	// ���ɊJ���Ă�����A�������Ȃ�
	if (mIsOpened) return;

	SetEnable(true);
	SetShow(true);
	mSelectIndex = 0;
	CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O�𗧂Ă�
	mIsOpened = true;
}

void CGameMenu::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	//CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O������
	mIsOpened = false;
}

void CGameMenu::HandleMouseInput()
{
	// �}�E�X���N���b�N���ꂽ���ǂ������`�F�b�N
	if (CInput::PushKey(VK_LBUTTON))
	{
		// �}�E�X�̍��W���擾
		CVector2 mousePos = CInput::GetMousePos();

		// �}�E�X���N���b�N���ꂽ�ʒu���`�F�b�N���A�Y�����郁�j���[���ڂ����
		for (int i = 0; i < mMenuItems.size(); i++)
		{
			CImage* item = mMenuItems[i];
			// ���j���[���ڂ̍���̍��W�ƉE���̍��W���擾
			CVector2 itemPos = item->GetPos();
			CVector2 itemSize = item->GetSize();
			float left = itemPos.X() - itemSize.X() / 2.2f;		// ���[�̍��W
			float right = itemPos.X() + itemSize.X() / 2.2f;	// �E�[�̍��W
			float top = itemPos.Y() - itemSize.Y() / 3.5f;		// ��[�̍��W
			float bottom = itemPos.Y() + itemSize.Y() / 3.5f;	// ���[�̍��W

			// �}�E�X�����j���[���ڂ̏�ɂ��邩�ǂ���
			if (mousePos.X() >= left && mousePos.X() <= right &&
				mousePos.Y() >= top && mousePos.Y() <= bottom)
			{
				// ���j���[���ڂ��N���b�N���ꂽ�ꍇ�̏��������s
				Decide(i);
				break;
			}
		}
	}
}


bool CGameMenu::IsOpened() const
{
	return mIsOpened;
}

void CGameMenu::Decide(int select)
{
	switch (select)
	{
	case 0:
	case 1:
		break;
	case 2:
		Close();
		CInput::ShowCursor(false);
		break;
	}
}

void CGameMenu::Update()
{
	HandleMouseInput(); // �}�E�X���͂�����
	if (IsOpened())
	{
		CInput::ShowCursor(true);
	}
	else
	{
		CInput::ShowCursor(false);
	}

	int itemCount = mMenuItems.size();
	if (CInput::PushKey(VK_UP))
	{
		mSelectIndex = (mSelectIndex + itemCount - 1) % itemCount;
	}
	else if (CInput::PushKey(VK_DOWN))
	{
		mSelectIndex = (mSelectIndex + 1) % itemCount;
	}
	else if (CInput::PushKey(VK_RETURN))
	{
		Decide(mSelectIndex);
	}

	mpBackground->Update();
	for (CImage* item : mMenuItems)
	{
		item->Update();
	}
	mpSelectFrame->Update();
}

void CGameMenu::Render()
{
	mpBackground->Render();
	for (int i = 0; i < mMenuItems.size(); i++)
	{
		CImage* item = mMenuItems[i];
		item->Render();

		if (i == mSelectIndex)
		{
			mpSelectFrame->SetPos(item->GetPos());
			mpSelectFrame->Render();
		}
	}
}