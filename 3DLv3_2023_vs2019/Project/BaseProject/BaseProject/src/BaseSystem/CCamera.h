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
	virtual ~CCamera();

	// ���C���J�������擾
	static CCamera* MainCamera();
	// ���݂̃J�������擾
	static CCamera* CurrentCamera();

	/// <summary>
	/// �J�����̏�Ԃ��R�s�[
	/// </summary>
	/// <param name="copy">�R�s�[���̃J����</param>
	void CopyCamera(CCamera* copy);

	/// <summary>
	/// �Ǐ]����^�[�Q�b�g��ݒ�
	/// </summary>
	/// <param name="target">�Ǐ]����^�[�Q�b�g</param>
	void SetFollowTargetTf(CTransform* target);

	/// <summary>
	/// �Ǐ]���̃I�t�Z�b�g���W��ݒ�
	/// </summary>
	/// <param name="offset"></param>
	void SetFollowTargetOffset(const CVector& offset);


	/// <summary>
	/// ��������ʒu��ݒ�i�����_�̂݁j
	/// </summary>
	/// <param name="pos">��������ʒu</param>
	void LookAt(const CVector& pos);
	/// <summary>
	/// ��������ʒu��ݒ�i�����_ + ��x�N�g���j
	/// </summary>
	/// <param name="pos">��������ʒu</param>
	/// <param name="up">��x�N�g��</param>
	void LookAt(const CVector& pos, const CVector& up);
	/// <summary>
	/// ��������ʒu��ݒ�i���_ + �����_ + ��x�N�g���j
	/// </summary>
	/// <param name="eye">�J�����̈ʒu</param>
	/// <param name="at">��������ʒu</param>
	/// <param name="up">��x�N�g��</param>
	void LookAt(const CVector& eye, const CVector& at, const CVector& up);

	/// <summary>
	/// ��ʃT�C�Y�ύX���̃R�[���o�b�N�֐�
	/// </summary>
	/// <param name="width">��ʂ̕�</param>
	/// <param name="height">��ʂ̍���</param>
	void Reshape(int width, int height);
	/// <summary>
	/// ��ʂ̕`��G���A���w��
	/// </summary>
	/// <param name="x">���̕`��J�n�ʒu</param>
	/// <param name="y">�c�̕`��J�n�ʒu</param>
	/// <param name="w">����</param>
	/// <param name="h">�c��</param>
	void Viewport(float x, float y, float w, float h);
	/// <summary>
	/// �������e�s���ݒ�
	/// </summary>
	/// <param name="fovy">��p</param>
	/// <param name="aspect">�A�X�y�N�g��</param>
	/// <param name="zNear">�`��ŒZ����</param>
	/// <param name="zFar">�`��Œ�����</param>
	void Perspective(float fovy, float aspect, float zNear, float zFar);

	/// <summary>
	/// �X�N���[�����W���烏�[���h���W�֕ϊ�
	/// </summary>
	/// <param name="screenPos">�X�N���[�����W</param>
	/// <returns>���[���h���W</returns>
	CVector ScreenToWorldPos(const CVector& screenPos);
	/// <summary>
	/// ���[���h���W����X�N���[�����W�֕ϊ�
	/// </summary>
	/// <param name="worldPos">���[���h���W</param>
	/// <returns>�X�N���[�����W</returns>
	CVector WorldToScreenPos(const CVector& worldPos);

	// �X�V
	void Update() override;

	// �J�������f
	void Apply();

	// 2D�p�̃J�����s��𔽉f
	static void Start2DCamera();
	// 3D�p�̃J�����s��֖߂�
	static void End2DCamera();

protected:
	CVector mEye;		// ���_
	CVector mAt;		// �����_
	CVector mUp;		// ��x�N�g��

private:
	static CCamera* spMainCamera;	// ���C���J����
	bool mIsMainCamera;				// ���C���J�������ǂ���
	CTransform* mFollowTargetTf;	// �Ǐ]����^�[�Q�b�g��CTransfrom
	CVector mFollowOffsetPos;		// �Ǐ]�^�[�Q�b�g�̈ʒu���王�_�܂ł̃I�t�Z�b�g�l

	CMatrix mViewMatrix;			// �r���[�s��
	CMatrix mProjectionMatrix;		// �v���W�F�N�V�����s��
	CMatrix mViewportMatrix;		// �r���[�|�[�g�s��
	float mFovy;		// �J�����̉�p
	float mZNear;		// �`��ŒZ����
	float mZFar;		// �`��Œ�����
};