#ifndef CMEAT1EVENT_H
#define CMEAT1EVENT_H

#include "CTask.h"
#include <list>

class CMeat1;
class CHighKinoko;

// ��1�l�����ɔ�������C�x���g�Ǘ��N���X
class CMeat1Event : public CTask
{
public:
	// �R���X�g���N�^
	CMeat1Event();
	// �f�X�g���N�^
	~CMeat1Event();

	// ����ǉ�
	void AddMeat1(CMeat1* meat);
	// �����l�����ɌĂяo��
	void KilledMeat1(CMeat1* meat);

	// �n�C�W�����v�L�m�R��ݒ�
	void SetHighKinoko(CHighKinoko* kinoko);
	// �n�C�W�����v�L�m�R���폜�����Ƃ��ɌĂяo��
	void KilledHighKinoko(CHighKinoko* kinoko);

	// �X�V����
	void Update() override;
private:
	// �l��������C�x���g������������̃��X�g
	std::list<CMeat1*> mMeats;
	// �n�C�W�����v�L�m�R
	CHighKinoko* mpKinoko;
};
#endif