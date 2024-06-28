#include "CHighKinoko.h"
#include "CMeat1Event.h"

// �R���X�g���N�^
CHighKinoko::CHighKinoko(ETag tag)
	: CObjectBase(tag, ETaskPriority::eKinoko, 0, ETaskPauseType::eGame)
	, mpEvent(nullptr)
{

}

// �f�X�g���N�^
CHighKinoko::~CHighKinoko()
{
	// �Ǘ�����Ă���C�x���g���ݒ肳��Ă�����A
	if (mpEvent != nullptr)
	{
		// ���g���폜���ɁA�Ǘ��C�x���g�֓`����
		mpEvent->KilledHighKinoko(this);
	}
}

// �����擾���ɌĂяo��
void CHighKinoko::Alpha()
{
}

// �Ǘ�����Ă���C�x���g��ݒ�
void CHighKinoko::SetEvent(CMeat1Event* ev)
{
	mpEvent = ev;
}

// �폜���ɌĂяo��
// �K�v��������