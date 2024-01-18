#ifndef CGUN_H
#define CGUN_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderLine.h"
#include "CModel.h"

// �e�N���X
class CGun :public CWeapon
{
public:
	CGun();
	~CGun();

	// �X�V����
	void Update();
	// �`�揈��
	void Render();

	// ����̍s����擾
	CMatrix Matrix() const override;

private:
	// �e���f��
	CModel* mpGun;
};
#endif