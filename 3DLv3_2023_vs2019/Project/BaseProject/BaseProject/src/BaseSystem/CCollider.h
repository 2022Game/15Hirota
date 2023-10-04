#pragma once
#include "CTransform.h"
#include "CollisionLayer.h"
#include "ColliderType.h"
#include "CObjectBase.h"

class CCollisionManager;
class CColliderLine;
class CColliderSphere;
class CColliderTriangle;

/// <summary>
/// �R���C�_�[�̃x�[�X�N���X
/// </summary>
class CCollider : public CTransform
{
	friend CCollisionManager;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p�̃��C���[</param>
	/// <param name="type">�R���C�_�[�̎��</param>
	CCollider(CObjectBase* owner, ELayer layer, EColliderType type);
	// �f�X�g���N�^
	virtual ~CCollider();

	// �Փ˔��背�C���[���擾
	ELayer Layer() const;
	// �R���C�_�[�̎�ނ��擾
	EColliderType Type() const;
	// �R���C�_�[�̎�������擾
	CObjectBase* Owner() const;
	// �R���C�_�[�̎�����̃^�O���擾
	ETag Tag() const;

	/// <summary>
	/// �R���C�_�[���L�����ǂ�����ݒ�
	/// </summary>
	/// <param name="isEnable">�L�����ǂ���</param>
	void SetEnable(bool isEnable);
	/// <summary>
	/// �R���C�_�[���L�����ǂ������擾
	/// </summary>
	/// <returns>true�Ȃ�ΗL��</returns>
	bool IsEnable() const;

	/// <summary>
	/// �w�肵���R���C�_�[�ƏՓ˔�����s�����ǂ������擾
	/// </summary>
	/// <param name="col">�Փ˔�����s�����m�F����R���C�_�[</param>
	/// <returns>true�Ȃ�ΏՓ˔�����s��</returns>
	bool IsCollision(CCollider* col) const;

	/// <summary>
	/// �Փ˔�����s�����C���[��ݒ�
	/// �i�ݒ�O�̏�Ԃ̓��Z�b�g����j
	/// </summary>
	/// <param name="layers">�Փ˔�����s�����C���[�̃��X�g</param>
	void SetCollisionLayers(Layers layers);
	/// <summary>
	/// �w�肵�����C���[�Ƃ̏Փ˔�����s�����ǂ�����ݒ�
	/// </summary>
	/// <param name="layer">�ݒ肷�郌�C���[</param>
	/// <param name="isCollision">�Փ˔�����s�����ǂ���</param>
	void SetCollisionLayer(ELayer layer, bool isCollision);
	/// <summary>
	/// �w�肵�����C���[�ƏՓ˔�����s�����ǂ������擾
	/// </summary>
	/// <param name="layer">���肷�郌�C���[</param>
	/// <returns>true�Ȃ�ΏՓ˔�����s��</returns>
	bool IsCollisionLayer(ELayer layer) const;

	/// <summary>
	/// �Փ˔�����s���I�u�W�F�N�g�^�O��ݒ�
	/// �i�ݒ�O�̏�Ԃ̓��Z�b�g����j
	/// </summary>
	/// <param name="tags">�Փ˔�����s���I�u�W�F�N�g�^�O�̃��X�g</param>
	void SetCollisionTags(Tags tags);
	/// <summary>
	/// �w�肵���I�u�W�F�N�g�^�O�Ƃ̏Փ˔�����s�����ǂ�����ݒ�
	/// </summary>
	/// <param name="tag">�ݒ肷��I�u�W�F�N�g�^�O</param>
	/// <param name="isCollision">�Փ˔�����s�����ǂ���</param>
	void SetCollisionTag(ETag tag, bool isCollision);
	/// <summary>
	/// �w�肵���I�u�W�F�N�g�^�O�ƏՓ˔�����s�����ǂ������擾
	/// </summary>
	/// <param name="tag">���肷��I�u�W�F�N�g�^�O</param>
	/// <returns>true�Ȃ�ΏՓ˔�����s��</returns>
	bool IsCollisionTag(ETag tag) const;

	// �s����擾
	CMatrix Matrix() const;

	// �R���C�_�[�`��
	virtual void Render() = 0;

	//CollisionTriangleLine(�O�p�R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleLine(CColliderTriangle* triangle, CColliderLine* line, CVector* adjust);
	//CollisionTriangleSphere(�O�p�R���C�_, ���R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionTriangleSphere(CColliderTriangle* triangle, CColliderSphere* sphere, CVector* adjust);
	//CollisionSphere(���R���C�_, ���R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionSphere(CColliderSphere* sphere1, CColliderSphere* sphere2, CVector* adjust);
	//CollisionSphereLine(���R���C�_, �����R���C�_, �����l)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionSphereLine(CColliderSphere* sphere, CColliderLine* line, CVector* adjust);
	//CollisionLine(�����R���C�_, �����R���C�_, �����l)
	//�i�����I�ɂ̓J�v�Z���ƃJ�v�Z���̏Փ˔�����s���Ă���)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	//�����l:�Փ˂��Ȃ��ʒu�܂Ŗ߂��l
	static bool CollisionLine(CColliderLine* line1, CColliderLine* line2, CVector* adjust);

	static float CalcDistancePointToLine(const CVector& point, const CVector& lineS, const CVector& lineE, CVector* nearest = nullptr);

	//�Փ˔���
	//Collision(�R���C�_1, �R���C�_2)
	//retrun:true�i�Փ˂��Ă���jfalse(�Փ˂��Ă��Ȃ�)
	static bool Collision(CCollider* c0, CCollider* c1, CVector* adjust);

protected:
	/// <summary>
	/// �R���C�_�[�̐ݒ�
	/// </summary>
	/// <param name="owner">�R���C�_�[�̎�����</param>
	/// <param name="layer">�Փ˔���p���C���[</param>
	void Set(CObjectBase* owner, ELayer layer);

private:
	ELayer mLayer;			// �Փ˔��背�C���[
	EColliderType mType;	// �R���C�_�[�̎��
	CObjectBase* mpOwner;	// �R���C�_�[�̎�����
	bool mIsEnable;			// �L�����ǂ���
	int mCollisionLayers;	// �Փ˔�����s�����C���[�̃r�b�g�t���O
	int mCollisionTags;		// �Փ˔�����s���I�u�W�F�N�g�^�O�̃r�b�g�t���O
};
