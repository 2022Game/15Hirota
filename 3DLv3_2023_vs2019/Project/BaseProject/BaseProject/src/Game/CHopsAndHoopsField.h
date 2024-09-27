#ifndef CHOPSANDHOOPSFIELD_H
#define CHOPSANDHOOPSFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �u�L�m�R�W�����v�X�e�[�W�v
class CHopsAndHoopsField : public CObjectBase
{
public:
	// �R���X�g���N�^
	CHopsAndHoopsField();
	// �f�X�g���N�^
	~CHopsAndHoopsField();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �X�e�[�W�̃��f��
	CModel* mpStageModel;
	// �X�e�[�W�̃R���C�_�[
	CColliderMesh* mpFloorCol;
};
#endif