#include "CUIBase.h"
#include "CImage.h"

CUIBase::CUIBase()
	: CTask(ETaskPriority::eUI)
	, image(nullptr)
{
}

CUIBase::~CUIBase()
{
}