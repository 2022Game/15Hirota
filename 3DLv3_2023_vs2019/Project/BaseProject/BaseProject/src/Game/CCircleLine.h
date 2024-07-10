#ifndef CCIRCLELINE_H
#define CCIRCLELINE_H

#include "CObjectBase.h"
#include "CModel.h"

// �����I�u�W�F�N�g�̃��C��
class CCircleLine : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CCircleLine(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CCircleLine();

	// �`�揈��
	void Render() override;
private:
	CModel* mpCircle;
};
#endif