#include "CField.h"
#include "CTaskManager.h"

//�R���X�g���N�^
CField::CField()
{
	//�|�[�Y�̎�ނ�ݒ�
	SetPauseType(TaskPauseType::eGame);
	//�^�X�N�̗D��x��ݒ�
	mPriority = (int)TaskPriority::eBackground;
}

//�f�X�g���N�^
CField::~CField()
{
}

//�X�V����
void CField::Update()
{
	CTransform::Update();
}