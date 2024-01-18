#ifndef CSTONE1_H
#define CSTONE1_H

#include "CModel.h"
#include "CColliderSphere.h"
#include "CRideableObject.h"

// ��1�N���X
class CStone1 : public CRideableObject
{
public:
	CStone1(const CVector& pos, const CVector& scale, const CVector& rot);
	~CStone1();

	// �X�V����
	void Update();
	// �X�V����
	void Render();

private:
	// ��1���f��
	CModel* mpModel;
	// ��1���f���̃R���C�_�[
	CColliderSphere* mpColliderSphere;
};
#endif