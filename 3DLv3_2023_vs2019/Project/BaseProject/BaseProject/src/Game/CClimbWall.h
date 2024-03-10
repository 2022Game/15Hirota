#ifndef CCLIMBWALL_H
#define CCLIMBWALL_H
#include "CObjectBase.h"
#include "CColliderMesh.h"

// �o����
class CClimbWall : public CObjectBase
{
public:
	// �R���X�g���N�^
	CClimbWall();
	// �f�X�g���N�^
	~CClimbWall();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CModel* mpWallModel;	// �o���ǂ̃��f���f�[�^
	CColliderMesh* mpWallCol;	// �o���ǂ̃R���C�_�[
};
#endif