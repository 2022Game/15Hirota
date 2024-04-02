#include "CStageTime.h"
#include "CText.h"

// CStageTimeƒNƒ‰ƒX‚ÌŽÀ‘•
CStageTime::CStageTime() 
    : mTime(500)
{
    mpTimerText = new CText(nullptr, 40, CVector2(0, 0),
        CVector2(1250, 600), CColor(1.0f, 1.0f, 1.0f, 1.0f),
        ETaskPriority::eUI, 0);
    mpTimerText->SetTextAlign(ETextAlignH::eRight, ETextAlignV::eTop);
}

CStageTime::~CStageTime()
{
    mpTimerText->Kill();
}

void CStageTime::Time(int time) {
    mTime = time;
}

void CStageTime::Update()
{

}

void CStageTime::Render()
{
    char buffer[16];
    sprintf_s(buffer, "TIME:%03d", mTime);
    mpTimerText->SetText(buffer);
}