#ifndef CPROPELLER_H
#define CPROPELLER_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

class CModel;

class CPropeller : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rotateSpeedZ">��]</param>
	CPropeller(const CVector& pos, const CVector& scale,
		float rotateSpeedZ);
	// �f�X�g���N�^
	~CPropeller();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	// ���f��
	CModel* mpRotationgModel;
	// ���b�V��
	CColliderMesh* mpRotationgCol;

	// ��]�X�s�[�h
	float mRotateSpeedZ;
};
#endif