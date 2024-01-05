#include "CJumpingBase.h"
#include "CPlayer.h"

CJumpingBase::CJumpingBase(ETaskPriority prio)
	: CObjectBase(ETag::eJumpingObject, prio, 0, ETaskPauseType::eGame)
{

}

CJumpingBase::~CJumpingBase()
{
	// プレイヤーが存在すれば、
	// 自分自身が削除されることをプレイヤーに伝える
	CPlayer* player = CPlayer::Instance();
	if (player != nullptr)
	{
		player->DeleteRideableObject(this);
	}
}