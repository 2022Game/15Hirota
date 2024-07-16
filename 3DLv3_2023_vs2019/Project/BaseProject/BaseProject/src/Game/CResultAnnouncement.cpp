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
#include "CCutInResult.h"
#include "CText.h"
#include "CExpandButton.h"
#include "CFade.h"
#include "Easing.h"
#include "CFont.h"
#include "CPlayer.h"

#define MENU_ALPHA 0.65f
// �^�C�g�����j���[�̃A�j���[�V��������
#define OPEN_ANIM_TIME 0.25f
// �^�C�g�����j���[�̃A�j���[�V������̑҂�����
#define OPENED_WAIT_TIME 0.5f

// �X�e�[�W�^�C�}�[�̃C���X�^���X
CResultAnnouncement* CResultAnnouncement::spInstance = nullptr;

CResultAnnouncement* CResultAnnouncement::Instance()
{
	if (spInstance == nullptr)
	{
		spInstance = new CResultAnnouncement();
	}
	return spInstance;
}

// �R���X�g���N�^
CResultAnnouncement::CResultAnnouncement()
	: CTask(ETaskPriority::eUI, 0, ETaskPauseType::eDefault)
	, mState(EState::eNone)
	, mStateStep(0)
	, mSelectIndex(0)
	, mAlpha(0.0f)
	, mElapsedTime(0.0f)
	, mElapsedABCTime(0.0f)
	, mElapsedRankTime(0.0f)
	, mIsEnd(false)
	, mIsOpened(false)
	, mResultOpened(false)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

	// �����N�I�̃t�H���g�f�[�^�𐶐�
	mpRankFont = new CFont("res\\Font\\toroman.ttf");
	mpRankFont->SetFontSize(70);
	mpRankFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
	mpRankFont->SetLineLength(WINDOW_WIDTH);

	// �����N�I�̃e�L�X�g�𐶐�
	mpRankText = new CText
	(
		mpRankFont, 70,
		CVector2(WINDOW_WIDTH * 0.4f, 300.0f),
		CVector2(WINDOW_WIDTH, WINDOW_HEIGHT),
		CColor(0.0f, 0.0f, 0.0f, 0.0f),
		ETaskPriority::eUI,
		0,
		ETaskPauseType::eDefault,
		false,
		false
	);
	mpRankText->SetText("�����N�I");
	mpRankText->SetEnableOutline(true);
	mpRankText->SetOutlineColor(CColor(0.9f, 0.9f, 0.9f));

	// [START]�{�^���𐶐�
	CExpandButton* btn1 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.3f, 600.0f),
		CVector2(250.0f, 250.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	// �{�^���̉摜��ǂݍ���
	btn1->LoadButtonImage("UI/ResultUI/Continue.png", "UI/ResultUI/Continue.png");
	// �{�^���N���b�N���ɌĂяo�����R�[���o�b�N�֐���ݒ�
	btn1->SetOnClickFunc(std::bind(&CResultAnnouncement::OnClickContinue, this));
	// �{�^���͍ŏ��͖��������āA�X�P�[���l��0�ɂ��Ă���
	btn1->SetEnable(false);
	btn1->SetScale(0.0f);
	// �{�^�����X�g�ɒǉ�
	mButtons.push_back(btn1);

	// [QUIT]�{�^���𐶐�
	CExpandButton* btn2 = new CExpandButton
	(
		CVector2(WINDOW_WIDTH * 0.7f, 600.0f),
		CVector2(250.0f, 250.0f),
		ETaskPriority::eUI, 0, ETaskPauseType::eGame,
		false, false
	);
	btn2->LoadButtonImage("UI/ResultUI/End.png", "UI/ResultUI/End.png");
	btn2->SetOnClickFunc(std::bind(&CResultAnnouncement::OnClickEnd, this));
	btn2->SetEnable(false);
	btn2->SetScale(0.0f);
	mButtons.push_back(btn2);

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
		float posX = (float)WINDOW_WIDTH * 0.75f;
		float posY = (float)WINDOW_HEIGHT * 0.4f;
		abc->SetPos(posX, posY);
		abc->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
		mABCItems.push_back(std::make_pair(Result, abc));
	}

	SetEnable(false);
}

// �f�X�g���N�^
CResultAnnouncement::~CResultAnnouncement()
{
	CStageManager::RemoveTask(this);

	spInstance = nullptr;

	//SAFE_DELETE(mpStartText);
	SAFE_DELETE(mpRankFont);
	SAFE_DELETE(mpRankText);

	int size = mButtons.size();
	for (int i = 0; i < size; i++)
	{
		CButton* btn = mButtons[i];
		mButtons[i] = nullptr;
		SAFE_DELETE(btn);
	}
	mButtons.clear();

	// �폜�����Ƃ��Ƀ��j���[���J�����܂܂ł���΁A
	// ���j���[�����
	if (mIsOpened)
	{
		Close();
	}
}

// �^�C�g����ʏI����
bool CResultAnnouncement::IsEnd() const
{
	return mIsEnd;
}

// �Q�[�����J�n���邩
bool CResultAnnouncement::IsStartGame() const
{
	// �I�����ڂ�1�ڂȂ�΁A�Q�[���J�n
	return mSelectIndex == 0;
}

// �Q�[�����I�����邩
bool CResultAnnouncement::IsExitGame() const
{
	// �I�����ڂ�3�ڂȂ�΁A�Q�[���I��
	return mSelectIndex == 1;
}

// ��Ԑ؂�ւ�
void CResultAnnouncement::ChangeState(EState state)
{
	if (state == mState) return;
	mState = state;
	mStateStep = 0;
	mElapsedTime = 0.0f;
}

// [CONTINUE]�N���b�N���̃R�[���o�b�N�֐�
void CResultAnnouncement::OnClickContinue()
{
	if (mIsEnd) return;

	mSelectIndex = 0;
	mIsEnd = true;
}

// [END]�N���b�N���̃R�[���o�b�N�֐�
void CResultAnnouncement::OnClickEnd()
{
	if (mIsEnd) return;

	mSelectIndex = 1;
	mIsEnd = true;
}

// �J��
void CResultAnnouncement::Open()
{
	// ���ɊJ���Ă�����
	if (mIsOpened) return;

	SetEnable(true);
	SetShow(true);
	mSelectIndex = 0;
	//CBGMManager::Instance()->Play(EBGMType::eMenu, false);
	CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O�𗧂Ă�
	mIsOpened = true;

	ChangeState(EState::eIdle);
}

// ����
void CResultAnnouncement::Close()
{
	// ���łɕ��Ă�����A�������Ȃ�
	if (!mIsOpened) return;

	SetEnable(false);
	SetShow(false);
	//CBGMManager::Instance()->Play(EBGMType::eGame, false);
	CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);
	// ���j���[���J�����t���O�����낷
	mResultOpened = true;
	mIsEnd = false;
	mIsOpened = false;
}

// �������Ȃ����
void CResultAnnouncement::UpdateNone()
{

}

// �ҋ@���
void CResultAnnouncement::UpdateIdle()
{
	ChangeState(EState::eOpen);
}

// ���j���[���J��
void CResultAnnouncement::UpdateOpen()
{
	switch (mStateStep)
	{
		// �X�e�b�v0�F���j���[�̓���A�j���[�V����
	case 0:
		if (mElapsedTime < OPEN_ANIM_TIME)
		{
			// �X�P�[���l����U1.0���傫�����āA1.0�֖߂�C�[�W���O�A�j���[�V����
			float scale = Easing::BackOut(mElapsedTime, OPEN_ANIM_TIME, 0.0f, 1.0f, 2.0f);
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(scale);
			}
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			for (CExpandButton* btn : mButtons)
			{
				btn->SetScale(1.0f);
			}
			mStateStep++;
			mElapsedTime = 0.0f;
		}
		break;
		// �X�e�b�v1�F���j���[�����̑҂�
	case 1:
		if (mElapsedTime < OPENED_WAIT_TIME)
		{
			mElapsedTime += Time::DeltaTime();
		}
		else
		{
			// ��莞�ԑ҂�����A�{�^�����I���ɂ��ă^�b�`�ł���悤�ɂ���
			// �i��^�b�`��h�����߂̑҂����ԁj
			for (CExpandButton* btn : mButtons)
			{
				btn->SetEnable(true);
			}
			ChangeState(EState::eSelect);
		}
		break;
	}
}

// ���j���[�I��
void CResultAnnouncement::UpdateSelect()
{
}

// �t�F�[�h�A�E�g
void CResultAnnouncement::UpdateFadeOut()
{
}

// �J�������ǂ���
bool CResultAnnouncement::IsOpened() const
{
	return mIsOpened;
}

// �ʂ̃N���X�Ń��U���g�̏�Ԃ��m�F����p
bool CResultAnnouncement::IsResultOpened() const
{
	return mResultOpened;
}

// �X�V����
void CResultAnnouncement::Update()
{
	// game��ԂɂȂ�����false�ɂ���
	if (CGameManager::GameState() == EGameState::eGame)
	{
		mResultOpened = false;
	}

	switch (mState)
	{
		// �������Ȃ����
	case EState::eNone:
		UpdateNone();
		break;
		// �ҋ@���
	case EState::eIdle:
		UpdateIdle();
		break;
		// ���j���[���J��
	case EState::eOpen:
		UpdateOpen();
		break;
		// ���j���[�I��
	case EState::eSelect:
		UpdateSelect();
		break;
		// �t�F�[�h�A�E�g
	case EState::eFadeOut:
		UpdateFadeOut();
		break;
	}

	// ���j���[���J���Ă�����
	if (IsOpened())
	{
		static const float fadeTimeRank = 0.1f;
		static const float fadeRankAlpha = 1.0f;
		if (mElapsedRankTime < fadeTimeRank)
		{
			float alphaRank = mElapsedRankTime / fadeTimeRank;
			mpRankText->SetAlpha(fadeRankAlpha * alphaRank);
			mElapsedRankTime += 0.0016f;
		}
		else
		{
			mpRankText->SetAlpha(fadeRankAlpha);
		}

		// A,B,C �̉摜
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;

			// �\������\���Ɋ|���鎞�ԁi�b�j
			static const float fadeTime = 1.5f;
			// �ő�A���t�@�l
			static const float fadeAlpha = 1.0f;

			//�t�F�[�h�w�i�̕\�����Ԃ��o�߂��Ă��Ȃ�
			if (mElapsedABCTime < fadeTime)
			{
				//�o�ߎ��Ԃɍ��킹�ăA���t�@�l��ݒ�
				float alpha = mElapsedABCTime / fadeTime;
				item->SetAlpha(fadeAlpha * alpha);
				//1�t���[���̌o�ߎ��Ԃ����Z�i���j
				mElapsedABCTime += 0.016f;
			}
			//�t�F�[�h�w�i�̕\�����Ԃ��o�߂���
			else
			{
				//�t�F�[�h�w�i�����S�ɕ\������
				item->SetAlpha(fadeAlpha);
			}
			mpRankText->Update();
		}
	}
	else
	{
		for (const auto& itemPair : mABCItems)
		{
			CImage* item = itemPair.second;

			item->SetAlpha(0.0f);
			mElapsedABCTime = 0.0f;
		}

		mpRankText->SetAlpha(0.0f);
		mElapsedRankTime = 0.0f;
	}

	for (CButton* btn : mButtons)
	{
		btn->Update();
	}
}

// �`�揈��
void CResultAnnouncement::Render()
{
	// ���j���[���J���Ă�����
	if (IsOpened())
	{
		// �ҋ@��Ԃł͉������Ȃ�(�ύX���邩��)
		if (mState == EState::eIdle)
		{
			
		}
		// �ҋ@��ԈȊO�́A���j���[�{�^����\��
		else
		{
			for (CButton* btn : mButtons)
			{
				btn->Render();
			}

			// �����N�I�`��
			mpRankText->Render();

			// �摜�p�X���X�V
			CResult* result = CResult::Instance();
			int score = result->GetTotalScore();

			// �v���C���[�̃C���X�^���X
			CPlayer* player = CPlayer::Instance();
			// �X�e�[�W1���N���A������
			bool stage1 = player->IsStage1Clear();
			// �X�e�[�W2���N���A������
			bool stage2 = player->IsStage2Clear();
			// �X�e�[�W�R���N���A������
			bool stage3 = player->IsStage3Clear();
			// ���S������
			bool stateEnd = player->IsDeath();

			// mABCItems���̉摜��`��
			for (int i = 0; i < mABCItems.size(); i++)
			{
				// �X�R�A�ɉ��������ʂ��v�Z
				// �X�e�[�W���ɕύX����
				Result resultType;
				// �X�e�[�W1�̌���
				if (stage1)
				{
					// A�����N
					if (score >= 4000)
					{
						resultType = Result::A;
					}
					// B�����N
					else if (score < 3900 && score >= 1500)
					{
						resultType = Result::B;
					}
					// C�����N
					else
					{
						resultType = Result::C;
					}
				}
				// �X�e�[�W�Q�̌���
				else if (stage2)
				{
					// A�����N
					if (score >= 2500)
					{
						resultType = Result::A;
					}
					// B�����N
					else if (score < 2500 && score >= 1500)
					{
						resultType = Result::B;
					}
					// C�����N
					else
					{
						resultType = Result::C;
					}
				}
				// �X�e�[�W�R�̌���
				else if (stage3)
				{
					// A�����N
					if (score >= 2500)
					{
						resultType = Result::A;
					}
					// B�����N
					else if (score < 2500 && score >= 1500)
					{
						resultType = Result::B;
					}
					// C�����N
					else
					{
						resultType = Result::C;
					}
				}

				// ���S���̌���
				if (stateEnd)
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
	}
}