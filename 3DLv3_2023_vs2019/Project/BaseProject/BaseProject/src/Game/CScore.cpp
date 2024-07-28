#include "CScore.h"
#include "CText.h"
#include "CGameManager.h"
#include "CTaskManager.h"
#include "CVanguard.h"
#include "CBlueMedal.h"
#include "CMeat1.h"
#include "CMeat2.h"
#include "CMeat3.h"
#include "CStageManager.h"

// �X�R�A�̃C���X�^���X
CScore* CScore::spInstance = nullptr;

CScore* CScore::Instance()
{
    if (spInstance == nullptr)
    {
        spInstance = new CScore();
    }
    return spInstance;
}

// �C���X�^���X
CScore::CScore()
	: mScore(0)
	, mIsStage1(false)
	, mIsStage2(false)
	, mIsStage3(false)
    , mIsStage4(false)
{
	// �C���X�^���X�̐ݒ�
	spInstance = this;

    // �^�C�g�����S�̃t�H���g�f�[�^�𐶐�
    mpLogoFont = new CFont("res\\Font\\toroman.ttf");
    mpLogoFont->SetFontSize(30);
    //mpLogoFont->SetAlignment(FTGL::TextAlignment::ALIGN_CENTER);
    mpLogoFont->SetLineLength(WINDOW_WIDTH);

    // �X�R�A�̃e�L�X�g
    mpScoreText = new CText
    (
        mpLogoFont, 30,
        CVector2(1050, 100),
        CVector2(400, 300),
        CColor(1.0f, 1.0f, 1.0f, 1.0f),
        ETaskPriority::eUI,
        0
    );
    mpScoreText->SetEnableOutline(true);
    mpScoreText->SetOutlineColor(CColor(0.0f, 0.0f, 0.0f));
}

// �f�X�g���N�^
CScore::~CScore()
{
    CStageManager::RemoveTask(this);
	spInstance = nullptr;
    SAFE_DELETE(mpLogoFont);
    SAFE_DELETE(mpScoreText);
}

// �X�R�A�̐ݒ�
void CScore::Score(int score)
{
    mScore = score;
}

// �X�V����
void CScore::Update()
{
    // ���݂̃X�e�[�W�ԍ�
    int currentStage = CGameManager::StageNo();
    // �|�[�Y�����Ă��邩�ǂ���
    bool pose = CTaskManager::Instance()->IsPaused();

    // ���݂̃X�e�[�W�ԍ���0��������
    if (currentStage == 0)
    {
        // �e�X�e�[�W�t���O��false�ɂ���
        mIsStage1 = false;
        mIsStage2 = false;
        mIsStage3 = false;
        mIsStage4 = false;
        // �X�R�A�e�L�X�g���\���ɐݒ�
        mpScoreText->SetShow(false);
        // �X�e�[�W0�̏ꍇ�͑��̏������X�L�b�v
        return;
    }
    
    // �|�[�Y����Ȃ�������
    if (!pose)
    {
        // �X�e�[�W1
        if (currentStage == 1 && !mIsStage1)
        {
            mIsStage1 = true;
            mIsStage2 = false;
            mIsStage3 = false;
            mIsStage4 = false;
            mpScoreText->SetShow(true);
        }
        // �X�e�[�W2
        else if (currentStage == 2 && !mIsStage2)
        {
            mIsStage1 = false;
            mIsStage2 = true;
            mIsStage3 = false;
            mIsStage4 = false;
            mpScoreText->SetShow(true);
        }
        // �X�e�[�W3
        else if (currentStage == 3 && !mIsStage3)
        {
            mIsStage1 = false;
            mIsStage2 = false;
            mIsStage3 = true;
            mIsStage4 = false;
            mpScoreText->SetShow(true);
        }
        // �X�e�[�W3
        else if (currentStage == 4 && !mIsStage4)
        {
            mIsStage1 = false;
            mIsStage2 = false;
            mIsStage3 = false;
            mIsStage4 = true;
            mpScoreText->SetShow(true);
        }
        
        // �X�e�[�W1,2,3�ɓ����Ă��鎞�̂݃X�R�A�̌v�Z���s��
        if (mIsStage1 || 
            mIsStage2 || 
            mIsStage3 ||
            mIsStage4)
        {
            // ���݂̃X�R�A�̌v�Z
            // ���@���K�[�h�X�R�A + �u���[���_���X�R�A
            mScore = CVanguard::GetScore() 
                + CBlueMedal::GetScore()
                + CMeat1::GetScore()
                + CMeat2::GetScore()
                + CMeat3::GetScore();
        }
    }

    // �X�R�A�̐ݒ�
    Score(mScore);

    //printf("mScore:%d\n", mScore);
}

// �`�揈��
void CScore::Render()
{
    // �X�R�A��0�ł��邱�Ƃ��m�F
    // 0��������0000�ƕ\��
    if (mScore == 0)
    {
        mpScoreText->SetText("SCORE  0000");
    }
    // 0�ȊO��������X�R�A��`��
    else
    {
        char buffer[16];
        sprintf_s(buffer, "SCORE  %04d", mScore);
        mpScoreText->SetText(buffer);
    }
}