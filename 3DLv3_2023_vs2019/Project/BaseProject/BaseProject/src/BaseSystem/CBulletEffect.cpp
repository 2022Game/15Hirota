//#include "CBulletEffect.h"
//#include "CCollisionManager.h"
//
//CBulletEffect::CBulletEffect()
//	:CBillBoardImage("Effect\\bakuhatsu",ETag::eBakuhatu,ETaskPriority::eEffect,
//		0,ETaskPauseType::eGame)
//	, mMoveSpeed(0.0f,0.0f,0.0f)
//{
//	mpColliderSpher = new CColliderSphere
//	(
//		this, ELayer::eEffect,
//		1.1f
//	);
//	mpColliderSpher->SetCollisionLayers({ ELayer::eEffect,ELayer::eEffect });
//}
//
//CBulletEffect::~CBulletEffect()
//{
//	SAFE_DELETE(mpColliderSpher);
//}
//
//
//void CBulletEffect::Setup(const CVector& pos, const CVector& dir)
//{
//	Position(pos);
//	mMoveSpeed = dir * 2.0f;
//}
//
//void CBulletEffect::Collision(CCollider* self, CCollider* other, const CHitInfo& hit)
//{
//	//if (self == mpColliderSpher)
//	//{
//	//	// �v���C���[�ƏՓ˂����ꍇ
//	//	if (other->Layer() == ELayer::ePlayer)
//	//	{
//	//		Kill();
//	//	}
//	//	else if (other->Layer() == ELayer::eField)
//	//	{
//	//		Position(Position() + hit.adjust * hit.weight);
//
//	//		mMoveSpeed.Y(0.0f);
//	//	}
//	//}
//}
//
//void CBulletEffect::Update()
//{
//	// �d�͂����Z
//	mMoveSpeed.Y(mMoveSpeed.Y() - 0.1f);
//	// ���W���ړ����x���ړ�������
//	Position(Position() + mMoveSpeed * Time::DeltaTime());
//}