#include "CCollider.h"
#include "CCollisionManager.h"
#include "CColliderLine.h"
#include "CColliderSphere.h"
#include "CColliderTriangle.h"
#include "CColliderMesh.h"
#include "CObjectBase.h"
#include "Maths.h"

// �R���X�g���N�^
CCollider::CCollider(CObjectBase* owner, ELayer layer, EColliderType type,
	bool isKinematic, float weight)
	: mLayer(layer)
	, mType(type)
	, mpOwner(owner)
	, mIsEnable(true)
	, mIsKinematic(isKinematic)
	, mWeight(weight)
	, mCollisionLayers(~0)
	, mCollisionTags(~0)
	, mpAttachMtx(nullptr)
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

// �Փˎ��̉����߂��̉e�����󂯂邩�ǂ�����ݒ�
void CCollider::SetKinematic(bool iskinematic)
{
	mIsKinematic = iskinematic;
}

// �Փˎ��̉����߂��̉e�����󂯂邩�ǂ���
bool CCollider::IsKinematic() const
{
	return mIsKinematic;
}

// �R���C�_�[�̏d�ʂ�ݒ�
void CCollider::SetWeight(float weight)
{
	mWeight = weight;
}

// �R���C�_�[�̏d�ʂ��擾
float CCollider::GetWeight() const
{
	return mWeight;
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

// �w�肵���s��ɃR���C�_�[�𕍑�������
void CCollider::SetAttachMtx(const CMatrix* mtx)
{
	mpAttachMtx = mtx;
}

// �s����擾
CMatrix CCollider::Matrix() const
{
	CMatrix m = CTransform::Matrix();
	// ����������s�񂪐ݒ肳��Ă����
	if (mpAttachMtx != nullptr)
	{
		// ���̍s��ɕ�������
		CMatrix sm;
		sm.Scale(100.0f, 100.0f, 100.0f);
		m = sm * *mpAttachMtx * m;
	}
	// �����傪�ݒ肳��Ă����
	else if (mpOwner != nullptr)
	{
		// ������̍s��ɕ���
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

// �O�p�`�ƎO�p�`�̏Փ˔���
bool CCollider::CollisionTriangle(const CVector& t00, const CVector& t01, const CVector& t02,
	const CVector& t10, const CVector& t11, const CVector& t12,
	CHitInfo* hit)
{
	return false;
}

// �O�p�`�Ɛ����̏Փ˔���
bool CCollider::CollisionTriangleLine(
	const CVector& t0, const CVector& t1, const CVector& t2,
	const CVector& ls, const CVector& le,
	CHitInfo* h, bool isLeftMain)
{
	//�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	CVector normal = CVector::Cross(t1 - t0, t2 - t0).Normalized();
	//�O�p�̒��_��������n�_�ւ̃x�N�g�������߂�
	CVector v0sv = ls - t0;
	//�O�p�̒��_��������I�_�ւ̃x�N�g�������߂�
	CVector v0ev = le - t0;
	//�������ʂƌ������Ă��邩���ςŊm�F����
	float dots = v0sv.Dot(normal);
	float dote = v0ev.Dot(normal);
	//�v���X�͌������ĂȂ�
	if (dots * dote >= 0.0f) {
		//�Փ˂��ĂȂ��i�����s�v�j
		h->adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����͖ʂƌ������Ă���
	//�ʂƐ����̌�_�����߂�
	//��_�̌v�Z
	CVector cross = ls + (le - ls) * (abs(dots) / (abs(dots) + abs(dote)));

	//��_���O�p�`���Ȃ�Փ˂��Ă���
	//���_1���_2�x�N�g���ƒ��_1��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((t1 - t0).Cross(cross - t0).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		h->adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//���_2���_3�x�N�g���ƒ��_2��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((t2 - t1).Cross(cross - t1).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		h->adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}
	//�ۑ�R�Q
	//���_3���_1�x�N�g���ƒ��_3��_�x�N�g���Ƃ̊O�ς����߁A
	//�@���Ƃ̓��ς��}�C�i�X�Ȃ�A�O�p�`�̊O
	if ((t0 - t2).Cross(cross - t2).Dot(normal) < 0.0f) {
		//�Փ˂��ĂȂ�
		h->adjust = CVector(0.0f, 0.0f, 0.0f);
		return false;
	}

	//�����l�v�Z�i�Փ˂��Ȃ��ʒu�܂Ŗ߂��j
	if (dots < 0.0f) {
		//�n�_������
		h->adjust = normal * dots;
	}
	else {
		//�I�_������
		h->adjust = normal * dote;
	}
	if (!isLeftMain) h->adjust = -h->adjust;
	return true;
}

// �O�p�`�Ƌ��̏Փ˔���
bool CCollider::CollisionTriangleSphere(
	const CVector& t0, const CVector& t1, const CVector& t2,
	const CVector& sp, const float sr,
	CHitInfo* h, bool isLeftMain)
{
	//CVector v[3], sv, ev;
	////�e�R���C�_�̒��_�����[���h���W�֕ϊ�
	//CMatrix tm = t->Matrix();
	//v[0] = t->V(0) * tm;
	//v[1] = t->V(1) * tm;
	//v[2] = t->V(2) * tm;
	////�ʂ̖@�����A�O�ς𐳋K�����ċ��߂�
	//CVector normal = CVector::Cross(v[1] - v[0], v[2] - v[0]).Normalized();
	////���R���C�_�����[���h���W�ō쐬
	//CMatrix sm = s->Matrix();
	//sv = normal * sm * s->Radius();
	//ev = -normal * sm * s->Radius();
	//CColliderLine line(nullptr, ELayer::eNone, sv, ev);
	////�O�p�R���C�_�Ɛ��R���C�_�̏Փˏ���
	//return CollisionTriangleLine(t, &line, h);
	return false;
}

// ���Ƌ��̏Փ˔���
bool CCollider::CollisionSphere(const CVector& sp0, const float sr0,
	const CVector& sp1, const float sr1, CHitInfo* hit)
{
	//���S���璆�S�ւ̃x�N�g�������߂�
	CVector vec = sp0 - sp1;
	float length = vec.Length();
	//���S�̋��������a�̍��v��菬�����ƏՓ�
	float sum = sr0 + sr1;
	if (sum > length) {
		hit->adjust = vec.Normalized() * (sum - length);
		//�Փ˂��Ă���
		return  true;
	}

	hit->adjust = CVector(0.0f, 0.0f, 0.0f);
	//�Փ˂��Ă��Ȃ�
	return false;
}

// ���Ɛ����̏Փ˔���
bool CCollider::CollisionSphereLine(const CVector& sp, const float sr,
	const CVector& ls, const CVector& le,
	CHitInfo* hit, bool isLeftMain)
{
	CVector nearest;
	float length = CalcDistancePointToLine(sp, ls, le, &nearest);
	if (length < sr)
	{
		CVector n = (sp - nearest).Normalized() * (isLeftMain ? 1.0f : -1.0f);
		hit->adjust = n * (sr - length);
		return true;
	}

	hit->adjust = CVector(0.0f, 0.0f, 0.0f);
	return false;
}
// �����Ɛ����̏Փ˔���
bool CCollider::CollisionLine(const CVector& ls0, const CVector& le0,
	const CVector& ls1, const CVector& le1, CHitInfo* hit)
{
	//TODO:�����l�̑Ή�
	hit->adjust = CVector(0.0f, 0.0f, 0.0f);

	CVector S1E1 = le0 - ls0;
	CVector S2E2 = le1 - ls1;
	CVector CD = CVector::Cross(le0 - ls0, le1 - ls1).Normalized();

	CVector S1S2 = ls1 - ls0;
	CVector S1E2 = le1 - ls0;
	CVector S2S1 = ls0 - ls1;
	CVector S2E1 = le0 - ls1;

	float length = 0.0f;
	float d1 = S1E1.Cross(S1S2).Dot(S1E1.Cross(S1E2));
	float d2 = S2E2.Cross(S2S1).Dot(S2E2.Cross(S2E1));
	if (d1 < 0 && d2 < 0)
	{
		length = abs(S1S2.Dot(CD));
	}
	else
	{
		float length1 = CalcDistancePointToLine(ls0, ls1, le1);
		float length2 = CalcDistancePointToLine(le0, ls1, le1);
		float length3 = CalcDistancePointToLine(ls1, ls0, le0);
		float length4 = CalcDistancePointToLine(le1, ls0, le0);
		length = fminf(fminf(length1, length2), fminf(length3, length4));
	}

	if (length < 0.1f + 0.1f)
	{
		return true;
	}

	return false;
}

// ���b�V���Ɛ����̏Փ˔���
bool CCollider::CollisionMeshLine(const std::list<STVertex>& tris,
	const CVector& ls, const CVector& le,
	CHitInfo* hit, bool isLeftMain)
{
	bool ret = false;
	CVector adjust;
	for (auto& v : tris)
	{
		if (CollisionTriangleLine(v.V[0], v.V[1], v.V[2], ls, le, hit, isLeftMain))
		{
			hit->tris.push_back(v);
			adjust = hit->adjust;
			ret = true;
		}
	}
	hit->adjust = adjust;
	return ret;
}

// ���b�V���Ƌ��̏Փ˔���
bool CCollider::CollisionMeshSpehre(const std::list<STVertex>& tris,
	const CVector& sp, const float sr,
	CHitInfo* hit, bool isLeftMain)
{
	bool ret = false;
	for (auto& v : tris)
	{
		if (CollisionTriangleSphere(v.V[0], v.V[1], v.V[2], sp, sr, hit, isLeftMain))
		{
			hit->tris.push_back(v);
			ret = true;
		}
	}
	return ret;
}

// ���b�V���ƎO�p�`�̏Փ˔���
bool CCollider::CollisionMeshTriangle(const std::list<STVertex>& tris,
	const CVector& t0, const CVector& t1, const CVector& t2,
	CHitInfo* hit, bool isLeftMain)
{
	bool ret = false;
	for (auto& v : tris)
	{
		CVector v00 = isLeftMain ? v.V[0] : t0;
		CVector v01 = isLeftMain ? v.V[1] : t1;
		CVector v02 = isLeftMain ? v.V[2] : t2;
		CVector v10 = isLeftMain ? t0 : v.V[0];
		CVector v11 = isLeftMain ? t1 : v.V[1];
		CVector v12 = isLeftMain ? t2 : v.V[2];
		if (CollisionTriangle(v00, v01, v02, v10, v11, v12, hit))
		{
			hit->tris.push_back(v);
			ret = true;
		}
	}
	return ret;
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

bool CCollider::Collision(CCollider* c0, CCollider* c1, CHitInfo* hit)
{
	switch (c0->Type())
	{
	case EColliderType::eLine:
	{
		CColliderLine* line0 = dynamic_cast<CColliderLine*>(c0);
		CVector ls0, le0;
		line0->Get(&ls0, &le0);

		switch (c1->Type())
		{
		case EColliderType::eLine:
		{
			CColliderLine* line1 = dynamic_cast<CColliderLine*>(c1);
			CVector ls1, le1;
			line1->Get(&ls1, &le1);
			return CollisionLine(ls0, le0, ls1, le1, hit);
		}
		case EColliderType::eSphere:
		{
			CColliderSphere* sphere = dynamic_cast<CColliderSphere*>(c1);
			CVector sp;
			float sr;
			sphere->Get(&sp, &sr);
			return CollisionSphereLine(sp, sr, ls0, le0, hit, false);
		}
		case EColliderType::eTriangle:
		{
			CColliderTriangle* triangle = dynamic_cast<CColliderTriangle*>(c1);
			CVector t0, t1, t2;
			triangle->Get(&t0, &t1, &t2);
			return CollisionTriangleLine(t0, t1, t2, ls0, le0, hit, false);
		}
		case EColliderType::eMesh:
		{
			CColliderMesh* mesh = dynamic_cast<CColliderMesh*>(c1);
			std::list<STVertex> tris;
			mesh->Get(&tris);
			return CollisionMeshLine(tris, ls0, le0, hit, false);
		}
		}
		break;
	}
	case EColliderType::eSphere:
	{
		CColliderSphere* sphere0 = dynamic_cast<CColliderSphere*>(c0);
		CVector sp0;
		float sr0;
		sphere0->Get(&sp0, &sr0);

		switch (c1->Type())
		{
		case EColliderType::eLine:
		{
			CColliderLine* line = dynamic_cast<CColliderLine*>(c1);
			CVector ls, le;
			line->Get(&ls, &le);
			return CollisionSphereLine(sp0, sr0, ls, le, hit, true);
		}
		case EColliderType::eSphere:
		{
			CColliderSphere* sphere1 = dynamic_cast<CColliderSphere*>(c1);
			CVector sp1;
			float sr1;
			sphere1->Get(&sp1, &sr1);
			return CollisionSphere(sp0, sr0, sp1, sr1, hit);
		}
		case EColliderType::eTriangle:
		{
			CColliderTriangle* triangle0 = dynamic_cast<CColliderTriangle*>(c0);
			CVector t0, t1, t2;
			triangle0->Get(&t0, &t1, &t2);
			return CollisionTriangleSphere(t0, t1, t2, sp0, sr0, hit, false);
		}
		case EColliderType::eMesh:
		{
			CColliderMesh* mesh = dynamic_cast<CColliderMesh*>(c1);
			std::list<STVertex> tris;
			mesh->Get(&tris);
			return CollisionMeshSpehre(tris, sp0, sr0, hit, false);
		}
		}
		break;
	}
	case EColliderType::eTriangle:
	{
		CColliderTriangle* triangle0 = dynamic_cast<CColliderTriangle*>(c0);
		CVector t00, t01, t02;
		triangle0->Get(&t00, &t01, &t02);
		switch (c1->Type())
		{
		case EColliderType::eLine:
		{
			CColliderLine* line = dynamic_cast<CColliderLine*>(c1);
			CVector ls, le;
			line->Get(&ls, &le);
			return CollisionTriangleLine(t00, t01, t02, ls, le, hit, true);
		}
		case EColliderType::eSphere:
		{
			CColliderSphere* sphere = dynamic_cast<CColliderSphere*>(c1);
			CVector sp;
			float sr;
			sphere->Get(&sp, &sr);
			return CollisionTriangleSphere(t00, t01, t02, sp, sr, hit, true);
		}
		case EColliderType::eTriangle:
		{
			CColliderTriangle* triangle1 = dynamic_cast<CColliderTriangle*>(c1);
			CVector t10, t11, t12;
			triangle1->Get(&t10, &t11, &t12);
			return CollisionTriangle(t00, t01, t02, t10, t11, t12, hit);
		}
		case EColliderType::eMesh:
		{
			CColliderMesh* mesh = dynamic_cast<CColliderMesh*>(c1);
			std::list<STVertex> tris;
			mesh->Get(&tris);
			return CollisionMeshTriangle(tris, t00, t01, t02, hit, false);
		}
		}
		break;
	}
	case EColliderType::eMesh:
	{
		CColliderMesh* mesh = dynamic_cast<CColliderMesh*>(c0);
		std::list<STVertex> tris;
		mesh->Get(&tris);
		switch (c1->Type())
		{
		case EColliderType::eLine:
		{
			CColliderLine* line = dynamic_cast<CColliderLine*>(c1);
			CVector ls, le;
			line->Get(&ls, &le);
			return CollisionMeshLine(tris, ls, le, hit, true);
		}
		case EColliderType::eSphere:
		{
			CColliderSphere* sphere = dynamic_cast<CColliderSphere*>(c1);
			CVector sp;
			float sr;
			sphere->Get(&sp, &sr);
			return CollisionMeshSpehre(tris, sp, sr, hit, true);
		}
		case EColliderType::eTriangle:
		{
			CColliderTriangle* triangle = dynamic_cast<CColliderTriangle*>(c1);
			CVector t0, t1, t2;
			triangle->Get(&t0, &t1, &t2);
			return CollisionMeshTriangle(tris, t0, t1, t2, hit, true);
		}
		case EColliderType::eMesh:
		{
			// ���b�V���ƃ��b�V���͏Փ˔�����s��Ȃ�
			return false;
		}
		}
		break;
	}
	}
	return false;
}

// �Փˎ��̉����߂��������Z�o
float CCollider::CalcPushBackRatio(CCollider* self, CCollider* other)
{
	// ���g�̃R���C�_�[�������߂��̉e�����󂯂Ȃ�
	if (self->IsKinematic()) return 0.0f;
	// ����̃R���C�_�[�������߂��̉e�����󂯂Ȃ�
	if (other->IsKinematic()) return 1.0f;

	// �����̃R���C�_�[�������߂��̉e�����󂯂�ꍇ�́A
	// �����̃R���C�_�[�̏d�ʂŉ����߂��������Z�o
	float sw = self->GetWeight();
	float ow = other->GetWeight();
	// �����d�ʂȂ�΁A50%�̉e�����󂯂�
	if (sw == ow) return 0.5f;
	// ���g�̏d�ʂ�0�Ȃ�΁A100%�̉e�����󂯂�
	if (sw <= 0.0f) return 1.0f;
	// ����̏d�ʂ�0�Ȃ�΁A�e���͎󂯂Ȃ�
	if (ow <= 0.0f) return 0.0f;

	// �d�ʂ̊������v�Z���ĕԂ�
	return 1.0f - Math::Clamp01(sw / (sw + ow));
}
