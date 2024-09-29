#ifndef CCIRCLENBFL3_H
#define CCIRCLENBFL3_H

#include "CNumberFloor3.h"

// �~��]����񐔂ŗ����鏰(3��)�x�[�X
class CCircleNbFl3 : public CNumberFloor3
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="angle">�p�x</param>
	/// <param name="dist">����</param>
	/// <param name="speed">��]�̑���</param>
	/// <param name="rotateangle">��]�����̐ݒ�</param>
	/// <param name="modelPath">���f���p�X</param>
	CCircleNbFl3(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CCircleNbFl3();

	void Update() override;

private:
	// ���̈ʒu
	CVector mDefaultPos;

	// �o�ߎ���
	float mElapsedRotateTime;
	// �p�x
	float mAngle;
	// ����
	float mDistance;
	// ��]�X�s�[�h
	float mSpeed;
};
#endif