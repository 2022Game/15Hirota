#ifndef CCOLLISIONMANAGER_H
#define CCOLLISIONMANAGER_H

#include "CTaskManager.h"

class CCollisionManager : public CTaskManager
{
public:
	//�C���X�^���X�̎擾
	static CCollisionManager* Instance();
	//�Փˏ���
	void Collision();
private:
	//�}�l�[�W���̃C���X�^���X
	static CCollisionManager* mpInstance;
};

#endif