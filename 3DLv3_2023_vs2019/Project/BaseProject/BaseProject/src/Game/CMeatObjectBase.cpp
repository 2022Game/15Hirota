#include "CMeatObjectBase.h"

CMeatObjectBase::CMeatObjectBase()
	: CObjectBase(ETag::eMeat, ETaskPriority::eItem)
	, mNumber(0)
{

}

CMeatObjectBase::~CMeatObjectBase()
{

}

// �i���o�[��ݒ�
void CMeatObjectBase::SetMeatNumber(int number)
{
	mNumber = number;
}

// �i���o�[���擾
int CMeatObjectBase::GetMeatNumber() const
{
	return mNumber;
}
