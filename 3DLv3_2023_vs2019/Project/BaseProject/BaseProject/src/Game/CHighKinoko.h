#ifndef CHIGHKINOKO_H
#define CHIGHKINOKO_H

#include "CObjectBase.h"

class CMeat1Event;

// �n�C�W�����v�L�m�R�̃x�[�X�N���X
class CHighKinoko : public CObjectBase
{
public:
	// �R���X�g���N�^
	CHighKinoko(ETag tag = ETag::eNone);
	// �f�X�g���N�^
	virtual ~CHighKinoko();

	// �����擾���ɌĂяo��
	virtual void Alpha();

	// �Ǘ����ꂽ����C�x���g��ݒ�
	void SetEvent(CMeat1Event* ev);

private:
	// �Ǘ�����Ă���C�x���g�̃|�C���^�[
	CMeat1Event* mpEvent;
};
#endif