#ifndef CMETALLADDER_H
#define CMETALLADDER_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �o��������q
class CMetalLadder : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="wireName">�o�����Ԃ̃��f���f�[�^�̃��\�[�X��</param>
	/// <param name="TopName">�o�����Ԃ̒���̃��f���̃f�[�^�̃��\�[�X��</param>
	/// <param name="moveUp">����֏�������̏�����̈ړ���</param>
	/// <param name="moveForward">����֏�������̐��ʕ����̈ړ���</param>
	CMetalLadder(std::string wireName, std::string wireCol, std::string topName,
		const CVector& moveUp, const CVector& moveForward);
	// �f�X�g���N�^
	~CMetalLadder();

	// ����֏��؂������̈ړ��ʂ��擾
	void GetClimbedMoveVec(CVector* outUp, CVector* outForward) const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;
private:
	CModel* mpMetalLadderModel;		// �o�����Ԃ̃��f���f�[�^

	CColliderMesh* mpWallCol;		// �o�����Ԃ̃R���C�_�[
	CColliderMesh* mpWallTopCol;	// �o�����Ԃ̒���R���C�_�[

	CVector mClimbedMoveUp;			// ����֓o��؂������̈ړ���
	CVector mClimbMoveForward;		// ����֓o��؂������̐��ʕ����̈ړ���
};
#endif