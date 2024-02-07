#ifndef CTREE1_H
#define CTREE1_H

#include "CModel.h"
#include "CColliderSphere.h"
#include "CRisingObject.h"

// �؃��f��1
class CTree1Obj : public CRideableObject
{
public:
	// �R���X�g���N�^
	CTree1Obj(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CTree1Obj();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ��1���f��
	CModel* mpModel;
	// ��1���f���R���C�_�[
	CColliderSphere* mpColliderSphere;
};
#endif