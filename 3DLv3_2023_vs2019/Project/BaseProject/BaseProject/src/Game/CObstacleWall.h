#ifndef COBSTACLEWALL_H
#define COBSTACLEWALL_H

#include "CObstacle.h"
#include "CColliderMesh.h"

class CModel;

// ��Q���̕�
class CObstacleWall : public CObstacle
{
public:
	// �R���X�g���N�^
	CObstacleWall(const CVector& pos, const CQuaternion& rot , const CVector& scale);
	// �f�X�g���N�^
	~CObstacleWall();

	/// <summary>
	/// �Փˏ���
	/// </summary>
	/// <param name="self">���g</param>
	/// <param name="other">����</param>
	/// <param name="hit">�Փˏ��</param>
	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	// �폜���ɌĂяo�����
	void Death() override;

	enum EState
	{
		eIdle,
		eDeath,
	};
	void UpdateIdle();
	void UpdateDeath();

	// �X�V
	void Update() override;
	// �`��
	void Render() override;

private:
	CModel* mpModel;
	CColliderMesh* mpColliderMesh;
	EState mState;
	int mStateStep;
	float mElapsedTimel;

	CVector mStartPos;
	CVector mTargetPos;
};
#endif