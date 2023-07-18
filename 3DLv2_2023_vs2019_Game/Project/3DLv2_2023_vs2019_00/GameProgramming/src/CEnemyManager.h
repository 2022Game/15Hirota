#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H
#include "CEnemy.h"

//�G�l�~�[�̊Ǘ��N���X
class CEnemyManager
{
public:
	//CEnemyManager�̃C���X�^���X���擾
	static CEnemyManager* Instance();
	//�R���X�g���N�^
	CEnemyManager();
	//�f�X�g���N�^
	~CEnemyManager();

	//�G�l�~�[�����X�g�ɒǉ�
	void Add(CEnemy* enemy);
	//�G�l�~�[�����X�g�����菜��
	void Remove(CEnemy* enemy);

	//�G�l�~�[�̃��X�g���擾
	const std::vector<CEnemy*>& GetEnemyList() const;

private:
	//CEnemyManager�̃C���X�^���X
	static CEnemyManager* mpInstance;
	//�G�l�~�[�̃��X�g
	std::vector<CEnemy*> mEnemyList;
};

#endif