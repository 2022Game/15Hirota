#include "CJumpingBase.h"
#include "CPlayer.h"

CJumpingBase::CJumpingBase(ETaskPriority prio)
	: CObjectBase(ETag::eJumpingObject, prio, 0, ETaskPauseType::eGame)
{

}

CJumpingBase::~CJumpingBase()
{
	// �v���C���[�����݂���΁A
	// �������g���폜����邱�Ƃ��v���C���[�ɓ`����
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		player->DeleteRideableObject(this);
	}
}