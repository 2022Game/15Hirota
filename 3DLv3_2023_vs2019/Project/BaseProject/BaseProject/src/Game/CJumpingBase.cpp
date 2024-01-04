#include "CJumpingBase.h"

CJumpingBase::CJumpingBase()
	: CObjectBase(ETag::eJumpingObject, ETaskPriority::eBackground, 0, ETaskPauseType::eGame)
{

}

CJumpingBase::~CJumpingBase()
{

}