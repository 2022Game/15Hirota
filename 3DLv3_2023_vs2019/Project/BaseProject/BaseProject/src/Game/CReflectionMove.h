#ifndef CREFLECTIONMOVE_H
#define CREFLECTIONMOVE_H

#include "CReflectionKinoko.h"

// �v���C���[�𒵂˕Ԃ�����L�m�R(�ړ��^�C�v)
class CReflectionMove : public CReflectionKinoko
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="move">��]����</param>
	/// <param name="moveTime">�ړ�����</param>
	/// <param name="modelPath">���f���p�X</param>
	CReflectionMove(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CReflectionMove();

	// �X�V����
	void Update() override;

private:
	// �ړ�����
	CVector mMoveVec;
	// ���̈ʒu
	CVector mDefaultPos;

	// �ړ����Ԍv���p
	float mMoveElapsedTime;
	// �ړ�����
	float mMoveTime;
};
#endif