#include "CCharacter3.h"
#include "CApplication.h"

CCharacter3::CCharacter3()
	:mpModel(nullptr)
	, mTag(EZERO)
{
	SetPauseType(TaskPauseType::eGame);

	//�^�X�N���X�g�ɒǉ�
//	CApplication::TaskManager()->Add(this);
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority)
	:mpModel(nullptr)
	, mTag(EZERO)
{
	SetPauseType(TaskPauseType::eGame);

	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}

CCharacter3::ETag CCharacter3::Tag()
{
	return mTag;
}

CCharacter3::~CCharacter3()
{
	//�^�X�N���X�g����폜
//	CApplication::TaskManager()->Remove(this);
	CTaskManager::Instance()->Remove(this);
}

void CCharacter3::Model(CModel* m)
{
	mpModel = m;
}

//�`�揈��
void CCharacter3::Render()
{
	mpModel->Render(mMatrix);
}

void CCharacter3::TakeDamage(int damege)
{
	//�^����ꂽ�_���[�W���AHP�����炷
	mHp -= damege;
	{
		//�L�����N�^�[���E������
		mEnabled = false;
	}
}

bool CCharacter3::IsDeath()
{
	//HP��0�ȉ��Ȃ玀��ł���
	return mHp <= 0;;
}