#ifndef CFINALSTAGEFIELD_H
#define CFINALSTAGEFIELD_H

#include "CObjectBase.h"
#include "CColliderMesh.h"

// �u�ŏI�X�e�[�W�v
class CFinalStageField : public CObjectBase
{
public:
	// �R���X�g���N�^
	CFinalStageField();
	// �f�X�g���N�^
	~CFinalStageField();

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �X�e�[�W�̃��f��
	CModel* mpStageModel;
	// ���C�����f��
	CModel* mpLineModel;

	// �X�e�[�W�̏��R���C�_�[
	CColliderMesh* mpStageFloorCol;
	// �X�e�[�W�̕ǃR���C�_�[
	CColliderMesh* mpStageWallCol;
};
#endif