#ifndef COBSTACLE_H
#define COBSTACLE_H
#include "CObjectBase.h"

class CBlueMedalEvent;

// ��Q���̃x�[�X�N���X
class CObstacle : public CObjectBase
{
public:
	// �R���X�g���N�^
	CObstacle(ETag tag = ETag::eNone);
	// �f�X�g���N�^
	virtual ~CObstacle();

	// �폜���ɌĂяo��(�p����Ŏ���)
	virtual void Death();

	// �Ǘ�����Ă���C�x���g��ݒ�
	void SetEvent(CBlueMedalEvent* ev);

private:
	// �Ǘ�����Ă���C�x���g�̃|�C���^�[
	CBlueMedalEvent* mpEvent;
};
#endif