#ifndef CWIREMESHCLIMBWALL_H
#define CWIREMESHCLIMBWALL_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

// �o������
class CWireMeshClimbWall : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="wireName">�o�����Ԃ̃��f���f�[�^�̃��\�[�X��</param>
	/// <param name="TopName">�o�����Ԃ̒���̃��f���̃f�[�^�̃��\�[�X��</param>
	/// <param name="moveUp">����֏�������̏�����̈ړ���</param>
	/// <param name="moveForward">����֏�������̐��ʕ����̈ړ���</param>
	CWireMeshClimbWall(std::string wireName, std::string topName,
		const CVector& moveUp, const CVector& moveForward);
	// �f�X�g���N�^
	~CWireMeshClimbWall();

	// ����֏��؂������̈ړ��ʂ��擾
	void GetClimbedMoveVec(CVector* outUp, CVector* outForward) const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CModel* mpWireMeshModel;		// �o�����Ԃ̃��f���f�[�^

	CColliderMesh* mpWallCol;		// �o�����Ԃ̃R���C�_�[
	CColliderMesh* mpWallTopCol;	// �o�����Ԃ̒���R���C�_�[

	CVector mClimbedMoveUp;			// ����֓o��؂������̈ړ���
	CVector mClimbMoveForward;		// ����֓o��؂������̐��ʕ����̈ړ���
};
#endif