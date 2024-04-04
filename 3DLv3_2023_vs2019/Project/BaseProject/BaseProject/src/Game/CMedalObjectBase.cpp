#include "CMedalObjectBase.h"

CMedalObjectBase::CMedalObjectBase(ETaskPriority prio)
	: CObjectBase(ETag::eMedal, prio, 0, ETaskPauseType::eGame)
{

}

CMedalObjectBase::~CMedalObjectBase()
{
}

void CMedalObjectBase::MedalStart()
{
	mMedalObjects.clear();
}

void CMedalObjectBase::MedalEnd()
{
}

void CMedalObjectBase::AddAttachHitMedalObj(CObjectBase* obj)
{
	mMedalObjects.push_back(obj);
}

bool CMedalObjectBase::IsAttachHitMedalObj(CObjectBase* obj) const
{
	// ���łɃ��X�g�ɒǉ�����Ă��邩�m�F������
	auto find = std::find
	(
		mMedalObjects.begin(),
		mMedalObjects.end(),
		obj
	);
	return find != mMedalObjects.end();
}