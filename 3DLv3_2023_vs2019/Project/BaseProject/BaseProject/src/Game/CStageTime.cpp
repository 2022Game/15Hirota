#include "CStageTime.h"
#include "CText.h"
#include "CImage.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CPlayer.h"

#define STAGE_1 300
#define STAGE_2 10
#define STAGE_3 400

#define STAR_STAGE_TIME 1.0f

// �X�e�[�W�^�C�}�[�̃C���X�^���X
CStageTime* CStageTime::spInstance = nullptr;

CStageTime* CStageTime::Instance()
{
    if (spInstance == nullptr)
    {
        spInstance = new CStageTime();
    }
    return spInstance;
}

// �R���X�g���N�^
CStageTime::CStageTime() 
    : mTime(0)
    , mpTimer(nullptr)
	, mIsStage1(false)
	, mIsStage2(false)
	, mIsStage3(false)
{
    // �C���X�^���X�̐ݒ�
    spInstance = this;
    mpTimerText = new CText(nullptr, 40, CVector2(0, 0),
        CVector2(1250, 600), CColor(1.0f, 0.5f, 0.5f, 1.0f),
        ETaskPriority::eUI, 0);
    mpTimerText->SetTextAlign(ETextAlignH::eRight, ETextAlignV::eTop);

    // ���v�̉摜��ݒ�
    mpTimer = new CImage("Timer");
    mpTimer->SetSize(100.0f, 70.0f);
    mpTimer->SetUV(0, 0, 1, 1);
    mpTimer->SetPos(1020, 0);
    mpTimer->SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
    mpTimer->SetShow(false);
}

// �f�X�g���N�^
CStageTime::~CStageTime()
{
    spInstance = nullptr;
    SAFE_DELETE(mpTimerText);
    SAFE_DELETE(mpTimer);
}

// ���Ԃ��擾
void CStageTime::Time(int time) {
    mTime = time;
}

// �X�V����
void CStageTime::Update()
{
    int currentStage = CGameManager::StageNo();
    bool paused = CTaskManager::Instance()->IsPaused();

    CPlayer* palyer = CPlayer::Instance();

    // �X�e�[�W��0�̏ꍇ�̓^�C�}�[�����Z�b�g
    if (currentStage == 0)
    {
        mIsStage1 = false;
        mIsStage2 = false;
        mIsStage3 = false;
        //mTime = 0;
    }
    else if (!paused) // �|�[�Y���łȂ���΃^�C�}�[�X�V
    {
        // �X�e�[�W1, 2, 3�̏ꍇ�̏���
        if (currentStage == 1 && !mIsStage1)
        {
            mTime = STAGE_1;
            mIsStage1 = true;
            mIsStage2 = false;
            mIsStage3 = false;
        }
        else if (currentStage == 2 && !mIsStage2)
        {
            mTime = STAGE_2;
            mIsStage1 = false;
            mIsStage2 = true;
            mIsStage3 = false;
        }
        else if (currentStage == 3 && !mIsStage3)
        {
            mTime = STAGE_3;
            mIsStage1 = false;
            mIsStage2 = false;
            mIsStage3 = true;
        }

        // �Q�[�����Ԃ̍X�V
        static float startTime = STAR_STAGE_TIME;
        if(CGameManager::GameState() == EGameState::eGame)
        startTime -= Time::DeltaTime();
        if (startTime <= 0.0f)
        {
            if (mTime > 0)
            {
                mTime--; // �^�C�}�[�����炷
                startTime = STAR_STAGE_TIME; // �^�C�}�[�����Z�b�g
            }

            // �^�C�}�[��0�ɂȂ�����v���C���[�����S������
            if (mTime == 0)
            {
                palyer->UpdateDeath();
            }
        }
    }

    // �X�e�[�W1,2,3�̂ݕ\��
    if (currentStage == 1 || currentStage == 2 || currentStage == 3)
    {
        mpTimer->SetShow(true);
        mpTimerText->SetShow(true);
    }
    else
    {
        mpTimer->SetShow(false);
        mpTimerText->SetShow(false);
    }
}

// �`�揈��
void CStageTime::Render()
{
    char buffer[16];
    sprintf_s(buffer, "TIME:%03d", mTime);
    mpTimerText->SetText(buffer);
}