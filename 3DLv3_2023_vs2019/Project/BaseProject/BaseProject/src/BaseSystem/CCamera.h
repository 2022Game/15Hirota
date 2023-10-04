#pragma once
#include "CObjectBase.h"

// �J����
class CCamera : public CObjectBase
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="eye">�J�����̎��_</param>
	/// <param name="center">�J�����̒����_</param>
	/// <param name="isMainCamera">���C���J�������ǂ���</param>
	CCamera(const CVector& eye, const CVector& center, bool isMainCamera = true);
	// �f�X�g���N�^
	~CCamera();

	// ���C���J�������擾
	static CCamera* MainCamera();

	/// <summary>
	/// �J�����̐ݒ�
	/// </summary>
	/// <param name="eye">���_</param>
	/// <param name="center">�����_</param>
	void Set(const CVector& eye, const CVector& center);

	/// <summary>
	/// �Ǐ]����^�[�Q�b�g��ݒ�
	/// </summary>
	/// <param name="target">�Ǐ]����^�[�Q�b�g</param>
	void SetFollowTargetTf(CTransform* target);

	/// <summary>
	/// ��������ʒu��ݒ�
	/// </summary>
	/// <param name="pos"></param>
	void LookAt(const CVector& pos);

	// �X�V
	void Update();

	// �J�������f
	void Apply();

	// 2D�p�̃J�����s��𔽉f
	static void Start2DCamera();
	// 3D�p�̃J�����s��֖߂�
	static void End2DCamera();

private:
	static CCamera* spMainCamera;	// ���C���J����
	bool mIsMainCamera;				// ���C���J�������ǂ���
	CTransform* mFollowTargetTf;	// �Ǐ]����^�[�Q�b�g��CTransfrom
	CVector mFollowOffsetPos;		// �Ǐ]�^�[�Q�b�g�̈ʒu���王�_�܂ł̃I�t�Z�b�g�l
};