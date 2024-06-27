#ifndef CJUMPINGKINOKOMOVE_H
#define CJUMPINGKINOKOMOVE_H

#include "CJumpingKinoko.h"

// �v���C���[�𒵂˂�����L�m�R(�ړ��^�C�v)
class CJumpingKinokoMove : public CJumpingKinoko
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="pos">�ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="rot">��]</param>
	/// <param name="move">�ړ�����</param>
	/// <param name="moveTime">�ړ�����</param>
	CJumpingKinokoMove(const CVector& pos, const CVector& scale, const CVector& rot,
		const CVector& move, float moveTime,
		std::string modelPath);
	// �f�X�g���N�^
	virtual ~CJumpingKinokoMove();

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