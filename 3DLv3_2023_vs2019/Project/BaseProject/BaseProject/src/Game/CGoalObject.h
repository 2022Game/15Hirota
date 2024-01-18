#ifndef CGOALOBJECT_H
#define CGOALOBJECT_H

#include "CModel.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderMesh.h"
#include "CGoalBase.h"

// �S�[���N���X
class CGoalObject : public CGoalBase
{
public:
	CGoalObject(const CVector& pos, const CVector& scale, const CVector&rot);
	~CGoalObject();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���f���E�f�ފ֘A
	// �S�[���̓y�䃂�f��
	CModel* mpModel;
	// �S�[���̃|�X�g���f��
	CModel* mpGoalPost;
	// �|�X�g�̃R���C�_�[
	CColliderLine* mpColliderLine;
	// �Ă��؂�̃R���C�_�[
	CColliderSphere* mpColliderSphere;
	// �y��̃R���C�_�[
	CColliderMesh* mpColliderMesh;
};
#endif