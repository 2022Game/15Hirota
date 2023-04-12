#include "CCollisionManager.h"

//�}�l�[�W���̃C���X�^���X
CCollisionManager* CCollisionManager::mpInstance = nullptr;
//�C���X�^�z�擾
CCollisionManager* CCollisionManager::Instance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new CCollisionManager();
	}
	return mpInstance;
}

//�Փˏ���
void CCollisionManager::Collision() {
	//���݈ʒu�ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�Ō�܂ŗ�����I������
	while (task->mpNext) {
		//���݈ʒu�̎������߂�
		CCollider* next = (CCollider*)task->mpNext;
		//����0�ɂȂ�����I��
		while (next->mpNext) {
			//�e�̏Փˏ������Ăяo��
			//�����̏Փˏ���
			if (task->mpParent)
				task->mpParent->Collision(task, next);
			//����̏Փˏ���
			if (next->mpParent)
				next->mpParent->Collision(next, task);
			//�������߂�
			next = (CCollider*)next->mpNext;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}

void CCollisionManager::Collision(CCollider* c, int range){
	//���݈ʒu��擪�ɂ���
	CCollider* task = (CCollider*)mHead.mpNext;
	//�͈͂܂œǂݔ�΂�
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority + range)
		{
			break;
		}
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
	//�Ō�܂ŗ�����I������
	while (task->mpNext) {
		if (task->mPriority <= c->mPriority - range)
		{
			break;
		}
		//�e�̏Փˏ������Ăяo��
		//�����̏Փˏ���
		if (c->mpParent && c != task)
			c->mpParent->Collision(c, task);
		//���݈ʒu�����ɂ���
		task = (CCollider*)task->mpNext;
	}
}