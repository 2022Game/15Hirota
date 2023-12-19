#ifndef CGUN_H
#define CGUN_H
#include "CObjectBase.h"
#include "CWeapon.h"
#include "CColliderLine.h"
#include "CModel.h"

class CGun :public CWeapon
{
public:
	CGun();
	~CGun();

	void Update();
	void Render();

	// •Ší‚Ìs—ñ‚ğæ“¾
	CMatrix Matrix() const override;

private:

	CModel* mpGun;
};
#endif