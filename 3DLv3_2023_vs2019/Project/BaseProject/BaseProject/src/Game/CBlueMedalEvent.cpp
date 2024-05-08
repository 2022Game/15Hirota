#include "CBlueMedalEvent.h"
#include "CBlueMedal.h"
#include "CObstacle.h"
#include "CStageManager.h"

// �R���X�g���N�^
CBlueMedalEvent::CBlueMedalEvent()
	: CTask(ETaskPriority::eEvent, 0, ETaskPauseType::eGame, false, true)
	, mpObstacle(nullptr)
{

}

// �f�X�g���N�^
CBlueMedalEvent::~CBlueMedalEvent()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
	// �u���[���_�����܂����݂��Ă�����A
	// �e�u���[���_�����玩�M�̃C�x���g�ւ̃����N������
	for (CBlueMedal* medal : mBlueMedals)
	{
		medal->SetEvent(nullptr);
	}

	// ��Q�����܂����݂��Ă�����
	// ��Q�����玩�g�̃C�x���g�ւ̃����N������
	if (mpObstacle != nullptr)
	{
		mpObstacle->SetEvent(nullptr);
	}
}

// �u���[���_����ǉ�
void CBlueMedalEvent::AddBlueMedal(CBlueMedal* medal)
{
	// �u���[���_���̃��X�g�ɒǉ�
	mBlueMedals.push_back(medal);
}

// �u���[���_�����l�����ɌĂяo��
void CBlueMedalEvent::KilledBlueMedal(CBlueMedal* medal)
{
	// �u���[���_���̃��X�g���Ƀ��_�������݂��Ȃ��ꍇ�͏������Ȃ�
	if (mBlueMedals.size() == 0) return;

	// �u���[���_���̃��X�g�����菜��
	mBlueMedals.remove(medal);

	// �S�Ẵu���[���_�����l��������A
	if (mBlueMedals.size() == 0)
	{
		if (mpObstacle != nullptr)
		{
			mpObstacle->Death();
		}
	}
}

// ��Q����ݒ�
void CBlueMedalEvent::SetObstacle(CObstacle* obj)
{
	mpObstacle = obj;
}

// ��Q�����폜�����Ƃ��ɌĂяo��
void CBlueMedalEvent::KilledObstacle(CObstacle* obj)
{
	mpObstacle = nullptr;

	// ��Q���̍폜�܂ŏI���΁A
	// �Ǘ��N���X�͕s�v�Ȃ̂ō폜���Ă���
	Kill();
}

// �X�V
void CBlueMedalEvent::Update()
{

}