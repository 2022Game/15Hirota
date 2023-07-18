#include "CEnemyManager.h"

//CEnemyManager�̃C���X�^���X���`
CEnemyManager* CEnemyManager::mpInstance = nullptr;

//�R���X�g���N�^
CEnemyManager::CEnemyManager()
{
}

//�f�X�g���N�^
CEnemyManager::~CEnemyManager()
{
	//CEnemyManager�ŊǗ����Ă����G�l�~�[���S�Ĕj��
	for (int i = 0; i < mEnemyList.size(); i++)
	{
		delete mEnemyList[i];
	}
	//�O�̂��߃��X�g���N���A���Ă���
	mEnemyList.clear();
	//�O�̂��߃C���X�^���X����ɂ��Ă���
	mpInstance = nullptr;
}

//CEnemyManager�̃C���X�^���X���擾
CEnemyManager* CEnemyManager::Instance()
{
	//�C���X�^���X����������Ă��Ȃ���΁A��������
	if (mpInstance == nullptr)
	{
		mpInstance = new CEnemyManager();
	}
	return mpInstance;
}

//�G�l�~�[�����X�g�ɒǉ�
void CEnemyManager::Add(CEnemy* enemy)
{
	//���X�g�̍Ō���ɒǉ�
	mEnemyList.push_back(enemy);
}

//�G�l�~�[�����X�g�����菜��
void CEnemyManager::Remove(CEnemy* enemy)
{
	//�w�肳�ꂽ�G�l�~�[�����X�g���猟��
	auto find = std::find
	(
		mEnemyList.begin(),
		mEnemyList.end(),
		enemy
	);
	//�w�肳�ꂽ�G�l�~�[�����X�g���ɑ��݂����
	if (find != mEnemyList.end())
	{
		//���X�g�����菜��
		mEnemyList.erase(find);
	}
}

//�G�l�~�[�̃��X�g���擾
const std::vector<CEnemy*>& CEnemyManager::GetEnemyList() const
{
	return mEnemyList;
}
