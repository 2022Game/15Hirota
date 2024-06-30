#include "CMeat1Event.h"
#include "CMeat1.h"
#include "CHighKinoko.h"
#include "CStageManager.h"
#include "CMeat1.h"

// �R���X�g���N�^
CMeat1Event::CMeat1Event()
	: CTask(ETaskPriority::eEvent, 0, ETaskPauseType::eGame, false, true)
	, mpKinoko(nullptr)
{

}

// �f�X�g���N�^
CMeat1Event::~CMeat1Event()
{
	// �쐬�����^�X�N����菜��
	CStageManager::RemoveTask(this);
	// ��1���܂����݂��Ă�����A
	// �����玩�g�̃C�x���g�ւ̃����N������
	for (CMeat1* meat1 : mMeats)
	{
		meat1->SetEvent(nullptr);
	}
	
	// �n�C�W�����v�L�m�R���܂����݂��Ă�����
	// �n�C�W�����v�L�m�R���玩�M�̃C�x���g�ւ̃����N������
	if (mpKinoko != nullptr)
	{
		mpKinoko->SetEvent(nullptr);
	}
}

// ����ǉ�
void CMeat1Event::AddMeat1(CMeat1* meat)
{
	// ���̃��X�g�ɒǉ�
	mMeats.push_back(meat);
}

// �����l�����ɌĂяo��
void CMeat1Event::KilledMeat1(CMeat1* meat)
{
	// ���̃��X�g���ɓ������݂��Ȃ��ꍇ�͏������Ȃ�
	if (mMeats.size() == 0) return;

	// ���̃��X�g�����菜��
	// kill���Ȃ��̂ŃR�����g�A�E�g
	//mMeats.remove(meat);

	CMeat1* meat1 = CMeat1::Instance();
	bool IsMeat = meat1->IsMeat1();

	// �����l��������
	//mMeats.size() == 0
	if (IsMeat)
	{
		if (mpKinoko != nullptr)
		{
			mpKinoko->Alpha();
		}
	}
}

// �n�C�W�����v�L�m�R��ݒ�
void CMeat1Event::SetHighKinoko(CHighKinoko* kinoko)
{
	mpKinoko = kinoko;
}

// �n�C�W�����v�L�m�R���폜�����Ƃ��ɌĂяo��
void CMeat1Event::KilledHighKinoko(CHighKinoko* kinoko)
{
	mpKinoko = nullptr;

	// �n�C�W�����v�L�m�R�̍폜�܂ŏI���΁A
	// �Ǘ��N���X�͕s�v�Ȃ̂ō폜����
	Kill();
}

// �X�V����
void CMeat1Event::Update()
{

}