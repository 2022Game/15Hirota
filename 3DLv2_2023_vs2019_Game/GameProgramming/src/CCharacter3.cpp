#include "CCharacter3.h"
#include "CApplication.h"

void CCharacter3::Model(CModel* m)
{
	mpModel = m;
}

//�`�揈��
void CCharacter3::Render()
{
	mpModel->Render(mMatrix);
}

CCharacter3::~CCharacter3() {
	//�^�X�N���X�g����폜
	CTaskManager::Instance()->Remove(this);
}

CCharacter3::CCharacter3()
	:mpModel(nullptr)
	,mTag(EZERO)
{
	//�^�X�N���X�g�ɒǉ�
	CTaskManager::Instance()->Add(this);
}

CCharacter3::CCharacter3(int priority)
	:mpModel(nullptr)
{
	mPriority = priority;
	CTaskManager::Instance()->Add(this);
}

CCharacter3::ETag CCharacter3::Tag()
{
	return mTag;
}