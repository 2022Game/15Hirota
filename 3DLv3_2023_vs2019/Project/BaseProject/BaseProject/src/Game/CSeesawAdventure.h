#ifndef CSEESAWADVENTURE_H
#define CSEESAWADVENTURE_H

#include "CObjectBase.h"
#include "CColliderMesh.h"
#include "CColliderSphere.h"

// �u�V�[�\�[�A�h�x���`���[�v
class CSeesawAdventure : public CObjectBase
{
public:
	// �R���X�g���N�^
	CSeesawAdventure();
	// �f�X�g���N�^
	~CSeesawAdventure();

	CColliderMesh* GetWallCol() const;

	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;

private:
	// �X�e�[�W�̃��f��
	CModel* mpStageModel;

	// �X�e�[�W�̃R���C�_�[
	CColliderMesh* mpFloorCol;
	// �X�e�[�W�̕ǃR���C�_�[
	CColliderMesh* mpWallCol;
};
#endif