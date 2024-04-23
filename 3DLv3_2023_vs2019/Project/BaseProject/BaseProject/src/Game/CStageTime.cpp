#include "CStageTime.h"
#include "CText.h"
#include "CImage.h"
#include "CGameManager.h"

// CStageTimeクラスの実装
CStageTime::CStageTime() 
    : mTime(500)
    , mpTimer(nullptr)
{
    mpTimerText = new CText(nullptr, 40, CVector2(0, 0),
        CVector2(1250, 600), CColor(1.0f, 0.5f, 0.5f, 1.0f),
        ETaskPriority::eUI, 0);
    mpTimerText->SetTextAlign(ETextAlignH::eRight, ETextAlignV::eTop);

    mpTimer = new CImage("Timer");
    mpTimer->SetSize(100.0f, 70.0f);
    mpTimer->SetUV(0, 0, 1, 1);
    mpTimer->SetPos(1020, 0);
    mpTimer->SetColor(CColor(1.0f, 1.0f, 1.0f, 1.0f));
    mpTimer->SetShow(false);
}

CStageTime::~CStageTime()
{
    mpTimerText->Kill();
    mpTimer->Kill();
}

void CStageTime::Time(int time) {
    mTime = time;
}

void CStageTime::Update()
{
    int currentStage = CGameManager::StageNo();
    // ステージ0以外の場合は表示
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

void CStageTime::Render()
{
    char buffer[16];
    sprintf_s(buffer, "TIME:%03d", mTime);
    mpTimerText->SetText(buffer);
}