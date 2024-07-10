#ifndef CPOINTLINE_H
#define CPOINTLINE_H

#include "CObjectBase.h"
#include "CModel.h"

// ����̈ʒu�Ɉړ�����I�u�W�F�N�g�̃|�C���g���C��
class CPointLine : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	CPointLine(const CVector& pos, const CVector& scale, const CVector& rot);
	// �f�X�g���N�^
	~CPointLine();

	// �`�揈��
	void Render() override;

private:
	CModel* mpPointLine;
};
#endif