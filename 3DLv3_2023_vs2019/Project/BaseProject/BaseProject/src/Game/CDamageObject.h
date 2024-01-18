#pragma once
#include "CRideableObject.h"
#include "CModel.h"
#include "CColliderMesh.h"

// �_���[�W��^����I�u�W�F�N���X
class CDamageObject : public CRideableObject
{
public:
	CDamageObject(const CVector& pos, const CVector& scale, const CVector& move, float moveTime);
	~CDamageObject();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:

	// ���f���E�f�ފ֘A
	// �_���[�W��^����I�u�W�F���f��
	CModel* mpModel;
	// �_���[�W��^����I�u�W�F�R���C�_�[
	CColliderMesh* mpColliderMesh;


	// �x�N�g���֘A
	// �����ʒu
	CVector mDefaultPos;
	// �ړ���
	CVector mMoveVec;

	
	// �ϐ��֘A
	// ���Ԍv��
	float mMoveTime;
	// �I�����Ԍv��
	float mElapsedTime;
};