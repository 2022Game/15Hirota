#include "CTitleMenu.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CImage.h"

#define MENU_ALPHA 0.75f

// �R���X�g���N�^
CTitleMenu::CTitleMenu()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mIsOpened(false)
{
	mpTitleMenu = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpTitleMenu->SetCenter(mpTitleMenu->GetSize() * 0.5f);
	mpTitleMenu->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpTitleMenu->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);

	const char* menuItems[] = { "UI/TitleUI/GameStart.png", "UI/TitleUI/EXIT.png" };
	int stageMenuCount = 2;
	float spaceX = (float)WINDOW_WIDTH / (stageMenuCount + 1);
	for (int i = 0; i < stageMenuCount; i++)
	{
		CImage* item = new CImage
		(
			menuItems[i],
			ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
			false, false
		);
		item->SetSize(400.0f, 300.0f);
		item->SetCenter(item->GetSize() * 0.5f);
		float posX = spaceX * (i + 1) - item->GetSize().X() / 2.0f + 200.0f;
		float posY = (float)WINDOW_HEIGHT / 2.0f + 100.0f;
		item->SetPos(posX, posY);
		item->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);
		mTitleMenuItems.push_back(item);
	}

	SetEnable(false);
	SetShow(false);
}

// �f�X�g���N�^
CTitleMenu::~CTitleMenu()
{
	// �폜�����Ƃ��Ƀ��j���[���J�����܂܂ł���΁A
	// ���j���[�����
	if (mIsOpened)
	{
		Close();
	}
}

// �J��
void CTitleMenu::Open()
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

// ����
void CTitleMenu::Close()
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

// �}�E�X����
void CTitleMenu::HandleMouseInput()
{
	// �}�E�X���N���b�N���ꂽ���ǂ������`�F�b�N
	if (CInput::PullKey(VK_LBUTTON))
	{
		// �}�E�X�̍��W���擾
		CVector2 mousePos = CInput::GetMousePos();

		// �}�E�X���N���b�N���ꂽ�ʒu���`�F�b�N���A�Y�����郁�j���[���ڂ����
		for (int i = 0; i < mTitleMenuItems.size(); i++)
		{
			CImage* item = mTitleMenuItems[i];
			// ���j���[���ڂ̍���̍��W�ƉE���̍��W���擾
			CVector2 itemPos = item->GetPos();
			CVector2 itemSize = item->GetSize();
			float left = itemPos.X() - itemSize.X() / 2.6f;		// ���[�̍��W
			float right = itemPos.X() + itemSize.X() / 2.6f;	// �E�[�̍��W
			float top = itemPos.Y() - itemSize.Y() / 9.0f;		// ��[�̍��W
			float bottom = itemPos.Y() + itemSize.Y() / 9.0f;	// ���[�̍��W

			// �}�E�X�����j���[���ڂ̏�ɂ��邩�ǂ���
			if (mousePos.X() >= left && mousePos.X() <= right &&
				mousePos.Y() >= top && mousePos.Y() <= bottom)
			{
				// ���j���[���ڂ��N���b�N���ꂽ�ꍇ�̏���
				Decide(i);
				break;
			}
		}
	}
}

bool CTitleMenu::IsOpened() const
{
	return mIsOpened;
}

// �ǂ̃��j���[�ɂ��邩
void CTitleMenu::Decide(int select)
{
	switch (select)
	{
	case 0:
		CTitleMenu::Close();
		CSceneManager::Instance()->LoadScene(EScene::eGame);
		/*CStageManager::LoadStage(0);
		CGameManager::SetStageNo(0);*/
		break;
	case 1:
		System::ExitGame();
		break;
	case 2:
		break;
	}
}

// �X�V����
void CTitleMenu::Update()
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
	/*int itemCount = mTitleMenuItems.size();
	if (CInput::PushKey(VK_LEFT))
	{
		mSelectIndex = (mSelectIndex + itemCount - 1) % itemCount;
	}
	else if (CInput::PushKey(VK_RIGHT))
	{
		mSelectIndex = (mSelectIndex + 1) % itemCount;
	}
	else if (CInput::PushKey(VK_RETURN))
	{
		Decide(mSelectIndex);
	}*/

	mpTitleMenu->Update();
	for (CImage* item : mTitleMenuItems)
	{
		item->Update();
	}
	//mpTitleMenuFrame->Update();
}

// �`�揈��
void CTitleMenu::Render()
{
	mpTitleMenu->Render();
	for (int i = 0; i < mTitleMenuItems.size(); i++)
	{
		CImage* item = mTitleMenuItems[i];
		item->Render();

		/*if (i == mSelectIndex)
		{
			mpTitleMenuFrame->SetPos(item->GetPos());
			mpTitleMenuFrame->Render();
		}*/
	}
}