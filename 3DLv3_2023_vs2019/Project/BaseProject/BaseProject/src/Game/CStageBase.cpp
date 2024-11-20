#include "CStageBase.h"
#include "CEnemyManager.h"
#include "CPlayer.h"
#include "CGameManager.h"

// �R���X�g���N�^
CStageBase::CStageBase()
	: mStageNo(0)
	, mElapsedTime(0.0f)
{

}

// �f�X�g���N�^
CStageBase::~CStageBase()
{

}

// �X�e�[�W�j��
void CStageBase::Unload()
{
	// ���̃X�e�[�W�ō쐬�����^�X�N�����ׂč폜
	for (CTask* task : mCreateTasks)
	{
		task->Kill();
	}
}

// �쐬�����^�X�N�����X�g�ɒǉ�
void CStageBase::AddTask(CTask* task)
{
	mCreateTasks.push_back(task);
}

// �쐬�����^�X�N�����X�g�����菜��
void CStageBase::RemoveTask(CTask* task)
{
	mCreateTasks.remove(task);
}

// �X�e�[�W�ԍ��擾
int CStageBase::GetStageNo() const
{
	return mStageNo;
}

// �G�̔z��̐��𒲂ׂ鏈��
void CStageBase::CheckNumberEnemies()
{
	// �C���X�^���X���擾
	CEnemyManager* enemyManager = CEnemyManager::Instance();
	if (enemyManager == nullptr) return;

	// �G���X�g���Q�ƂŎ擾
	const std::vector<CXCharacter*>& enemies = enemyManager->GetEnemies();

	// �폜�Ώۂ��ꎞ�I�ɕێ�����
	std::vector<CXCharacter*> enemiesToRemove;

	if (CGameManager::GameState() == EGameState::eGame)
	{
		// �G���m�F
		for (CXCharacter* enemy : enemies)
		{
			if (enemy->HPStatus())
			{
				if (mElapsedTime <= 3.0f)
				{
					mElapsedTime += Time::DeltaTime();
				}
				else
				{
					enemiesToRemove.push_back(enemy);
					mElapsedTime = 0.0f;
				}
			}
		}
	}

	// �폜�Ώۂ��폜
	for (CXCharacter* enemy : enemiesToRemove)
	{
		enemyManager->RemoveEnemy(enemy);
	}

	// �v���C���[�̃��b�N�I���ƃJ�����ʒu���X�V
	CPlayer::Instance()->UpdateLockOnAndCameraPosition(enemies);
}

// �X�V
void CStageBase::Update()
{

}