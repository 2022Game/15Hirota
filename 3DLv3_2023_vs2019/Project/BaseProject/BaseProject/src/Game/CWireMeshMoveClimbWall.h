#ifndef CWIREMESHMOVECLIMBWALL_H
#define CWIREMESHMOVECLIMBWALL_H
#include "CObjectBase.h"
#include "CRideableObject.h"
#include "CColliderMesh.h"

// ���E�ɓ����o������
class CWireMeshMoveClimbWall : public CRideableObject
{
public:
	CWireMeshMoveClimbWall(std::string wireName, std::string topName,
		const CVector& moveUp, const CVector& moveForward,
		const CVector& pos, const CVector& move, float moveTime);
	~CWireMeshMoveClimbWall();

	// ����֏��؂������̈ړ��ʂ��擾
	void GetClimbedMoveVec(CVector* outUp, CVector* outForward) const;

	void Update() override;
	void Render() override;

private:
	CModel* mpWireMeshModel;

	CColliderMesh* mpWallCol;
	CColliderMesh* mpWallTopCol;

	CVector mClimbedMoveUp;
	CVector mClimbMoveForward;
	CVector mDefaultPos;
	CVector mMoveVec;
	float mMoveTime;
	float mElapsedTime;
};
#endif