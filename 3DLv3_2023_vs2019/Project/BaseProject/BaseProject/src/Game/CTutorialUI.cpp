#include "CTutorialUI.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CTaskManager.h"
#include "CInput.h"
#include "Maths.h"

#define ALPHA_CHANGE_TIME 1.0f

CTutorialUI::CTutorialUI()
    : CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
    , mIsTransitioning(false)
    , mElapsedTime(0.0f)
    , mIsChangeImage(false)
    , mpCurrentImage(nullptr)
{
    // �`���[�g���A���摜��ǂݍ���
    CImage* image1 = new CImage
    (
        "UI/Tutorial/Tutorial1.png",
        ETaskPriority::eUI, 0, ETaskPauseType::eGame,
        false, false
    );
    image1->SetSize(900.0f, 700.0f);
    image1->SetCenter(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
    image1->SetPos(CVector2(WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.52f));
    image1->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    mTutorialItems.push_back(image1);

    CImage* image2 = new CImage
    (
        "UI/Tutorial/Tutorial2.png",
        ETaskPriority::eUI, 0, ETaskPauseType::eGame,
        false, false
    );
    image2->SetSize(900.0f, 700.0f);
    image2->SetCenter(CVector2(WINDOW_WIDTH, WINDOW_HEIGHT) * 0.5f);
    image2->SetPos(CVector2(WINDOW_WIDTH * 0.65f, WINDOW_HEIGHT * 0.52f));
    image2->SetColor(1.0f, 1.0f, 1.0f, 0.0f);
    mTutorialItems.push_back(image2);

    // �ŏ��̉摜���Z�b�g
    if (!mTutorialItems.empty())
    {
        mpCurrentImage = mTutorialItems[0];
    }
}

// �f�X�g���N�^
CTutorialUI::~CTutorialUI()
{
    CStageManager::RemoveTask(this);
    // �폜�����Ƃ��Ƀ��j���[���J�����܂܂ł���΁A
    // ���j���[�����
    if (mIsOpened)
    {
        Close();
    }

    for (auto image : mTutorialItems)
    {
        SAFE_DELETE(image);
    }
    mTutorialItems.clear();
}

// �J��
void CTutorialUI::Open()
{
    // ���ɊJ���Ă�����A�������Ȃ�
    if (mIsOpened) return;

    mpCurrentImage = mTutorialItems[0];

    CTaskManager::Instance()->Pause(PAUSE_MENU_OPEN);

    SetEnable(true);
    SetShow(true);
    // ���j���[�J�����t���O���グ��
    mIsOpened = true;
}

// ����
void CTutorialUI::Close()
{
    // ���łɕ��Ă�����A�������Ȃ�
    if (!mIsOpened) return;

    CTaskManager::Instance()->UnPause(PAUSE_MENU_OPEN);

    SetEnable(false);
    SetShow(false);
    // ���j���[���J�����t���O������
    mIsOpened = false;
}

// �J���Ă��邩�ǂ���
bool CTutorialUI::IsOpened() const
{
    return mIsOpened;
}

// �X�V����
void CTutorialUI::Update()
{
    if (!mIsOpened) return;

    auto it = std::find(mTutorialItems.begin(), mTutorialItems.end(), mpCurrentImage);

    if (mIsTransitioning)
    {
        if (mElapsedTime < ALPHA_CHANGE_TIME)
        {
            mpCurrentImage->SetAlpha(1.0f);
            // �T�C���J�[�u�œ_��
            float per = sinf(M_PI * mElapsedTime / ALPHA_CHANGE_TIME);
            mpCurrentImage->SetAlpha(1.0f - per);
            mElapsedTime += Time::DeltaTime();
            if (mpCurrentImage->GetAlpha() <= 0.0f)
            {
                if (mIsChangeImage)
                {
                    mpCurrentImage->SetAlpha(0.0f);
                    mpCurrentImage = *(it + 1); // ���̉摜�ɐ؂�ւ�
                }
                else if (!mIsChangeImage)
                {
                    mpCurrentImage->SetAlpha(0.0f);
                    mpCurrentImage = *(it - 1); // �O�̉摜�ɐ؂�ւ�
                }
            }
        }
        else
        {
            mpCurrentImage->SetAlpha(1.0f);
            mIsTransitioning = false;
        }
    }
    else if (mpCurrentImage->GetAlpha() >= 1.0f)
    {
        if (CInput::PushKey(VK_RIGHT) && it != mTutorialItems.end() && (it + 1) != mTutorialItems.end())
        {
            mIsChangeImage = true;
            mIsTransitioning = true;
            mElapsedTime = 0.0f;
        }
        else if (CInput::PushKey(VK_LEFT) && it != mTutorialItems.begin())
        {
            mIsChangeImage = false;
            mIsTransitioning = true;
            mElapsedTime = 0.0f;
        }
        else if (CInput::PushKey(VK_RETURN))
        {
            if (mpCurrentImage == mTutorialItems.back())
            {
                Close(); // �`���[�g���A���I��
            }
        }
    }

    mpCurrentImage->Update();
    for (CImage* tutorial : mTutorialItems)
    {
        tutorial->Update();
    }
}

// �X�V����
void CTutorialUI::Render()
{
    if (mIsOpened)
    {
        mpCurrentImage->SetShow(true);
        mpCurrentImage->SetEnable(true);
        mpCurrentImage->Render();
    }
}