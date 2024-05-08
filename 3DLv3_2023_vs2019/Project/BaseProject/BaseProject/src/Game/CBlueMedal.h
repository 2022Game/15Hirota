#ifndef CBLUEMEDAL_H
#define CBLUEMEDAL_H

#include "CObjectBase.h"
#include "CMedalObjectBase.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CModel.h"
class CSoud;
class CPlayer;
class CBlueMedalEvent;

// �u���[���_���A�C�e��
class CBlueMedal : public CMedalObjectBase
{
public:
	CBlueMedal(const CVector& pos, const CVector& scale);
	~CBlueMedal();

	void Collision(CCollider* self, CCollider* other, const CHitInfo& hit);

	static void SetScore(int score);
	static int GetScore();

	// �Ǘ�����Ă���C�x���g��ݒ�
	void SetEvent(CBlueMedalEvent* ev);

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

private:
	static int sScore;

	CBlueMedalEvent* mpEvent;
	CModel* mpBlueMedel;
	CColliderSphere* mpBlueMedalCol;

	// �ړ����x
	CVector mMoveSpeed;

	bool mIsGround;
};
#endif