#ifndef CBLUEMEDALEVENT_H
#define CBLUEMEDALEVENT_H

#include "CTask.h"
#include <list>

class CBlueMedal;
class CObstacle;

// ���_���l�����ɔ�������C�x���g�Ǘ��N���X
class CBlueMedalEvent : public CTask
{
public:
	// �R���X�g���N�^
	CBlueMedalEvent();
	// �f�X�g���N�^
	~CBlueMedalEvent();

	// �u���[���_����ǉ�
	void AddBlueMedal(CBlueMedal* medal);
	// �u���[���_�����l�����ɌĂяo��
	void KilledBlueMedal(CBlueMedal* medal);

	// ��Q����ݒ�
	void SetObstacle(CObstacle* obj);
	// ��Q�����폜�����Ƃ��ɌĂяo��
	void KilledObstacle(CObstacle* obj);

	// �X�V
	void Update() override;

private:
	// �S�Ċl��������C�x���g����������u���[���_���̃��X�g
	std::list<CBlueMedal*> mBlueMedals;
	// ��Q��
	CObstacle* mpObstacle;
};
#endif