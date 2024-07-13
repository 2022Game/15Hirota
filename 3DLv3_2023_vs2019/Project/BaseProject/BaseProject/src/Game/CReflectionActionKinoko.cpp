#include "CReflectionActionKinoko.h"
#include "CStageManager.h"

// �R���X�g���N�^
CReflectionActionKinoko::CReflectionActionKinoko(const CVector& pos, const CVector& scale, const CVector& rot)
	: CReflectionKinoko(pos, scale, rot, "ReflectionKinoko")
{

}

// �f�X�g���N�^
CReflectionActionKinoko::~CReflectionActionKinoko()
{
	CStageManager::RemoveTask(this);
}