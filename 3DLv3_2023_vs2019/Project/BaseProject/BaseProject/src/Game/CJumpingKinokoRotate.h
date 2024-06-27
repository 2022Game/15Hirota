#ifndef CJUMPINGKINOKOROTATE_H
#define CJUMPINGKINOKOROTATE_H

#include "CJumpingKinoko.h"

// �v���C���[�𒵂˂�����L�m�R(��]�ړ��^�C�v)
class CJumpingKinokoRotate : public CJumpingKinoko
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
	CJumpingKinokoRotate(const CVector& pos, const CVector& scale, const CVector& rot,
		float angle, float dist, float speed, bool rotateangle,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CJumpingKinokoRotate();

	void Update() override;

private:
	// ���̈ʒu
	CVector mDefaultPos;

	// �o�ߎ���
	float mElapsedTime;
	// �p�x
	float mAngle;
	// ����
	float mDistance;
	// ��]�X�s�[�h
	float mSpeed;
};
#endif