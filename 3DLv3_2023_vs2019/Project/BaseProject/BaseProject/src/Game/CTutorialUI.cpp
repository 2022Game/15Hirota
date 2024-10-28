#include "CTutorialUI.h"
#include "CImage.h"
#include "CStageManager.h"
#include "CTaskManager.h"
#include "CInput.h"

CTutorialUI::CTutorialUI()
    : CTask(ETaskPriority::eUI, 0, ETaskPauseType::eMenu)
	, mIsOpened(false)
    , mCurrentImage(nullptr)
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
    image2->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    mTutorialItems.push_back(image2);

    // �ŏ��̉摜���Z�b�g
    if (!mTutorialItems.empty())
        mCurrentImage = mTutorialItems[0];
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
        delete image;
    mTutorialItems.clear();
}

// �J��
void CTutorialUI::Open()
{
    // ���ɊJ���Ă�����A�������Ȃ�
    if (mIsOpened) return;

    mCurrentImage = mTutorialItems[0];

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

    // �L�[���͏����i���z�L�[�R�[�h�ɉ����ēK�X�ύX�j
    if (CInput::PushKey(VK_RIGHT))
    {
        auto it = std::find(mTutorialItems.begin(), mTutorialItems.end(), mCurrentImage);
        if (it != mTutorialItems.end() && (it + 1) != mTutorialItems.end())
        {
            mCurrentImage = *(it + 1); // ���̉摜�ɐ؂�ւ�
        }
    }
    else if (CInput::PushKey(VK_LEFT))
    {
        auto it = std::find(mTutorialItems.begin(), mTutorialItems.end(), mCurrentImage);
        if (it != mTutorialItems.begin())
        {
            mCurrentImage = *(it - 1); // �O�̉摜�ɐ؂�ւ�
        }
    }
    else if (CInput::PushKey(VK_RETURN))
    {
        if (mCurrentImage == mTutorialItems.back())
        {
            Close(); // �`���[�g���A���I��
        }
    }
    mCurrentImage->Update();
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
        mCurrentImage->SetShow(true);
        mCurrentImage->SetEnable(true);
        mCurrentImage->Render();
    }
}