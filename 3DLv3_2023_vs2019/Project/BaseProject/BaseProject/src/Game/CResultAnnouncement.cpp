#include "CResultAnnouncement.h"
#include "Maths.h"
#include "CInput.h"
#include "CSceneManager.h"
#include "CTaskManager.h"
#include "CBGMManager.h"
#include "CStageManager.h"
#include "CGameManager.h"
#include "CImage.h"
#include "CResult.h"

#define MENU_ALPHA 0.65f

// �R���X�g���N�^
CResultAnnouncement::CResultAnnouncement()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mSelectIndex(0)
	, mElapsedTime(0.0f)
	, mAlpha(0.0f)
	, mIsOpened(false)
{
	/*mpResultsMenu = new CImage
	(
		"UI/menu_back.png",
		ETaskPriority::eUI, 0, ETaskPauseType::eMenu,
		false, false
	);
	mpResultsMenu->SetCenter(mpResultsMenu->GetSize() * 0.5f);
	mpResultsMenu->SetPos(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
	mpResultsMenu->SetColor(1.0f, 1.0f, 1.0f, MENU_ALPHA);*/

	const char* menuItems[] = { "UI/ResultUI/Continue.png", "UI/ResultUI/End.png" };
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
		item->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		mResultsMenuItems.push_back(item);
	}

	// ���U���g�摜
	int resultCount = 3;
	for (int i = 0; i < resultCount; i++)
	{
		Result Result;
		const char* imagePath;

		// mABCItems�ɍ��킹�ĉ摜�ƃA�C�e���̎�ނ�ݒ�
		switch (i)
		{
		case 0:
			Result = Result::A;
			imagePath = "UI/ResultUI/A.png";
			break;
		case 1:
			Result = Result::B;
			imagePath = "UI/ResultUI/B.png";
			break;
		case 2:
			Result = Result::C;
			imagePath = "UI/ResultUI/C.png";
			break;
		}

		// mABCItems�̉摜��`��
		CImage* abc = new CImage
		(
			imagePath,
			ETaskPriority::eUI, 0, ETaskPauseType::eGame,
			false, false
		);
		abc->SetSize(300.0f, 350.0f);
		abc->SetCenter(abc->GetSize() * 0.5f);
		float posX = (float)WINDOW_WIDTH * 0.65f;
		float posY = (float)WINDOW_HEIGHT* 0.4f;
		abc->SetPos(posX, posY);
		abc->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mABCItems.push_back(std::make_pair(Result, abc));
	}

	SetEnable(false);
	SetShow(false);
}

// �f�X�g���N�^
CResultAnnouncement::~CResultAnnouncement()
{
	// �폜�����Ƃ��Ƀ��j���[���J�����܂܂ł���΁A
	// ���j���[�����
	if (mIsOpened)
	{
		Close();
	}
}

// �J��
void CResultAnnouncement::Open()
{
	// ���ɊJ���Ă�����
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
void CResultAnnouncement::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O�����낷
	mIsOpened = false;
}

// �}�E�X����
void CResultAnnouncement::HandleMouseInput()
{
	// �}�E�X���N���b�N���ꂽ���ǂ������`�F�b�N
	if (CInput::PullKey(VK_LBUTTON))
	{
		// �}�E�X�̍��W���擾
		CVector2 mousePos = CInput::GetMousePos();

		// �}�E�X���N���b�N���ꂽ�ʒu���`�F�b�N���A�Y�����郁�j���[���ڂ����
		for (int i = 0; i < mResultsMenuItems.size(); i++)
		{
			CImage* item = mResultsMenuItems[i];
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

bool CResultAnnouncement::IsOpened() const
{
	return mIsOpened;
}

// �ǂ̃��j���[�ɂ��邩
void CResultAnnouncement::Decide(int select)
{
	switch (select)
	{
	case 0:
		CResultAnnouncement::Close();
		CGameManager::GameStart();
		break;
	case 1:
		System::ExitGame();
		break;
	case 2:
		break;
	}
}

// �X�V����
void CResultAnnouncement::Update()
{
	HandleMouseInput(); // �}�E�X���͂�����
	if (IsOpened())
	{
		CInput::ShowCursor(true);
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;

			// �\������\���Ɋ|���鎞�ԁi�b�j
			static const float fadeTime = 4.0f;
			// �ő�A���t�@�l
			static const float fadeAlpha = 1.0f;

			//�t�F�[�h�w�i�̕\�����Ԃ��o�߂��Ă��Ȃ�
			if (mElapsedTime < fadeTime)
			{
				//�o�ߎ��Ԃɍ��킹�ăA���t�@�l��ݒ�
				float alpha = mElapsedTime / fadeTime;
				item->SetAlpha(fadeAlpha * alpha);
				//1�t���[���̌o�ߎ��Ԃ����Z�i���j
				mElapsedTime += 0.0016f;
			}
			//�t�F�[�h�w�i�̕\�����Ԃ��o�߂���
			else
			{
				//�t�F�[�h�w�i�����S�ɕ\������
				item->SetAlpha(fadeAlpha);
				return;
			}
		}
	}
	else
	{
		CInput::ShowCursor(false);
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;
			
			item->SetAlpha(0.0f);
			mElapsedTime = 0.0f;
		}
	}

	//mpResultsMenu->Update();
	for (CImage* item : mResultsMenuItems)
	{
		item->Update();
	}
}

// �`�揈��
void CResultAnnouncement::Render()
{
	//mpResultsMenu->Render();
	for (int i = 0; i < mResultsMenuItems.size(); i++)
	{
		CImage* item = mResultsMenuItems[i];
		item->Render();
	}

	// �摜�p�X���X�V
	CResult* result = CResult::Instance();
	int score = result->GetTotalScore();

	// mABCItems���̉摜��`��
	for (int i = 0; i < mABCItems.size(); i++)
	{
		// �X�R�A�ɉ��������ʂ��v�Z
		Result resultType;
		if (score >= 2500)
		{
			resultType = Result::A;
		}
		else if (score < 2500 && score >= 1500)
		{
			resultType = Result::B;
		}
		else
		{
			resultType = Result::C;
		}

		// �A�C�e���̎�ނ��擾
		Result itemResult = mABCItems[i].first;

		// �摜�p�X����v������̂�`��
		if (itemResult == resultType)
		{
			// �`��
			mABCItems[i].second->Render();
			Update();
		}
	}
}