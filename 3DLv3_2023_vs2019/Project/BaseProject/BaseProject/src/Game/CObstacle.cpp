#include "CObstacle.h"
#include "CBlueMedalEvent.h"

// �R���X�g���N�^
CObstacle::CObstacle(ETag tag)
	: CObjectBase(tag, ETaskPriority::eObstacle, 0, ETaskPauseType::eGame)
	, mpEvent(nullptr)
{

}

// �f�X�g���N�^
CObstacle::~CObstacle()
{
	// �Ǘ�����Ă���C�x���g���ݒ肳��Ă�����A
	if (mpEvent != nullptr)
	{
		// ���M���폜���ɁA�Ǘ��C�x���g�֓`����
		mpEvent->KilledObstacle(this);
	}
}

// �Ǘ�����Ă���C�x���g��ݒ�
void CObstacle::SetEvent(CBlueMedalEvent* ev)
{
	mpEvent = ev;
}

// �폜�ɌĂяo��
void CObstacle::Death()
{

}