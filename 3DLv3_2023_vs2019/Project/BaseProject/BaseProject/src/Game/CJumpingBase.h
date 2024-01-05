#ifndef CJUMPINGBASE_H
#define CJUMPINGBASE_H
#include "CObjectBase.h"

class CJumpingBase : public CObjectBase
{
public:
	CJumpingBase(ETaskPriority prio = ETaskPriority::eBackground);
	virtual ~CJumpingBase();
};
#endif