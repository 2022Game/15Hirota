#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderTriangle.h"

// �R���X�g���N�^
CCollider::CCollider(CObjectBase* owner, ELayer layer, EColliderType type)
	: mLayer(layer)
	, mType(type)
	, mpOwner(owner)
	, mIsEnable(true)
	, mCollisionLayers(~0)
	, mCollisionTags(~0)
{
	// �R���W�������X�g�ɒǉ�
	CCollisionManager::Instance()->Add(this);
}

// �f�X�g���N�^
CCollider::~CCollider()
{
	// �R���W�������X�g����폜
	CCollisionManager::Instance()->Remove(this);
}

// �Փ˔��背�C���[���擾
ELayer CCollider::Layer() const
{
	return mLayer;
}

// �R���C�_�[�̎�ނ��擾
EColliderType CCollider::Type() const
{
	return mType;
}

// �R���C�_�[�̎������Ԃ�
CObjectBase* CCollider::Owner() const
{
	return mpOwner;
}

// �R���C�_�[�̎�����̃^�O���擾
ETag CCollider::Tag() const
{
	// �����傪���݂���΁A������̃^�O��Ԃ�
	if (mpOwner == nullptr) return ETag::eNone;
	return mpOwner->Tag();
}

// �R���C�_�[���L�����ǂ�����ݒ�
void CCollider::SetEnable(bool isEnable)
{
	mIsEnable = isEnable;
}

// �R���C�_�[���L�����ǂ������擾
bool CCollider::IsEnable() const
{
	return mIsEnable;
}

// �w�肵���R���C�_�[�ƏՓ˔�����s�����ǂ������擾
bool CCollider::IsCollision(CCollider* col) const
{
	// �������g�������͑���̃R���C�_�[���L���łȂ���΁A
	// �Փ˔�����s��Ȃ�
	if (col == nullptr) return false;
	if (!col->IsEnable()) return false;
	if (!mIsEnable) return false;

	// �����R���C�_�[�������́A�����傪�����ł���΁A
	// �Փ˔�����s��Ȃ�
	if (col == this) return false;
	if (col->Owner() != nullptr || mpOwner != nullptr)
	{
		if (col->Owner() == mpOwner) return false;
	}

	// �Փ˔�����s�����C���[��
	if (!IsCollisionLayer(col->Layer())) return false;
	// �Փ˔�����s���I�u�W�F�N�g�^�O��
	if (!IsCollisionTag(col->Tag())) return false;

	// �S�Ă̏����𖞂������ꍇ�͏Փ˔�����s��
	return true;
}

// �Փ˔�����s�����C���[��ݒ�
void CCollider::SetCollisionLayers(Layers layers)
{
	mCollisionLayers = 0;
	for (auto&& layer : layers)
	{
		mCollisionLayers |= 1 << (int)layer;
	}
}

// �w�肵�����C���[�Ƃ̏Փ˔�����s�����ǂ�����ݒ�
void CCollider::SetCollisionLayer(ELayer layer, bool isCollision)
{
	if (isCollision) mCollisionLayers |= 1 << (int)layer;
	else mCollisionLayers &= ~(1 << (int)layer);
}

// �w�肵�����C���[�ƏՓ˔�����s�����ǂ������擾
bool CCollider::IsCollisionLayer(ELayer layer) const
{
	return (mCollisionLayers & 1 << (int)layer) != 0;
}

// �Փ˔�����s���I�u�W�F�N�g�^�O��ݒ�
void CCollider::SetCollisionTags(Tags tags)
{
	mCollisionTags = 0;
	for (auto&& tag : tags)
	{
		mCollisionTags |= 1 << (int)tag;
	}
}

// �w�肵���I�u�W�F�N�g�^�O�Ƃ̏Փ˔�����s�����ǂ�����ݒ�
void CCollider::SetCollisionTag(ETag tag, bool isCollision)
{
	if (isCollision) mCollisionTags |= 1 << (int)tag;
	else mCollisionTags &= ~(1 << (int)tag);
}

// �w�肵���I�u�W�F�N�g�^�O�ƏՓ˔�����s�����ǂ������擾
bool CCollider::IsCollisionTag(ETag tag) const
{
	return (mCollisionTags & 1 << (int)tag) != 0;
}

// �s����擾
CMatrix CCollider::Matrix() const
{
	CMatrix m = CTransform::Matrix();
	if (mpOwner != nullptr)
	{
		m = mpOwner->Matrix() * m;
	}
	return m;
}

// �R���C�_�[�̐ݒ�
void CCollider::Set(CObjectBase* owner, ELayer layer)
{
	mpOwner = owner;
	mLayer = layer;
}

bool CCollider::CollisionTriangleLine(CColliderTriangle* t, CColliderLine* l, CVector* a)
{
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	CMatrix tm = t->Matrix();
	v[0] = t->V(0) * tm;
	v[1] = t->V(1) * tm;
	v[2] = t->V(2) * tm;
	CMatrix lm = l->Matrix();
	sv = l->V(0) * lm;
	ev = l->V(1) * lm;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = CVector::Cross(v[1] - v[0], v[2] - v[0]).Normalized();
	//�O�p�̒��_��������n�_�ւ̃x�N�g�������߂�
	CVector v0sv = sv - v[0];
	//�O�p�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = ev - v[0];
	//�������ʂƌ������Ă��邩���ςŊm�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������ĂȂ�
	if (dots * dote >= 0.0f) {
		//�Փ˂��ĂȂ��i�����s�v�j
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����͖ʂƌ������Ă���
	//�ʂƐ����̌�_�����߂�
	//��_�̌v�Z
	CVector cross = sv + (ev - sv) * (abs(dots) / (abs(dots) + abs(dote)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���
	//���_1���_2�x�N�g���ƒ��_1��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[1] - v[0]).Cross(cross - v[0]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_2���_3�x�N�g���ƒ��_2��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[2] - v[1]).Cross(cross - v[1]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�ۑ�R�Q
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((v[0] - v[2]).Cross(cross - v[2]).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		*a = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂��j
	if (dots < 0.0f) {
		//�n�_������
		*a = normal * -dots;
	}
	else {
		//�I�_������
		*a = normal * -dote;
	}
	return true;
}

bool CCollider::CollisionTriangleSphere(CColliderTriangle* t, CColliderSphere* s, CVector* a)
{
	CVector v[3], sv, ev;
	//�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	CMatrix tm = t->Matrix();
	v[0] = t->V(0) * tm;
	v[1] = t->V(1) * tm;
	v[2] = t->V(2) * tm;
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = CVector::Cross(v[1] - v[0], v[2] - v[0]).Normalized();
	//���R���C�_�����[���h���W�ō쐬
	CMatrix sm = s->Matrix();
	sv = normal * sm * s->Radius();
	ev = -normal * sm * s->Radius();
	CColliderLine line(nullptr, ELayer::eNone, sv, ev);
	//�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	return CollisionTriangleLine(t, &line, a);
}

bool CCollider::CollisionSphere(CColliderSphere* sphere1, CColliderSphere* sphere2, CVector* adjust)
{
	//�e�R���C�_�̒��S���W�����߂�
	//���_�~�R���C�_�̕ϊ��s��~�e�̕ϊ��s��
	CVector pos1 = sphere1->Matrix().Position();
	CVector pos2 = sphere2->Matrix().Position();
	//���S���璆�S�ւ̃x�N�g�������߂�
	CVector vec = pos1 - pos2;
	float length = vec.Length();
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	float sum = sphere1->Radius() + sphere2->Radius();
	if (sum > length) {
		*adjust = pos2 + vec.Normalized() * sum;
		//�Փ˂��Ă���
		return  true;
	}

	*adjust = CVector(0.0f, 0.0f, 0.0f);
	//�Փ˂��Ă��Ȃ�
	return false;
}

bool CCollider::CollisionSphereLine(CColliderSphere* sphere, CColliderLine* line, CVector* adjust)
{
	CVector spherePos = sphere->Matrix().Position();
	CMatrix lm = line->Matrix();
	CVector lineStartPos = line->V(0) * lm;
	CVector lineEndPos = line->V(1) * lm;

	CVector nearest;
	float length = CalcDistancePointToLine(spherePos, lineStartPos, lineEndPos, &nearest);
	if (length < sphere->Radius())
	{
		*adjust = nearest + (spherePos - nearest).Normalized() * sphere->Radius();
		return true;
	}

	*adjust = CVector(0.0f, 0.0f, 0.0f);
	return false;
}

bool CCollider::CollisionLine(CColliderLine* line1, CColliderLine* line2, CVector* adjust)
{
	//TODO:�����l�̑Ή�
	*adjust = CVector(0.0f, 0.0f, 0.0f);

	CMatrix lm1 = line1->Matrix();
	CVector S1 = line1->V(0) * lm1;
	CVector E1 = line1->V(1) * lm1;
	CMatrix lm2 = line2->Matrix();
	CVector S2 = line2->V(0) * lm2;
	CVector E2 = line2->V(1) * lm2;

	CVector S1E1 = E1 - S1;
	CVector S2E2 = E2 - S2;
	CVector CD = CVector::Cross(E1 - S1, E2 - S2).Normalized();

	CVector S1S2 = S2 - S1;
	CVector S1E2 = E2 - S1;
	CVector S2S1 = S1 - S2;
	CVector S2E1 = E1 - S2;

	float length = 0.0f;
	float d1 = S1E1.Cross(S1S2).Dot(S1E1.Cross(S1E2));
	float d2 = S2E2.Cross(S2S1).Dot(S2E2.Cross(S2E1));
	if (d1 < 0 && d2 < 0)
	{
		length = abs(S1S2.Dot(CD));
	}
	else
	{
		float length1 = CalcDistancePointToLine(S1, S2, E2);
		float length2 = CalcDistancePointToLine(E1, S2, E2);
		float length3 = CalcDistancePointToLine(S2, S1, E1);
		float length4 = CalcDistancePointToLine(E2, S1, E1);
		length = fminf(fminf(length1, length2), fminf(length3, length4));
	}

	if (length < line1->Radius() + line2->Radius())
	{
		return true;
	}

	return false;
}

float CCollider::CalcDistancePointToLine(const CVector& point, const CVector& lineS, const CVector& lineE, CVector* nearest)
{
	CVector SE = lineE - lineS;
	float t = (point - lineS).Dot(SE.Normalized());

	CVector C;
	if (t < 0) C = lineS;
	else if (t > SE.Length()) C = lineE;
	else
	{
		C = lineS + SE.Normalized() * t;
	}

	if (nearest != nullptr) *nearest = C;

	return (C - point).Length();
}

bool CCollider::Collision(CCollider* c0, CCollider* c1, CVector* adjust)
{
	switch (c0->Type())
	{
		case EColliderType::eLine:
			switch (c1->Type())
			{
			case EColliderType::eLine:
				return CollisionLine
				(
					dynamic_cast<CColliderLine*>(c0),
					dynamic_cast<CColliderLine*>(c1),
					adjust
				);
			case EColliderType::eSphere:
				return CollisionSphereLine
				(
					dynamic_cast<CColliderSphere*>(c1),
					dynamic_cast<CColliderLine*>(c0),
					adjust
				);
			case EColliderType::eTriangle:
				return CollisionTriangleLine
				(
					dynamic_cast<CColliderTriangle*>(c1),
					dynamic_cast<CColliderLine*>(c0),
					adjust
				);
			}
			break;
		case EColliderType::eSphere:
			switch (c1->Type())
			{
			case EColliderType::eLine:
				return CollisionSphereLine
				(
					dynamic_cast<CColliderSphere*>(c0),
					dynamic_cast<CColliderLine*>(c1),
					adjust
				);
			case EColliderType::eSphere:
				return CollisionSphere
				(
					dynamic_cast<CColliderSphere*>(c1),
					dynamic_cast<CColliderSphere*>(c0),
					adjust
				);
			case EColliderType::eTriangle:
				return CollisionTriangleSphere
				(
					dynamic_cast<CColliderTriangle*>(c1),
					dynamic_cast<CColliderSphere*>(c0),
					adjust
				);
			}
			break;
		case EColliderType::eTriangle:
			switch (c1->Type())
			{
			case EColliderType::eLine:
				return CollisionTriangleLine
				(
					dynamic_cast<CColliderTriangle*>(c0),
					dynamic_cast<CColliderLine*>(c1),
					adjust
				);
			case EColliderType::eSphere:
				return CollisionTriangleSphere
				(
					dynamic_cast<CColliderTriangle*>(c0),
					dynamic_cast<CColliderSphere*>(c1),
					adjust
				);
			case EColliderType::eTriangle:
				//return CollisionTriangle
				//(
				//	dynamic_cast<CColliderTriangle*>(c0),
				//	dynamic_cast<CColliderTriangle*>(c1),
				//	adjust
				//);
				break;
			}
			break;
	}
	return false;
}
