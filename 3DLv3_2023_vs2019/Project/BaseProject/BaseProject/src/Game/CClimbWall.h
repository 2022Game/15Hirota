#ifndef CCLIMBWALL_H
#define CCLIMBWALL_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

// �o����
class CClimbWall : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="climbName">�o���ǂ̃��f���f�[�^�̃��\�[�X��</param>
	/// <param name="TopName">�o���ǂ̒���̃��f���̃f�[�^�̃��\�[�X��</param>
	/// <param name="moveUp">����֏�������̏�����̈ړ���</param>
	/// <param name="moveForaward">����֏�������̐��ʕ����̈ړ���</param>
	CClimbWall(std::string climbName, std::string TopName, 
		const CVector& moveUp, const CVector& moveForward);
	// �f�X�g���N�^
	~CClimbWall();

	// ����֏��؂������̈ړ��ʂ��擾
	void GetClimbedMoveVec(CVector* outUp, CVector* outForward) const;

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CModel* mpWallModel;		// �o���ǂ̃��f���f�[�^
	CColliderMesh* mpWallCol;	// �o���ǂ̃R���C�_�[
	CColliderMesh* mpWallTopCol;// �o���ǂ̒���R���C�_�[
	CVector mClimbedMoveUp;		// ����֓o����؂������̈ړ���
	CVector mClimbMoveForward;	// ����֏��؂������̐��ʕ����̈ړ���
};
#endif